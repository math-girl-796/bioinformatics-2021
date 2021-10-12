#include "dr_tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void Hello(void) {
    printf("Hello, world!\n");
}

long* CountFasta(const char* filePath) {
    // 打开文件
    FILE* f = fopen(filePath, "r");
    if (f == NULL) {
        perror("CountFasta");
        exit(1);
    }
    // 逐个读取文件字符，根据情况执行相应行为
    long maxSize = 1;
    long pos = 0;
    long* ret = malloc(maxSize * sizeof(long));
    while (1) {
        char c = fgetc(f);
        // putchar(c);
        /* 读到文件结尾：结束循环 */
        if (c == EOF) break; 
        /* 读到">"：读掉这一行, 游标加1, 游标处初始化为0 */ 
        else if (c == '>') { 
            while ((c = fgetc(f)) != '\n' && c != EOF);
            pos ++;
            // printf("maxSize: %ld\npos: %ld\n", maxSize, pos);
            if (pos == maxSize && c != EOF) {
                maxSize *= 2;
                ret = realloc(ret, maxSize * sizeof(long)); // 这里千万记得乘sizeof(long)
            }
            ret[pos] = 0;
        }
        /* 遇到空白符：跳过 */
        else if (isspace(c)) { 
            continue;
        }
        /* 其他情况：正常计数 */
        else if (pos >= 1) { 
            ret[pos] ++;
            // printf("%ld\n", ret[pos]);
        }
    }
    ret[0] = pos;
    ret = realloc(ret, (pos + 1) * sizeof(long));  // 回收未使用的临时堆内存
    fclose(f);
    return ret;
}


long Computer2BitStrLength(long byteStringLength) {
    return (byteStringLength % 4 == 0) ? byteStringLength / 4 : byteStringLength / 4 + 1;
}

// rule: ['a': b'00', 'c': b'01', 'g': b'10', 't': b'11']
// acgtString "123456789" will be converted to "'1234','5678','9xxx'"
char* CompressBase(const char* acgtString, long* length) {
    long strLength = strlen(acgtString);
    long realStringLength = strLength > *length ? strLength : *length;
    long retStringLength = Computer2BitStrLength(realStringLength);
    char* ret = malloc(retStringLength * sizeof(char));

    long sPos = -1; // pos of acgtString
    long rPos = -1; // pos of ret

    while(1) {
        if (++rPos > retStringLength) break;
        char buffer = 0;
        for (int i = 0; i < 4; i++) {
            if (++sPos >= realStringLength) break;
            char select = 0;
            switch(acgtString[sPos]){
                case 'A':
                case 'a': select = 0; break;
                case 'C':
                case 'c': select = 1; break;
                case 'G': 
                case 'g': select = 2; break;
                case 'T': 
                case 't': select = 3; break;
                default:
                    fprintf(stderr, "CompressBase: unexpected character %c", acgtString[sPos]);
                    exit(1);
            }
            buffer += select << (3-i) * 2;
        }
        ret[rPos] = buffer;
    }

    *length = realStringLength;
    return ret;
}

char* DeCompressBase(const char* compressedString, long start, long length) {
    long cPos = start / 4; // compressedString pos
    char* ret = malloc(length * sizeof(char) + 1); // +1 for '\0'

    long rPos = -1; // ret pos
    int i = start % 4;
    while(1) {
        if (++rPos >= length) break;

        char code = (unsigned char) // 每次移位后都要强转为无符号数，因为移位表达式的值是有符号数
            ((unsigned char)compressedString[cPos] << 2 * i) // 保证进行的是逻辑右移
             >> 6;
        if (++i == 4) {
            i = 0;
            cPos++;
        }

        switch (code)
        {
            case 0: ret[rPos] = 'A'; break;
            case 1: ret[rPos] = 'C'; break;
            case 2: ret[rPos] = 'G'; break;
            case 3: ret[rPos] = 'T'; break;
            default: fprintf(stderr, "DeCompressBase: decode fault: %d!\n", code); exit(1);
        }
    }
    ret[rPos] = '\0';
    return ret;
}

char RetrieveCompressBase(const char* compressedString, long pos) {
    long cPos = pos / 4; // compressedString pos
    int i = pos % 4;
    char ret;

    char code = (unsigned char) // 每次移位后都要强转为无符号数，因为移位表达式的值是有符号数
        ((unsigned char)compressedString[cPos] << 2 * i) // 保证进行的是逻辑右移
        >> 6;

    switch (code)
    {
        case 0: ret = 'A'; break;
        case 1: ret = 'C'; break;
        case 2: ret = 'G'; break;
        case 3: ret = 'T'; break;
        default: fprintf(stderr, "RetrieveCompressBase: decode fault: %d!\n", code); exit(1);
    }
    return ret;
}


// long* QuickSortSaFromCs(const char* cprString, long start, long length) {}