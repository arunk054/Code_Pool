/*
 * testcase.c
 *
 *  Created on: Aug 20, 2009
 *      Author: root
 */
#include "sort.h"

#define MAX_COUNT 10000000

int main(int argc, char **argv) {

	int i,*arr,count=MAX_COUNT;
	int max_val=10000;
	char ch,quiet=0;
	clock_t c1,c2;

	if (argc > 1)
		quiet=1;



	if (!quiet){
		printf("\nEnter how many numbers do you want to sort (10 -1000000000):");
		scanf("%d",&count);
		printf("\nGenerating %d random numbers, please wait...\n\n",count);
		while(fgetc(stdin)!='\n');
	}

	arr=(int*)malloc(count*sizeof(int));
	for (i = 0; i < count; ++i) {
		arr[i]=rand()%max_val;
	}

	if (!quiet){
		printf("Do you want to print the un-sorted array (y/n):");
		scanf("%c",&ch);
		if (ch=='y' || ch=='Y') {
			for (i = 0; i < count; ++i) {
				printf("%d\n",arr[i]);
			}
		}
		while(fgetc(stdin)!='\n');
		printf("\nSorting %d elements in the array...\n", count);
	}

	c1=clock();
	sort(arr,count);
	c2=clock();

	if (!quiet) {
		printf("Completed execution of the sort method...\n");
	}

	printf ("\nTime taken to sort %d numbers is %.2f seconds\n\n",count,(c2-c1)/((double)(CLOCKS_PER_SEC)));
	if (!quiet) {
		printf("Do you want to print the sorted array (y/n):");
		scanf("%c",&ch);
		if (ch=='y' || ch=='Y') {
			for (i = 0; i < count; ++i) {
				printf("%d\n",arr[i]);
			}
		}
	}
	printf("-------END OF PROGRAM---------\n\n");
}

