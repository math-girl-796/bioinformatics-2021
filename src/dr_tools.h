#ifndef DR_TOOLS_H
#define DR_TOOLS_H

/*
    simply print "Hello world!" to default output stream.
*/
void Hello(void);

/*
    compress an uncased acgt string to a 2bit per base format.
    *length will be change to number of real compressed letters
    
    input: 
        acgtString: string of 'a', 'c', 'g', 't', 'A', 'C', 'G', 'T'.
        *length: length of the string, compressing will stop when it reaches the length or the end of the string.
    output: 2bit format string of acgt
*/
char* CompressBase(const char* acgtString, long* length);

/*
    decompress a 2bit format string to an UPPER case ACGT string

    input:
        compressedString: 2bit per base format string
        start: 0-base start pos of the dna sequance
        length: length of the sequence you want to decompress from the start
    output: 1byte encoded string of ACGT
    warning: SEGMENT FAULT! no check in this function about start and length
*/
char* DeCompressBase(const char* compressedString, long start, long length);

/*
    retrive a charater in dna string

    input:
        compressedString: 2bit per base format string
        pos: 0-base base position you want to retrieve in the compressedString
    output: one of 'A', 'C', 'G', 'T'
    warning: SEGMENT FAULT! no check in this function about pos
*/
char RetrieveCompressBase(const char* compressedString, long pos);

/*
    function: return (long)cell(byteStringLength / 4.0)
    implemented by logic, without float type
*/
long Computer2BitStrLength(long byteStringLength);

/*
    quick sort a compressed acgt string to get its SA.

    input: 
        cprString: compressed acgt string
        start: 0-base start pos of the dna sequance
        length: length of the sequence you want to decompress from the start
    output: array of type LONG, represent a suffix array
    warning: SEGMENT FAULT! no check in this function about start and length
*/
// long* QuickSortSaFromCs(const char* cprString, long start, long length);


/*
    return the number of reads and lengthes of each fasta string 
    in the input file in order

    input:
        filePath: path of a fasta format file
    output: array of type LONG, first element represents the number of reads
        others represent lengthes of each fasta string
        in the input file in order
*/
long* CountFasta(const char* filePath);



#endif