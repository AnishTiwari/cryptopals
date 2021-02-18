#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <limits.h>


char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int* char_to_bin(char c, int* bin) {
	int i;
	int idx = 0;
	for(i = 7; i >= 0; i--){
		bin[idx++] = ( unsigned int )( ( c & (1 << i) ) ? 1 : 0);
	}
	return bin;
}


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

int binary_to_decimal(char* n)
{
	char* num = n;
	int dec_value = 0;
	int base = 1;
 	int len = strlen(num);
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}
	return dec_value;
}

char* string_to_b64(char* ascii_string, char* b64_arr){
	int no_padding_char = ((strlen(ascii_string) % 3) > 0) ? 3 - (strlen(ascii_string) % 3) :0;
	int idx = 0;
	char all_bin[(strlen(ascii_string) * 8)+6] ;
	while(*ascii_string){
		int bin[8];
		char c = *(ascii_string++);
		int* binary = char_to_bin(c, bin);
		for(int i=0; i < 8; i++){
			all_bin[idx++] = binary[i] + '0';
		}
	}
	int bin_pad = 0;
	((idx % 6) != 0) ? bin_pad = idx%6    : bin_pad ;

	for(int i=0; i < bin_pad; i++){
		all_bin[idx++] = '0';
	}
	int final_idx = 0;
	char final_res [idx] ;
	for(int i=0; i < idx; i+=6){
		char string[7];
		strncpy(string, all_bin+i, 6);
		string[6] = '\0';

		final_res[final_idx++] = (char)char_set[binary_to_decimal(string)];
	}
	b64_arr = final_res;

	int i;
	for(i=0; i < no_padding_char; i++){
		b64_arr[final_idx+i] = '=';
	}
	b64_arr[final_idx+i] = '\0';
	return b64_arr;
}

int main(int argc, char* args[]){

	if(argc < 1){
		perror("Invalid Arg");
		exit(1);
	}

	char* hex_string =NULL;
	hex_string = malloc(sizeof(char) *strlen(args[1]));
	hex_string = args[1];
	printf("%s\n", hex_string);

	char* ascii_string = convert_hex_to_ascii(hex_string);

	char* b64 = NULL;
	b64 = malloc(sizeof(char) * strlen(ascii_string));
	b64 = string_to_b64(ascii_string, b64);
	printf("%s",b64);
	return 0;

}
