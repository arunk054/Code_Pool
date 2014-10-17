#include<stdio.h>
#include<stdlib.h>

int getAbs(int val){
	if (val>=0)
		return val;
	val=~val;
	return ++val;

}
int sumOfDigits(int val) {
	int sum=0;
	val=getAbs(val);

	while(val>0) {
		sum+=val%10;
		val=val/10;
	}
	return sum;
}

int noOfCountEquals(int array[], int value, int noOfValues) {
	int i=0, returnValue=0;

	if (noOfValues <=0 || noOfValues>100)
		return -1;

	for (i = 0; i < noOfValues; ++i) {
		if (array[i] < -50000 || array[i] > 50000)
			continue;//skip this entry
		if (sumOfDigits(array[i]) == value)
			returnValue++;
	}

	return returnValue;

}

int* countEquals(int array[], int value, int noOfValues) {
	int *result,i=0, count=0;

	result=(int*)malloc(noOfCountEquals(array,value,noOfValues)*sizeof(int));

	if (noOfValues <=0 || noOfValues>100)
		return 0;

	for (i = 0; i < noOfValues; ++i) {
		if (array[i] < -50000 || array[i] > 50000)
			continue;//skip this entry
		if (sumOfDigits(array[i]) == value)
			result[count++]=array[i];
	}

	return result;
}

// You could use this sample code to test your C functions
// Please make appropriate changes to use this for C++.

// Following main function contains 3 representative test cases

int main()
{
		int i,j,k;
		int array[] = {23, 9, 34, 44, 45, 36, 54, 11, 23};
		int value = 9;
		int noOfValues = 9;

		int* result = countEquals(array, value, noOfValues);
		int count = noOfCountEquals(array, value, noOfValues);

		printf("countEquals : ");

		for(i=0;i<count;i++)
			printf ("%d, ",result[i]);

		printf ("\ncount : %d\n",count);
}
