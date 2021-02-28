#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char* take_n_bits(int start,int end, unsigned char* arr, int delimit, int idx){
	unsigned char* string = NULL;
	if(delimit){
		start +=idx;
		string = malloc(sizeof(unsigned char) * 321);
		int j = 0;
		/* printf("start is %d\n", start); */
		for(int i = start; arr[i] !=  '\n'; i++)
			string[j++] = arr[i];
		string[j] = '\0';

	}

	else
	{
		string = malloc(sizeof(unsigned char) * (end - start)+1);
		int j = 0;
		for(int i = start; i < end; i++)
			string[j++] = arr[i];
		string[j] = '\0';
	}
	return string;
}

unsigned char* file_read(char* filename){

	FILE *f = fopen(filename, "r");
	fseek(f, 0L, SEEK_END);
	unsigned int size = ftell(f);
	fseek(f, 0L, SEEK_SET);
	unsigned char* array = malloc(sizeof(unsigned char) * (size+1));
	if(!array)
		printf("file malloc:\n"),exit(-1);
	unsigned int read_size = fread(array, 1, size, f)+1;
	array[read_size] = '\0';
	fclose(f);
	return array;
}

int main(){
	unsigned char* filearr = file_read("s1c8.txt");
        /* 32 bytes sized blocks */
	int idx = 0;
	for  (int block =0; block < (int)strlen((const char*)filearr); block+=320)
	{	unsigned char* block_char = NULL;
		block_char = take_n_bits(block, block+320, filearr,1, idx);
		/* printf("BLOCK IS %s %d \n\n", block_char,block); */
		for(int i=0; i < (int)strlen((char *)block_char); i+=32){
			unsigned char* str1 = take_n_bits(i, i+32, block_char,0,idx);
			for(int j=i+32; j <= (int)strlen((const char*)block_char);j +=32){
				unsigned char* str2 = take_n_bits(j, j+32, block_char,0,idx);
				/* printf("%s %s \n", str1, str2); */
				if (strcmp((const char *)str1,(const char *)str2) == 0)
				{	printf("\n\n%s - %s at block %d\n\n%s",str1,str2,idx+1,block_char);
					return 0;
				}
				free(str2);
			}
			free(str1);
		}
		idx++;
		free(block_char);
	}
	free(filearr);
	return 0;
}
