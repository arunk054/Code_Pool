#include<stdio.h>

#define MAX_DIGITS 5
#define MIN_VALUE 11

long tenpow(int n){
	if (n <= 0)
		return 1;
	return 10*tenpow(n-1);
}

long fact (int n) {
	if (n<=0)
		return 1;
	return n*fact(n-1);
}

int validateInput (long val) {
	if (val < MIN_VALUE || val >= tenpow(MAX_DIGITS))
		return 0;

	return 1;
}

long findVal (char number[], int len) {
	int var=0;
	long returnVal=0;

	for (var = len-1; var >= 0; --var) {
		returnVal += number[var]*tenpow(len-1-var);
	}
	return returnVal;
}

void getAllCombinations (long val) {

	char number[MAX_DIGITS];
	int var=0, count=MAX_DIGITS-1, len=0, i,max;
	long temp=val;

	while (temp>0 && count >= 0) {
		number[count--] = temp%10;
		temp  = temp / 10;
	}

	//shifting the elements in number to begin from 0
	for (var = count+1; var < MAX_DIGITS; ++var) {
		number[len]=number[var];
		if(number[len] < 1)
			return -1;
		len++;
	}
	max=fact(len);

	for (i = 0; i < max; ++i) {
		//swap i and i+1 mod len
		temp=number[i%len];
		number[i%len]=number[(i+1)%len];
		number[(i+1)%len]=temp;
		printf("%ld\n",findVal(number,len));
	}
}



int getNoOfPairs(long val){
	char number[MAX_DIGITS];
	int var=0, count=0, len=0;
	long temp=val;

	if (!validateInput(val))
		return -1;

}


int main(int argc, char **argv) {
	getAllCombinations(1234);
	printf("%d",fact(1));
	return 0;
}
