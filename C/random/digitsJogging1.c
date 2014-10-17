#include <stdio.h>
#define MAX_DIGITS 7

long tenpow(int n){
	if (n <= 0)
		return 1;
	return 10*tenpow(n-1);
}

int validateInputLength (int  digits) {
	if (digits < 2 || digits > MAX_DIGITS)
		return 0;
	return 1;
}

int getDigits(long value) {
	int digits=0;

	while(value>0) {
		digits++;
		value=value/10;
	}
	return digits;
}

int isDuplicateDigits(long val) {

	char number[10]={0,0,0,0,0,0,0,0,0,0};
	int temp, pos = 0;

	while(val>0){
		temp=val%10;
		if (number[temp] != 0)//implies duplicate digits
			return 1;
		number[temp]=1;
		val=val/10;
	}
	//0 is forbidden in val
	if (number[0] != 0)
		return 1;
	return 0;
}

int getDigitAt(int pos, long value, int noOfDigits){

	int count=0, temp=-1;

	while ((noOfDigits-count) > pos) {
		temp=value%10;
		value/=10;
		count++;
	}

	return temp;

}

long getNumber (long val) {
	int noOfDigits, i,pos;
	char isDigitVisited[MAX_DIGITS];
	long  maxValue;

	maxValue=tenpow(MAX_DIGITS)-1;
	//find no of digits
	noOfDigits=getDigits(val);

	//validate input
	if (!validateInputLength(noOfDigits))
		return -1;

	do {
		//check if it has duplicates
		if (isDuplicateDigits(val))
			continue;

		//initialize isDigitsVisited
		for (i = 0; i < MAX_DIGITS; ++i) {
			isDigitVisited[i]=0;
		}

		pos=noOfDigits-1;
		isDigitVisited[pos]++;


		//loop through the val by counting the value in each digit
		for (i = 0; i < noOfDigits; ++i) {

			//compute the new pos
			pos=(getDigitAt(pos,val,noOfDigits) + pos)%noOfDigits;

			isDigitVisited[pos]++;
			if (isDigitVisited[pos] > 1){
				break;
			}
		}
		//found the output which is greater than or equal to input
		if(pos==(noOfDigits-1) && i==(noOfDigits-1)) {
			return val;
		}
	}while(++val<=maxValue);

	return -1;

}

int main() {

	printf("%d \n", getNumber(123));
	return 0;
}
