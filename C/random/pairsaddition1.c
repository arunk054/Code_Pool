#include<stdio.h>
#include<stdlib.h>

#define MIN_VALUE 10
#define MAX_VALUE 100000

char *flags;

int getAbs(int val){
	if (val>=0)
		return val;
	val=~val;
	return ++val;

}

int tenpow(int n){
	if (n <= 0)
		return 1;
	return 10*tenpow(n-1);
}

int getDigits(int value) {
	int digits=0;

	while(value>0) {
		digits++;
		value=value/10;
	}
	return digits;
}

int isDigitsMatch(int p1, int p2, int tolerance) {

	//assuming p1 p2 differ not more than 1 digit
	int numbersP1[10] = {0,0,0,0,0,0,0,0,0,0}, numbersP2[10] = {0,0,0,0,0,0,0,0,0,0};
	int diff=0,i;

	while(p1>0){
		numbersP1[p1%10]++;
		p1=p1/10;
	}
	while(p2>0){
		numbersP2[p2%10]++;
		p2=p2/10;
	}
	for (i = 0; i < 10; ++i) {
		//one of the digits did not match
		if (numbersP1[i] != numbersP2[i]) {
			if (tolerance<=0)//no tolerance to mismatch
				return 0;
			diff+=getAbs(numbersP1[i]-numbersP2[i]);
			if (diff>tolerance)
				return 0;
		}
	}
	return 1;
}

int isApplicable(int sum, int value){

	if (sum >= value)
		return 0;
	else
		return 1;

}

int isPairs(int p1, int p2, int value) {

	int sum = p1+p2;

	sum=value-sum;

	//check if sum + p1 satisfies
	if (!flags[sum+p1] && !flags[p2] && isDigitsMatch(p1,sum+p1,1)) {
		//printf("%d %d\n",sum+p1, p2);
		flags[sum+p1]=1;
		flags[p2]=1;
		return 1;
	}


	//check if sum+p2 satis.fies
	if (!flags[sum+p2] && !flags[p1] && isDigitsMatch(p2,sum+p2,1)) {
		//printf("%d %d\n",sum+p2, p1);
		flags[sum+p2]=1;
		flags[p1]=1;
		return 1;
	}
	return 0;

}

int getNoOfCombi(int value) {
	int digits, min, max,i,j, noOfPairs=0;

	if (value < MIN_VALUE || value > MAX_VALUE)
		return -1;

	//find digits in value
	digits = getDigits(value);

	//loop from min value of n-1 digits to its max value
	min=tenpow(digits-2);
	max=tenpow(digits-1)-1;
	flags=(char*)calloc((value==MAX_VALUE)?MAX_VALUE:tenpow(digits),1);

	for (i = min; i <= max; ++i) {
		for (j = i; j <=max; ++j) {
			//is pair applicable and isDigitsMatch
			if(!isApplicable(i+j,value) || !isDigitsMatch(i,j,0))
				continue;

			//Find Pairs
			if (isPairs(i,j,value)) {
				//printf ("i j %d %d\n", i, j);
				noOfPairs++;
			}
		}
	}
	free(flags);
	return noOfPairs;
}


int main()
{
	//TestCase 1
	{
		printf("TestCase 1\n");
		int value=7567;
		int noOfCombi = getNoOfCombi(value);
		printf ("\n\n No. of Combinations : %d",noOfCombi);
	}
	//TestCase 2
	{
		printf("\nTestCase 2\n");
		int value=256;
		int noOfCombi = getNoOfCombi(value);
		printf ("\n\n No. of Combinations : %d",noOfCombi);
	}
	//TestCase 3
	{
		printf("\nTestCase 3\n");
		int value=8;
		int noOfCombi = getNoOfCombi(value);
		printf ("\n\n No. of Combinations : %d",noOfCombi);
	}
}

