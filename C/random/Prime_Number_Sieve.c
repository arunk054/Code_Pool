/*
 * q7.c
 *
 *  Created on: Jan 16, 2010
 *      Author: arunk
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
Write a C program to compute and output to a file all the prime
numbers less than 2 × 10^9 , using the standard “sieve” method.
NB: There are about 98.1 million prime numbers less than 2 × 109 ,
and a standard ASCII file containing all of them, separated by spaces,
is about 639 MB in size!
 */

/*
 * Design: Here we use the standard sieve of eratosthenes, but each integer is stored
 * in a bit, not only that, our representation does not store multiples of 2 and 3, so,
 * values starts with 5,7,11,13 and so on... We will use a formula to convert a bit
 * index to a value and vice versa. For 2*10^9, we only need abt 80Mb of memory, (div by 3*8)
 */

//This has been optimized for large prime numbers of the order of millions - billions
//block size in bytes, having such a large block size may not be efficient for small numbers
#define MAX_BLOCK_SIZE 32768

//Each bit represents an integer, if it the corresponding bit is 0 ==> prime, 1==> composite
static unsigned char **bitVector;
static unsigned int noOfblocks = 0;

void freeBitVector(){
	unsigned int i;
	if (noOfblocks == 0)
		return;
	for (i = 0; i < noOfblocks; ++i) {
		free(bitVector[i]);
	}
	free(bitVector);
	noOfblocks = 0;
}

//This will compute primes upto <= maxNum and store it in a bit vector format
//The caller will have to call another method which will store the prime numbers to a file
void computePrimeNumbers(unsigned int maxNum) {
	unsigned int p,value;
	unsigned int i, j, dupBlocks;
	unsigned int curBitIndex, tempBitIndex, temp;
	unsigned int block_off,byte_off, *srcP, *destP;
	unsigned char mask, **dupBitVector;

	//Just make sure that user did not forget to free
	freeBitVector();

	//Allocate memory, we div by 3 because we have eliminated all multiples of 3,2
	noOfblocks = maxNum/(8*3*MAX_BLOCK_SIZE);
	//if there is no remainder then
	if ((maxNum % (8*3*MAX_BLOCK_SIZE)) > 0 )
		noOfblocks++;

	bitVector = (unsigned char**)malloc(noOfblocks*sizeof(char*));

	//printf("Allocating memory for bit vector...\n");
	for (i = 0; i < noOfblocks; ++i) {
		//calloc is used because we want all blocks initialized to zeros
		bitVector[i]=(unsigned char*)calloc(MAX_BLOCK_SIZE,sizeof(char));
	}
	//This is used to limit the size of duplicate bit vector
	//Div by 5, because our 'p' starts from 5.
	temp = maxNum/5;
	//But why do we need a duplicate, we need it because
	//we have to multiply a prime with non-prime in its first iteration, so, crossing out
	//non-primes is not allowed till all non-primes are crossed for that 'p'.
	dupBlocks = temp/(8*3*MAX_BLOCK_SIZE);
	if ((temp % (8*3*MAX_BLOCK_SIZE)) > 0 )
		dupBlocks++;

	dupBitVector = (unsigned char**)malloc(dupBlocks*sizeof(char*));
	for (i = 0; i < dupBlocks; ++i) {
		//calloc is used because we want all blocks initialized to zeros
		dupBitVector[i]=(unsigned char*)calloc(MAX_BLOCK_SIZE,sizeof(char));
	}

	//printf("Allocated memory for bit Vector\n");
	printf("TOTAL MEMORY allocated = %u KB\n", noOfblocks*MAX_BLOCK_SIZE/1024 + dupBlocks*MAX_BLOCK_SIZE/1024);

	printf("Generating prime numbers upto %u...\n",maxNum);
	//Our logic assumes that 2,3 is prime and all its multiples have been eliminated
	//hence start with p=5.
	if (maxNum<25) {
		//Free the duplicate bit vector
		for (i = 0; i < dupBlocks; ++i) {
			free(dupBitVector[i]);
		}
		free(dupBitVector);
		return;//do nothing. the bit vector already has the primes
	}

	p=5;
	curBitIndex = 0;
	value = (p*p);

	//The standard sieve method
	while((value) <= maxNum) {

		do {
			//Set the bit corresponding to value
			//so, first get its index, TODO put this in an inline function
			tempBitIndex = (value-5)/3;
			tempBitIndex += ((value-5)%3 != 0 )?1:0;

			//find block offest, byteOffset and bit position to set
			//div by 8*MAX_BS, TODO put this in an inline function
			block_off = (tempBitIndex>>3)/MAX_BLOCK_SIZE;
			byte_off = (tempBitIndex>>3)%MAX_BLOCK_SIZE;
			mask = 1<<(7-(tempBitIndex%8));
			//Always first set it to the dupBlock
			if (block_off < dupBlocks)
				dupBitVector[block_off][byte_off] = (dupBitVector[block_off][byte_off] | mask);
			else
				bitVector[block_off][byte_off] = (bitVector[block_off][byte_off] | mask);

			do {
				//find next curBitIndex till bit val = 0
				curBitIndex++;
				//check if it is marked as non-prime
				block_off = (curBitIndex>>3)/MAX_BLOCK_SIZE;
				byte_off = (curBitIndex>>3)%MAX_BLOCK_SIZE;
				mask = 1<<(7-(curBitIndex%8));
				//printf("new curBitIndex = %u\n",curBitIndex);
			}while ((mask & bitVector[block_off][byte_off]));
			//printf("===Outside loop ============\n");
			//Convert bitIndex to a value eg: 0==>5, 1==>7, 2==>11 and so on
			//TODO put this in an inline function
			value = 3*curBitIndex + 5 - (curBitIndex%2);
			value = p*value;

		}while(value <= maxNum);

		//Now copy the contents of dupBitVector back to the orig bitVector
		for (i = 0; i < dupBlocks; ++i) {
			//Doing this dirty way to improve copying by 4x
			//Assuming the MAX_BLOCK_SIZE is multiple of 4
			srcP = (unsigned int*)(dupBitVector[i]);
			destP = (unsigned int*)(bitVector[i]);
			temp = MAX_BLOCK_SIZE/4;
			for (j = 0; j < temp; ++j) {
				destP[j]=srcP[j];
			}

		}

		//Find the next p and value
		// first get index of current p
		curBitIndex = (p-5)/3;
		curBitIndex += ((p-5)%3 != 0 )?1:0;

		do {
			//find next curBitIndex till bit val = 0
			curBitIndex++;
			//check if it is marked as non-prime
			block_off = (curBitIndex>>3)/MAX_BLOCK_SIZE;
			byte_off = (curBitIndex>>3)%MAX_BLOCK_SIZE;
			mask = 1<<(7-(curBitIndex%8));
		}while ((mask & bitVector[block_off][byte_off]));

		//get p from curBitIndex
		p = 3*curBitIndex + 5 - (curBitIndex%2);
		//and compute value
		value = p*p;
	}

	//Do not free the bit vector,as it will be used in subsequent calls
	//Once all the prime numbers have been stored, then we can free the bitVector

	//But free the duplicate bit vector
	for (i = 0; i < dupBlocks; ++i) {
		free(dupBitVector[i]);
	}
	free(dupBitVector);
}

