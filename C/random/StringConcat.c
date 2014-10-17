//help@devsquare.com

char* concat (char* string1, char *string2) {
	char *returnVal;
	int count1 = -1, count2=-1, i;

	while(string1[++count1]!='\0');
	while(string2[++count2]!='\0');
	returnVal=(char*)malloc(count1+count2+1);

	for (i=0;i<count1;++i)
		returnVal[i]=string1[i];
	for (i=0;i<count2;++i)
		returnVal[i+count1]=string2[i];
	returnVal[count1+count2]='\0';
	return returnVal;
}
int main(int argc, char **argv) {
	printf("%s\n",concat("Good","Information"));
	return 0;
}
