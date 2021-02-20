#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int BUFFER = 200;
int main(int argc, char* args[]){

	printf("%s\n", args[1]);
	if(argc != 3){
		perror("Invalid Arguments\n");
		exit(1);
	}
	char* key = NULL;
	key = malloc(sizeof(char) * strlen(args[2]));
	key = args[2];
	FILE *fp = NULL;
	fp = fopen(args[1], "r");
	if(fp == NULL){
		perror("Invalid file argument\n");
		exit(1);
	}

	char curr_char;
	char *xor_rep =NULL;
	xor_rep = malloc(sizeof(char) * BUFFER);
	int idx = 0;
	int i=0;
	while ((curr_char = fgetc(fp)) != EOF)
	{
		xor_rep[idx++] = curr_char ^ key[i];
		(i == (int)strlen(key)-1) ?i = 0:i++;
	}
	xor_rep[idx] = '\0';
	for(int i = 0; i < idx-1; i++){
		printf("%x",xor_rep[i]);
	}
	return 0;
}