//This shld be called only after computePrime and maxNum here shld be <= to the one computed
//Supports only upto maxNum = 4gb
void convertBitVectorToPrime(unsigned int maxNum, FILE *fp, char delimiter){

	unsigned int curBitIndex=0, value;
	unsigned int block_off,byte_off;
	unsigned char mask;

	if (maxNum < 2)
		return;
	//By default 2, 3 are primes
	fprintf(fp,"2%c3",delimiter);

	value = 3*curBitIndex + 5 - (curBitIndex%2);

	//TODO We need to optimize disk access by writing large blocks
	//Large buffer for large maxNum
/*	if (maxNum > 99999999)
		buffSize = 10485760; //10 MB
	else if (maxNum > 99999)
		buffSize = 1048576;//1MB*/
	//Having large buffers is infact reducing the performance

	printf("Writing prime numbers to file...\n");

	while(value <= maxNum) {
		block_off = (curBitIndex>>3)/MAX_BLOCK_SIZE;
		byte_off = (curBitIndex>>3)%MAX_BLOCK_SIZE;
		mask = 1<<(7-(curBitIndex%8));
		if(!(mask & bitVector[block_off][byte_off])) {
			fprintf(fp,"%c%u",delimiter,value);
		}
		curBitIndex++;
		value = 3*curBitIndex + 5 - (curBitIndex%2);
	}
//	fprintf(fp,"\n");
}

int main(int argc, char **argv) {

	FILE *fp;
	char str[260];
	unsigned int maxNum;
	char delimiter = ' ';

	//A hack to use new line as the delimiter instead of space
	//This is useful if you want to find the number of prime numbers, we can do wc -l fname
	if (argc > 3)
		delimiter = '\n';


	//The maxNum and filename have been passed in command line
	if (argc > 2) {
		sscanf(argv[1],"%u",&maxNum);
		strcpy(str,argv[2]);
	} else {
		printf("Generate prime numbers upto: ");
		scanf("%u",&maxNum);

		fflush(stdin);
		getchar();//flush is not working
		printf("Enter the file name (full path) to store the prime numbers: ");
		scanf("%[^\n]",str);

	}
	fp=fopen(str,"w");
	if (fp == NULL)
		return -1;

	computePrimeNumbers(maxNum);
	convertBitVectorToPrime(maxNum,fp,delimiter);

	//freeing and closing
	freeBitVector();
	fclose(fp);

	printf("\nCompleted writing to file - %s\n",str);
	return 0;
}

