#include <stdio.h>
#define MAX_DIGITS 7

long tenpow(int n){
	if (n <= 0)
		return 1;
	return 10*tenpow(n-1);
}

int validateInputLength (long val) {
	if (val < tenpow(1) || val >= tenpow(MAX_DIGITS))
		return 0;
	return 1;
}

long findVal (char number[], int len) {
	int var=0, count=0;
	long returnVal=0;

	for (var = len-1, count=0; var >= 0; --var, ++count) {
		returnVal += number[var]*tenpow(count);
	}
	return returnVal;
}

int isDuplicates (char number[], int len) {
	int i,j, count=0;

	for (i = 0; i < len; ++i) {
		for (j=0; j < len; ++j) {
			if (i!=j && number[i] == number[j])
				count++;
		}
	}
	return count;
}

int incrementDigit(char number[], int *len) {
	int var=0;
	int length = *len;

	if (length >= MAX_DIGITS) {
		return 0;
	}
	for (var = 0; var < length+1; ++var) {
		number[var]=1;//because the lowest number is 1111...
	}
	*len=*len + 1;
	return 1;

}

int incrementValue(char number[], int *len) {
	int var = 0;
	int length = *len;

	for (var = length-1; var >= 0; --var) {
		if (number[var]<9) {
			number[var]++;
			return 1;
		} else if (var == 0){
			//implies the first digit
			return incrementDigit(number, len);
		} else if (number[var] >= 9) {
			number[var] = 1;
		}
	}
}

long getNumber (long val) {

	char number[MAX_DIGITS];
	long temp=val,bestValue=-1;
	int count = MAX_DIGITS-1, var=0, len=0,j=0, prevDup=0;

	if (!validateInputLength(val))
		return -1;

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

	//now we have each digit in number[] and the length in len
	do {
		for (var = 0; var < len; ++var) {
			if ((number[var]+var)%len != (var+1)%len)
				break;
		}
		if (var == len) {
			if ((count=isDuplicates(number, len))) {
				if (bestValue==-1 || prevDup>count) {
					bestValue=findVal(number,len);
					prevDup=count;
				}
				if (!incrementValue(number, &len))
					return bestValue;
			} else //no duplicates and the required number
				return findVal(number,len);
		} else {
			number[var]+=len-(number[var]%len) + 1;
			for (j = var+1; j < len; ++j) {
				number[j] = 1;
			}
			if (number[var] > 9) {
				if (var>0 && number[var-1]<9) {
					number[var]=1;
					number[var-1]++;
				} else if (!incrementDigit(number, &len))	//already reached the greatest number
					return bestValue;
			}
		}
		//printf ("%ld\n",findVal(number,len));
	} while (len <= MAX_DIGITS);
	return bestValue;
}

int main() {

	printf("%ld \n", getNumber(88888));
	return 0;
}
