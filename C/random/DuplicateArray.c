
int noOfOccurrence(int array[], int value, int length) {
	int i=0, retVal=0;

	for (i = 0; i < length; ++i) {
		if(array[i]==value)
			retVal++;
	}

	return retVal;
}

void swap(int *a, int*b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

int* removeDuplicateOptimized(int array[], int length){
	int i=0, noOfDuplicates=0,j;

	for (i = 0; i < length; ++i) {
		for (j=0; j<i;++j){
			if(array[i]==array[j]){
				swap(&array[noOfDuplicates], &array[i]);
				noOfDuplicates++;
				break;
			}
		}
	}
	return array+noOfDuplicates;
}

void shiftArrayLeft(int array[], int index, int noOfDuplicates) {
	int temp=array[index],i;

	for (i=index-1; i >=noOfDuplicates; --i) {
		array[i+1]=array[i];
	}
	array[noOfDuplicates]=temp;
}

int* removeDuplicate(int array[], int length){
	int i=0, noOfDuplicates=0,j;

	for (i = 0; i < length; ++i) {
		for (j=0; j<i;++j){
			if(array[i]==array[j]){
				shiftArrayLeft(array, i, noOfDuplicates);
				noOfDuplicates++;
				break;
			}
		}
	}
	return array+noOfDuplicates;
}

int main(int argc, char **argv) {
	int array[] = {0,1,2,6,9,3,5,2,5,2,6,9};
			int value = 2,i=0;
			int length = 12;
			int count = noOfOccurrence(array, value, length);
			int* output = removeDuplicate(array, length);
			printf ("\n\n No of Occurancess : %d",count);
			printf ("\n\n FINAL ARRAY : ");
			for(i=0;i<7;i++)
				printf ("%d, ",output[i]);
	return 0;
}
