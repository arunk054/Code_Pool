
int string_compare (char *string1, char *string2, int size) {
	int count = 0;

	while (count < size && string1[count]!='\0' && string2[count]!='\0'){
		if (string1[count] == string2[count]) {
			count++;
			continue;
		}
		if (string1[count]-string2[count] < 0)
			return -1;
		else
			return 1;
	}
	if (count == size)
		return 0;
	else if (string1[count]=='\0')
		return -1;
	else
		return 1;
}

int main(int argc, char **argv) {
	printf ("%d\n",string_compare("123", "1234", 3));
}
