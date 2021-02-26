#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_KEYSIZE 40
#define MIN_KEYSIZE 2

typedef struct pair p;
typedef p* p_t;

struct pair{
	int keysize;
	float score;
};

int* char_to_bin(char c, int* bin) {
	int i;
	int idx = 0;
	for(i = 7; i >= 0; i--){
		bin[idx++] = ( unsigned int )( ( c & (1 << i) ) ? 1 : 0);
	}
	return bin;
}

char* file_read(char* filename){

	FILE *f = fopen(filename, "r");
	fseek(f, 0L, SEEK_END);
	unsigned int size = ftell(f);
	fseek(f, 0L, SEEK_SET);
	char* array = malloc(sizeof(char)* size +1);
	unsigned int read_size = fread(array, 1, size, f)+1;
	array[read_size] =0;
	fclose(f);
	return array;
}


char* take_n_bits(int start,int end, char* arr){
	char* string = malloc(sizeof(char) * (end-start)+1);
	int j = 0;
	for(int i = start; i < end; i++){
		string[j++] = arr[i];
	}
	return string;
}

int calc_hamming_dist(char* str1, char* str2){

	if(strlen(str1) != strlen(str2)) {
		printf("%ld %ld\n",strlen(str1), strlen(str2));
		perror("Hamming Distance: length mismatch\n");
		exit(1);
	}
	int dist = 0;
	while(*str1){
		int* str1_b = malloc(sizeof(int) * 8);
		int* str2_b = malloc(sizeof(int) * 8);
		char_to_bin(*str1, str1_b);
		char_to_bin(*str2, str2_b);
		for(int i=0; i < 8; i++){
			if(str1_b[i] ^ str2_b[i])
				dist++;
		}
		str1++;
		str2++;
	}
	return dist;
}

int compare (const void * a, const void * b)
{
	const p *A = a;
	const p *B = b;
	return ( B->score <A->score?1:-1 );
}

void best_ans(){

	FILE *fp = fopen("s1c6_converted.txt", "r");
	if(fp == NULL){
		perror("No input file provided\n");
		exit(1);
	}

	char* file_line=NULL;
	file_line =  malloc(sizeof(char) * 200);
	char res ='!';
	char* value = NULL;
	float best_score = -1;
	while(fscanf(fp, "%s\n", file_line) == 1){
		value = malloc(sizeof(char) * strlen(file_line));
		value = (file_line);
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
			if( best_score <= score){
				best_score = score;
				res = i;
			}
		}
	}
	printf("%c",  res);

}

int main(int argc, char* argv[]){

	if(argc != 2){
		perror("Invalid Args\n");
		exit(1);
	}

	printf("%d\n", calc_hamming_dist("this is a test", "wokka wokka!!!"));

	char* filearr = file_read("s1c6_decoded.txt");

	struct pair pairs[40];
	int idx = 0;
	for(int i = MIN_KEYSIZE; i < MAX_KEYSIZE+1; i++){

		float score1 = (1.0 * calc_hamming_dist(take_n_bits(0, i, filearr), take_n_bits(i, i*2, filearr)))/i;
		float score2 = (1.0 * calc_hamming_dist(take_n_bits(i, i*2, filearr), take_n_bits(i*2, i*3, filearr)))/i;
		float score3 = (1.0 * calc_hamming_dist(take_n_bits(i*2, i*3, filearr), take_n_bits(i*3, i*4, filearr)))/i;
		float score4 = (1.0 * calc_hamming_dist(take_n_bits(i*3, i*4, filearr), take_n_bits(i*4, i*5, filearr)))/i;
		float score5 = (1.0 * calc_hamming_dist(take_n_bits(i*4, i*5, filearr), take_n_bits(i*5, i*6, filearr)))/i;

		pairs[idx].keysize = i;
		pairs[idx].score = (score1+score2+score3+score4+score5)/5.0;
		idx++;
	}
	qsort(pairs, 40, sizeof(p), compare);

	for(int i=0 ; i < 40; i++){
		printf("%d - %f\t", pairs[i].keysize, pairs[i].score);

	}

	int KEYSIZE = 29;

	FILE *fp = NULL;
	fp = fopen("s1c6_converted.txt","w");
	if(fp == NULL){
		perror("FILE: not found\n");
		exit(1);
	}

	printf("\n\n");
	for(int i=0; i < (int) (strlen(filearr)/KEYSIZE); i++){
		int z = i;
		while(1){
			if(i > (int)strlen(filearr)){
				break;
			}
			i = i + KEYSIZE;
			fputc(filearr[i], fp);
		}
		i = z;
		fclose(fp);
		best_ans();
		fp = fopen("s1c6_converted.txt","w");
		if(fp == NULL){
			perror("FILE: not found\n");
			exit(1);
		}
	}
	fclose(fp);
	return 0;
}
