#include <stdlib.h>

int isVowel(char c) {
	if (c < 97)
		c+=32;//convert to lower
	switch(c) {
	case 'a':
		return 1;
	case 'e':
		return 1;
	case 'i':
		return 1;
	case 'o':
		return 1;
	case 'u':
		return 1;
	default:
		return 0;
	}
}
char* removeVowels(char *sen) {
	char *temp=sen, *returnVal;
	int count = 0;

	if (sen == NULL)
		return NULL;

	//find size of sen including \0
	while (temp[count++] != '\0');

	//alloc memory
	returnVal = (char*)malloc(count*sizeof(char));

	//again RESET TEMP, COUNT
	temp = sen;count =0;

	while (temp[0] != '\0') {
		if (!isVowel(temp[0]))
			returnVal[count++] = temp[0];
		temp++;
	}
	returnVal[count]='\0';

	return returnVal;
}

int main(int argc, char **argv) {
	printf ("%s", removeVowels("This is India dsaliiO sdEa 0q9243*@o#pp $%A( lkhasdf "));
	return 0;
}


