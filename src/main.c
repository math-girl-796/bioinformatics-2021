#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "dr_tools.h"
#include "dr_sort.h"

long A[10] = {5,7,3,8,6,2,4,0,9,1};
int cmp(long l, long r) {
    if (A[l] < A[r]) return -1;
    else if (A[l] == A[r]) return 0;
    else return 1;
}

char* compressedCmp;
long compressedCmpLen;
int CmpCompressedSuffix(long l, long r) {
    while (l < compressedCmpLen && r < compressedCmpLen) {
        char lchar = RetrieveCompressBase(compressedCmp, l);
        char rchar = RetrieveCompressBase(compressedCmp, r);
        if (lchar < rchar) return -1;
        else if (lchar > rchar) return 1;
        else {
            l++; r++;
        }
    }
    if (l > r) return -1;
    else if (l < r) return 1;
    else {
        fprintf(stderr, "CmpCompressedSuffix: equal happens when compare suffixes!");
        exit(1);
    }
}

int main() {
    Hello();

    /* 测试：fasta文件计数测试 */
    // long* counts = CountFasta("/root/bioinformatics/lab1/test.fasta");
    // printf("NC_008253 length: %ld\n", counts[0]);
    // printf("NC_008253 length: %ld\n", counts[1]);
    // printf("NC_008253 length: %ld\n", counts[2]);
    // printf("NC_008253 length: %ld\n", counts[3]);
    // printf("NC_008253 length: %ld\n", counts[4]);
    // printf("NC_008253 length: %ld\n", counts[5]);
    // printf("NC_008253 length: %ld\n", counts[6]);

    /* 测试：计算压缩后序列长度 */
    // printf("%ld\n", Computer2BitStrLength(4));
    // printf("%ld\n", Computer2BitStrLength(5));
    // printf("%ld\n", Computer2BitStrLength(6));

    /* 测试：压缩，解压缩，Retrive压缩字符串 */
    // char* s = "gctagaccgggatttac";
    // long shortLength = strlen(s);
    // char* cs = CompressBase(s, &shortLength); // 压缩
    // printf("real compressed length: %ld\n", shortLength);
    // char* dcs = DeCompressBase(cs, 0, shortLength); // 解压
    // printf("decompress length: %ld\n", strlen(dcs));
    // printf("decompress result: %s\n", dcs);
    // printf("retrive each base: "); // Retrive
    // for (int i = 0; i < shortLength; i++) {
    //     printf("%c", RetrieveCompressBase(cs, i));
    // } printf("\n");
    // compressedCmp = cs; // 后缀数组
    // compressedCmpLen = shortLength;
    // long* shortSA = QuickSort(shortLength, CmpCompressedSuffix, SimpleQuickSortPartition); 
    // for (int i = 0; i < shortLength; i++) {
    //     printf("%s\n", dcs+shortSA[i]);
    // }

    /* 测试：快速排序10个整数 */
    // printf("index:\t\t");
    // for (int i = 0; i < 10; ++i) printf("%d ", i);
    // printf("\n");
    // printf("unsorted array:\t");
    // for (int i = 0; i < 10; ++i) printf("%ld ", A[i]);
    // printf("\n");
    // printf("sort 0-10:\t");
    // long* sorted_index = QuickSort(0, 10, cmp, SimpleQuickSortPartition);
    // for (int i = 0; i < 10; ++i) printf("%ld ", A[sorted_index[i]]);
    // printf("\n");
    // printf("sort 3-8:\t");
    // sorted_index = QuickSort(3, 8, cmp, SimpleQuickSortPartition);
    // for (int i = 0; i < 10; ++i) {
    //     if (3 <= i && i < 8) printf("%ld ", A[sorted_index[i - 3]]);
    //     else printf("%ld ", A[i]);
    // }
    // printf("\n");

    /* 测试：快速排序NC_008253.fna */
    // char* NC_008253FilePath = "/root/bioinformatics/lab1/data/NC_008253.fna";
    // long NC_008253Length = CountFasta(NC_008253FilePath)[1];
    // FILE* f_NC_008253 = fopen(NC_008253FilePath, "r");
    // char c;
    // long pos = -1;
    // while ((c = fgetc(f_NC_008253)) != '\n' && c != EOF); // 读掉第一行
    // char* NC_008253String = malloc(NC_008253Length * sizeof(char)); // 申请内存放置源字符串
    // while ((c = fgetc(f_NC_008253)) != EOF) {
    //     if (c == 'A' || c == 'a' || c == 'C' || c == 'c' || c == 'G' || c == 'g' || c == 'T' || c == 't')
    //         NC_008253String[++pos] = c;
    //     else
    //         continue;
    // }
    // printf("NC_008253String length: %ld\n", strlen(NC_008253String));
    // long NC_008253CompressedLength = NC_008253Length;
    // char* NC_008253CompressedString = CompressBase(NC_008253String, &NC_008253CompressedLength); // 压缩字符串
    // printf("compressed length: %ld\n", NC_008253CompressedLength);
    // compressedCmp = NC_008253CompressedString;
    // compressedCmpLen = NC_008253CompressedLength;

    // printf("start compute SA...\n");
    // clock_t time = clock();
    // long* NC_008253SA = QuickSort(0, NC_008253CompressedLength, CmpCompressedSuffix, SimpleQuickSortPartition);
    // time = clock() - time;
    // printf("compute SA time: %lfs\n", (double)time / CLOCKS_PER_SEC);

    // printf("start print partial result\n");
    // for (int i = 0; i < NC_008253CompressedLength; i++) {
    //     if (0 <= i && i <= 999) {
    //         printf("%-.100s\n", NC_008253String + NC_008253SA[i]);
    //     }
    // }
    // printf("end print partial result\n");
    // fclose(f_NC_008253);

    return 0;
}