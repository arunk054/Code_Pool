#include <stdio.h>

void trimWord(char* word){
	//todo
}

int firstAndOnlyIndex(char *line, char *word) {

	int count=0, noOfOccur=0, len=-1, index=-1;
	char *temp = word;

	//Find the length of the word
	while (word[++len]!='\0');

	printf ("len = %d\n", len);

	while (line[count] != '\0') {
		if (temp[0] == line[count]) {
			printf ("match of %c count %d\n", temp[0], count);
			temp++;
		} else {
			temp = word;
		}
		//if we have reached the end of word
		//and if the next char in the line is space or \0
		//and if the word in the line is really a word
		if (temp[0] == '\0' && (line[count+1]==' ' || line[count+1]=='\0')
				&& ((count-len)==-1 || line[count-len] == ' ')) {
			printf("found pattern %d\n", count);
			noOfOccur++;
//			if (noOfOccur > 1)
				//return -1;//more than one occurrence

			temp=word;
			index=count-(len-1);
			//return index;
		}
		count++;
	}
	return index;
}

int findEndOfWord(char *line, int index){

	while(line[index] != ' ' && line[index] != '\0'){
		index++;
	}
	return index-1;
}

int findDistanceWithNormalSpace(char *line, int index1, int index2) {
	int isPrevSpace=0;
	int count = 0;

	while (index1 < index2){
		if (line[index1] != ' '){
			count++;
			isPrevSpace = 0;
		} else if (!isPrevSpace) {
			count++;
			isPrevSpace=1;
		}
		index1++;
	}
	return count;
}

int getStringDistanceWithSpace(char *line, char *word1, char*word2) {
	int index1, index2;
	index1 = firstAndOnlyIndex(line, word1);

	if (index1 == -1)
		return -1;

	index2 = firstAndOnlyIndex(line, word2);

	if (index2 == -1)
		return -1;

	//not sure what to do if word1=word2, whether return -1 or 0
	if ((index2-index1) <=0 )
		return -1;


	index1 = findEndOfWord(line, index1);

	return (index2-index1)-1;
}

int getStringDistanceWithNormalSpace(char *line, char *word1, char*word2){

	int index1, index2;
	index1 = firstAndOnlyIndex(line, word1);

	if (index1 == -1)
		return -1;

	index2 = firstAndOnlyIndex(line, word2);

	if (index2 == -1)
		return -1;

	//not sure what to do if word1=word2, whether return -1 or 0
	if ((index2-index1) <=0 )
		return -1;


	index1 = findEndOfWord(line, index1);

	return findDistanceWithNormalSpace(line, index1+1, index2);
}

int main(int argc, char **argv) {
	printf ("%d\n", getStringDistanceWithSpace("ewrwer oprew sdfk mmnxcv sdsad xz mmm kklo qwe uirur weqe e eqw eq w q q q qqqq erere", "w", "q"));
//	printf ("%d\n", getStringDistanceWithNormalSpace("how areare  he you are  abds  kjc  hel", "are", "hel"));
	//printf ("%d\n", getStringDistanceWithSpace("abc dwef w ref q fig", "w", "q"));
	return 0;
}

