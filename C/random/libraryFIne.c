#include <stdio.h>

double fineCalculation (double bookCost, int noOfDays) {
	float percentFine = 0;//no fine

	if (noOfDays < 1)
		return 0;
	else if (noOfDays == 1)
		percentFine = 0.02;
	else if (noOfDays==2)
		percentFine=0.04;
	else
		percentFine=0.05;

	return (percentFine*bookCost);
}

int main(int argc, char **argv) {
	printf("%f\n", fineCalculation(43565.000000,0));
	return 0;
}
