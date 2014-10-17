#include <stdio.h>
#include <stdlib.h>

#define START_YEAR 0
#define INVALID "invalid"
int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char days[7][10] = {"monday", "tuesday", "wednesday","thursday","friday","saturday","sunday"};
int referenceDays[4] = {5,4,2,0};

int extractCentury (int year) {
	int first, second;

	if (year < START_YEAR || year > 9999) {
		return -1;
	}
	first = year / 1000;
	second = (year%1000)/100;
	return first*10 + second;
}

int extractYearLastTwo (int year, int century) {
	return year - (century * 100);
}

char validateMonth (int month) {
	if (month < 1 || month > 12)
		return 0;
	return 1;
}

char validateDate (int date, int month) {
	if (date < 1 || date > months[month-1])
		return 0;
	return 1;
}

int isLeapYear (int year) {
	if (year%4 == 0 && (year%100 != 0 || year%400 == 0))
		return 1;
	return 0;
}

char* determineDay (int date, int month, int year) {

	int century = 0, referenceDay = 0,i=0, offsetDays=0;

	century = extractCentury (year);
	if (century == -1)
		return INVALID;

	if (isLeapYear (year)) {
		months[1] = 29;
	} else {
		months[1] = 28;
	}

	year = extractYearLastTwo (year, century);

	if (!validateMonth (month))
		return INVALID;

	if (!validateDate (date, month))
		return INVALID;

	//referenceDay will be the day of 1st jan in that year
	referenceDay = referenceDays[century%4] + year;
	referenceDay += ((year-1)/4); // no of leap years passed

	if ((century%4 == 0) && year != 0) // if reference century is leap year
		referenceDay+=1;

//printf ("%d\n", referenceDay);
	//Find total days from jan 1 to 1st of given month
	for (i = 0; i < month-1; ++i) {
		offsetDays+=months[i];
	}

	offsetDays = (offsetDays+date-1) % 7;

	return days[(referenceDay + offsetDays) % 7];
}

int main(int argc, char **argv) {
printf("%s\n", determineDay(12,5,9999));
}
