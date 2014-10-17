/*
 * lz_encoder.c
 *
 *  Created on: Nov 16, 2009
 *      Author: Arun K
 */
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include<string.h>

/*
 * If there are any invalid chars in the text file, then those chars are replaced with space,
 * It wont result in error while encoding
 */

//SO total = 27 + 5 = 32
#define MAX_SYMBOLS 5

//max number of strings that can be combined in one Code word
#define MAX_LEN 100

//The codebook is a 16bit code book, hence len = 2^16
#define CODE_BOOK_LEN 16

//The text file can contain alphabets, space, comma, fullstop,
//question mark, exclamation and apostrophe only...

char symbols[MAX_SYMBOLS]={',','.','?','\n','`'};

char toLower (char ch){

	char ret;

	ret = ch-'A';
	if (ret>=0 && ret<26){
		return ret+'a';
	} else {
		return ch;
	}
}

//1 implies valid
int is_valid_char(char ch){
	int i;

	//Check if it is a character (lowercase)
	if (ch>='a' && ch <='z') {
		return 1; // implies valid
	}
	if (ch == ' '){
		return 1;
	}
	//Check if the char is one of the symbols and space
	for (i = 0; i < MAX_SYMBOLS; ++i) {
		if (ch == symbols[i])
			return 1;
	}
	return 0;
}

//Store all upper case to lower case...
void encode(FILE *fp, FILE *ofp){

	char new_char[2]={' ','\0'}, prev_char[MAX_LEN+1], wPlusC[MAX_LEN+2];
	int max_no_codes = 1<<CODE_BOOK_LEN;
	unsigned short int output;
	//This is used because we cant store negative num in output
	int ret_addr;

	//THe dict count cannot exceed the max no of codes
	int dict_count=27+MAX_SYMBOLS;

	if (fp == NULL || ofp == NULL)
		return;
	prev_char[0]=toLower(fgetc(fp));
	prev_char[1]='\0';

	//Text file is empty
	if (prev_char[0] == EOF) {
		printf("Input file is empty\n");
		return;
	}

	//Invalid char, no problem, just replace it with space
	if (!is_valid_char(prev_char[0])){
		prev_char[0]=' ';
	}
	//Now you have a prev char and wplusc and a new char
	while((new_char[0]=toLower(fgetc(fp))) !=  EOF){
		if (!is_valid_char(new_char[0])){
			new_char[0] = ' ';
		}
		strcpy(wPlusC,prev_char);
		strcat(wPlusC,new_char);


		//Check if we have the wPlusC in dict
		ret_addr = dict_get_address(wPlusC);
		//If the code is not in dict, we transmit the prev char
		if (ret_addr == -1){
			//Transmit the prev char
			ret_addr = dict_get_address(prev_char);

			//unnecessary, but for debugging
			if (ret_addr == -1) {
				printf("\nFATAL ERROR in program logic...\n");
				return;
			}
			strcpy(prev_char,new_char);

			//Add to dict only if dict count not exceed
			//Second cond is that we are crossing the max number of chars that can be grouped
			//Try to make it wPlusC dynamic...
			if (dict_count < max_no_codes && strlen(wPlusC)<MAX_LEN) {
				dict_insert(wPlusC);
				dict_count++;
			}

		} else {//dont transmit and make wplusc as prev char
			ret_addr = -1;
			strcpy(prev_char,wPlusC);
		}
		//Write to the encoded file
		if (ret_addr != -1){
			output = ret_addr;
			fwrite(&output,sizeof(unsigned short int),1,ofp);

		}
	}
	//Just transmit the prev_char which will be last char(s) of the file
	output = dict_get_address(prev_char);
	fwrite(&output,sizeof(unsigned short int),1,ofp);
	printf("\nSuccessfully encoded the given text file...\n");
}

