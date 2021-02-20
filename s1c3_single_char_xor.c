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

int main(int argc, char* argv[]){


	if(argc <2){
		perror("Invalid Argument\n");
		exit(1);
	}
	char* value=NULL;
	value =  malloc(sizeof(char) * strlen(argv[1]));
	value = convert_hex_to_ascii(argv[1]);
        float best_score = -1;
	char res ;
	for(int i=0; i < 256; i++){
		float score = 0;

		for(int j=0; j <(int)strlen(value); j++){
			char xor = value[j] ^ (char)i;
	        	switch(tolower(xor)){
			case 'a':
				score += 0.0651738;
			case 'b':
				score += 0.0124248;
			case 'c':
				score += 0.0217339;
			case 'd':
				score += 0.0349835;
			case 'e':
				score += 0.1041442;
			case 'f':
				score += 0.0197881;
		        case 'g':
				score += 0.0158610;
			case 'h':
				score += 0.0492888;
			case 'i':
				score += 0.0558094;
			case 'j':
				score += 0.0009033;
			case 'k':
				score += 0.0050529;
			case 'l':
				score += 0.0331490;
			case 'm':
				score += 0.0202124;
			case 'n':
				score += 0.0564513;
			case 'o':
				score += 0.0596302;
			case 'p':
				score += 0.0137645;
			case 'q':
				score += 0.0008606;
			case 'r':
				score += 0.0497563;
			case 's':
				score += 0.0515760;
			case 't':
				score += 0.0729357;
			case 'u':
				score += 0.0225134;
			case 'v':
				score += 0.0082903;
			case 'w':
				score += 0.0171272;
			case 'x':
				score += 0.0013692;
			case 'y':
				score += 0.0145984;
			case 'z':
				score += 0.0007836;
			case ' ':
				score += 0.1918182;
				break;
			}

		}
        	if( best_score <= score){
        		best_score = score;
			res = i;
		}

	}
	for(int i=0; i < (int)strlen(value); i++){
		printf("%c", value[i] ^  res);
	}
	return 0;
}
