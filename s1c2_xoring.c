#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void bin_to_hex(char* binary, char* result){

	int bin_i;
	sscanf(binary, "%d", &bin_i);
	int hexConstant[] = {0, 1, 10, 11, 100, 101, 110, 111, 1000,
			     1001, 1010, 1011, 1100, 1101, 1110, 1111};

	char hex[2];
	int index, i, digit;
	index = 0;
	while(bin_i!=0)
	{
		digit = bin_i % 10000;

		for(i=0; i<16; i++)
		{
			if(hexConstant[i] == digit)
			{
				if(i<10)
				{
					hex[index] = (char)(i + 48);
				}
				else
				{
					hex[index] = (char)((i-10) + 65);
				}

				index++;
				break;
			}
		}
		bin_i /= 10000;
	}
	hex[index] = '\0';

	memcpy(result, hex, 2);
}

char* hex_to_bin(char hex){

	switch(hex)
        {
	case '0':
                return "0000";
                break;
	case '1':
                return  "0001";
                break;
	case '2':
                return "0010";
                break;
	case '3':
		return  "0011";
                break;
	case '4':
                return "0100";
                break;
	case '5':
                return  "0101";
                break;
	case '6':
                return "0110";
                break;
	case '7':
                return "0111";
                break;
	case '8':
                return  "1000";
                break;
	case '9':
                return "1001";
                break;
	case 'a':
	case 'A':
                return "1010";
                break;
	case 'b':
	case 'B':
                return "1011";
                break;
	case 'c':
	case 'C':
                return  "1100";
                break;
	case 'd':
	case 'D':
                return "1101";
                break;
	case 'e':
	case 'E':
                return "1110";
                break;
	case 'f':
	case 'F':
		return  "1111";
                break;
	default:
                printf(":/");
		return "";
        }
	return "";
}

char* xored(char* buff_1, char* buff_2){


	char* xored_string = NULL;
	xored_string = malloc(sizeof(char) * strlen(buff_1));

	for(int i=0; i < (int)strlen(buff_1); i++){
		char* val_1 = NULL;
		val_1 = malloc(sizeof(char)* 5);
		val_1 = hex_to_bin(buff_1[i]);
		char* val_2 = NULL;
		val_2 = malloc(sizeof(char) * 5);
		val_2 = hex_to_bin(buff_2[i]);
		char xored[5];
		for(int j=0; j < 4; j++){

			xored[j] = 0;
			xored[j] = (val_1[j] ^ val_2[j]) +'0';
		}
		xored[4] = '\0';
        	char hexas[2];
		bin_to_hex(xored, hexas);
		strcat(xored_string, hexas);
	}

	return xored_string;
}

int main(int argc, char* argv[]){

	if(argc < 3){
		perror("Invalid Args\n");
		exit(1);
	}

	char* buff_1 = NULL;
	buff_1 = malloc(sizeof(char) * strlen(argv[1]));
	buff_1 = argv[1];
	char* buff_2 = NULL;
	buff_2 = malloc(sizeof(char) * strlen(argv[2]));
	buff_2 = argv[2];
	if(strlen(buff_1 ) != strlen(buff_2)){
		printf("Buffer lenght mismatch\n");
		exit(1);
	}
	char* xored_string = xored(buff_1, buff_2);

	printf("%s",xored_string);
	return 0;
}