void decode (FILE *fp, FILE *ofp){
	char **dict_arr;
	char *prev_data, *output, prevPlusRcd[MAX_LEN+1];
	int cur_dict_count = 0;
	int i, max_no_codes = 1<<CODE_BOOK_LEN;
	char temp[2]={' ','\0'};
	unsigned short int raw_data;

	//Allocate memory
	dict_arr = (char**)malloc(sizeof(char*)*(max_no_codes));
	for (i=0; i< max_no_codes; ++i)
	{
		dict_arr[i]=(char*)malloc(sizeof(char)*(MAX_LEN+1));
	}

	//populate the dict
	//Note it shld be in the same order as in encoder
	for (i = 0; i < 26; ++i) {
		if (i%2 == 1) {
			temp[0]='a'+i;
			strcpy(dict_arr[cur_dict_count++],temp);
		}
	}
	//Now store the even alphas to dict, this is to avoid bst skewness
	for (i = 0; i < 26; ++i) {
		if (i%2 == 0) {
			temp[0]='a'+i;
			strcpy(dict_arr[cur_dict_count++],temp);
		}
	}
	temp[0]=' ';
	strcpy(dict_arr[cur_dict_count++],temp);
	for (i = 0; i < MAX_SYMBOLS; ++i) {
		temp[0]=symbols[i];
		strcpy(dict_arr[cur_dict_count++],temp);
	}

	if (fp == NULL || ofp == NULL)
		return;

	fread(&raw_data,sizeof(unsigned short int),1,fp);

	//The first value has to be in dictionary...
	prev_data = dict_arr[raw_data];
	fprintf(ofp,"%s",prev_data);


	while (fread(&raw_data,sizeof(unsigned short int),1,fp) == 1){
		if (prev_data != NULL)
			strcpy(prevPlusRcd,prev_data);
		else
			prevPlusRcd[0]='\0';

		//The code not in dict, so add the prev data first char again...
		//The idea is, prevPlusRcd = prev+rcd[0] id it is in dict else it is prev+prev[0]
		if (raw_data >= cur_dict_count){
			temp[0]=prev_data[0];
			output = prevPlusRcd;
		} else {
			output = dict_arr[raw_data];
			temp[0]=output[0];
		}
		strcat(prevPlusRcd,temp);
		fprintf(ofp,"%s",output);

		//This condition is imp for large files, because we cud easily exhaust our codes
		if (cur_dict_count < max_no_codes) {
			strcpy(dict_arr[cur_dict_count++],prevPlusRcd);
		}
		prev_data=output;

	}
	printf("\nSuccessfully decoded the give compressed file\n\n");
	free(dict_arr);
}

int main(int argc, char **argv) {

	char file_to_encode[400];
	char output_file[400];
	FILE *fp=NULL, *ofp=NULL;
	int i;
	//TO store the initial dictionary
	char temp[2]={' ','\0'};

	printf("\n========LZ ENcoder Decoder =========\n\n");

	printf("(1) Encoding\n");
	printf("(2) Decoding\n");
	printf("Enter the choice:");
	scanf("%d",&i);getchar();
	if (i == 1) {
		printf("\nThe text file can contain alphabets, space, comma, fullstop, question mark, exclamation and apostrophe only...\n\n");
		printf("Enter Absolute path of the text file to encode: ");
		fflush(stdin);
		scanf("%399[^\n]",file_to_encode);
		getchar();
		fp = fopen(file_to_encode,"r");
		if (fp == NULL){
			printf("INVALID input FILENAME\n");
			return 1;
		}

		printf("Enter Absolute path of the output file (i.e. compressed file): ");
		fflush(stdin);
		scanf("%399[^\n]",output_file);
		getchar();
		ofp = fopen(output_file,"wb");
		if (ofp == NULL){
			printf("INVALID PATH\n");
			fclose(fp);
			return 1;
		}

		//Initialize the dictionary
		dict_initialize();

		//Populate the 32 symbols to dict
		//First store the odd alphabets to dict
		for (i = 0; i < 26; ++i) {
			if (i%2 == 1) {
				temp[0]='a'+i;
				dict_insert(temp);
			}
		}
		//Now store the even alphas to dict, this is to avoid bst skewness
		for (i = 0; i < 26; ++i) {
			if (i%2 == 0) {
				temp[0]='a'+i;
				dict_insert(temp);
			}
		}
		//Now store the symbols and space
		temp[0]=' ';
		dict_insert(temp);
		for (i = 0; i < MAX_SYMBOLS; ++i) {
			temp[0] = symbols[i];
			dict_insert(temp);
		}

		//Now call the encode
		encode(fp,ofp);
	} else{//Implies decoding
		printf("Enter Absolute path of the encoded file: ");
		fflush(stdin);
		//read it as file to decode
		scanf("%399[^\n]",file_to_encode);
		getchar();
		fp = fopen(file_to_encode,"rb");
		if (fp == NULL){
			printf("INVALID input FILENAME\n");
			return 1;
		}

		printf("Enter Absolute path of the output file (i.e. unzipped file): ");
		fflush(stdin);
		scanf("%399[^\n]",output_file);
		getchar();

		ofp = fopen(output_file,"w");
		if (ofp == NULL){
			printf("INVALID PATH\n");
			fclose(fp);
			return 1;
		}

		//Now call the encode
		decode(fp,ofp);
	}

	fclose(ofp);
	fclose(fp);

	printf("End of program, press any key...\n");
	getchar();

	return 0;

}
