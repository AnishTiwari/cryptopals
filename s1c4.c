#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int hex_to_int(char c)
{
	if (c >= 97)
		c = c - 32;
	int first = c / 16 - 3;
	int second = c % 16;
	int result = first * 10 + second;
	if (result > 9) result--;
	return result;
}

char* convert_hex_to_ascii(char* hex_string){

	char* ascii_string = NULL;
	ascii_string = malloc(sizeof(char) * (strlen(hex_string)/2));

	int idx = 0;
	while(*hex_string){

		char high = *(hex_string++);
		int high_val = hex_to_int(high)*16;
		char low = *(hex_string++);
		int low_val = hex_to_int(low);
   		int value = high_val+low_val;
		ascii_string[idx++] = (char)value;
	}
	return ascii_string;
}

int main(){
	FILE *fp = fopen("s1c4.txt", "r");
	if(fp == NULL){
		perror("No input file provided\n");
		exit(1);
	}

	char* file_line=NULL;
	file_line =  malloc(sizeof(char) * 61);
	char* string =NULL;
	string = malloc(sizeof(char) *61);
	char res ;
	char* value = NULL;
	value = malloc(sizeof(char) * 61);
		float best_score = -1;

	while(fscanf(fp, "%s\n", file_line) == 1){
		value = convert_hex_to_ascii(file_line);
		for(int i=0; i < 256; i++){
			float score = 0;

			for(int j=0; j <(int)strlen(value); j++){
				char xor = value[j] ^ (char)i;
				switch(tolower(xor)){
				case 'a':
					score += 0.0651738;
				case 'd':
					score += 0.0349835;
				case 'e':
					score += 0.1041442;
				case 'h':
					score += 0.0492888;
				case 'i':
					score += 0.0558094;
				case 'l':
					score += 0.0331490;
				case 'n':
					score += 0.0564513;
				case 'o':
					score += 0.0596302;
				case 'r':
					score += 0.0497563;
				case 's':
					score += 0.0515760;
				case 't':
					score += 0.0729357;
				case 'u':
					score += 0.0225134;
				case ' ':
					score += 0.1918182;
					break;
				}

			}

			if( best_score < score){
				best_score = score;
				res = i;
				memcpy(string , value, 61);
			}
		}
	}
			for(int i=0; i < (int)strlen(string); i++){
			printf("%c", string[i] ^  res
				);
		}

	return 0;
}
