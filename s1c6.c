#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_KEYSIZE 40
#define MIN_KEYSIZE 2

int a_len=0;

typedef struct pair p;
typedef p* p_t;

struct pair{
	int keysize;
	float score;
};

int* char_to_bin(const unsigned char c, int* bin) {
	int i;
	int idx = 0;
	for(i = 7; i >= 0; i--){
		bin[idx++] = ( int )( ( c & (1 << i) ) ? 1 : 0);
	}
	return bin;
}

unsigned char* file_read(char* filename){

	FILE *f = fopen(filename, "r");
	fseek(f, 0L, SEEK_END);
	unsigned int size = ftell(f);
	fseek(f, 0L, SEEK_SET);
	unsigned char* array = malloc(sizeof(unsigned char)* size +1);
	unsigned int read_size = fread(array, 1, size, f)+1;
	array[read_size] = '\0';
	fclose(f);
	a_len = read_size;
	return array;
}

unsigned char* take_n_bits(int start,int end, unsigned char* arr){
	unsigned char* string = NULL;
	string = malloc(sizeof(unsigned char) * (end - start)+1);
	int j = 0;
	for(int i = start; i < end; i++){
		string[j++] = arr[i];
	}
	string[j] = '\0';
	return string;
}

int calc_hamming_dist(const unsigned char* str1, const unsigned char* str2){

	int dist = 0;
	while(*str1 || *str2){
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
		free(str1_b);
		free(str2_b);
	}
	return dist;
}

int compare (const void * a, const void * b)
{
	const p *A = a;
	const p *B = b;
	return ( B->score < A->score ? 1 : -1 );
}

char* best_ans(unsigned char* arr, int key_size){

	char* key = malloc(sizeof(char) * key_size);
	int i = 0;
	int data_len = a_len;
	for (i = 0; i < key_size; ++i) {
		unsigned char best_byte = 0;
		float best_score = 0;
		for (int byte = 0; byte <= 255; ++byte) {
			int j = 0;
			float score = 0;
			for (j = i; j < data_len; j += key_size) {
				char xor = arr[j] ^ (char)byte;
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
			if (score > best_score) {
				best_score = score;
				best_byte = byte;
			}
		}
		key[i] = best_byte;
	}
	return key;
}
void decrypt(char* key, const unsigned char* enc, int key_size){

	int idx =0;
	for(int i=0; i < a_len; i++){
		if(idx % key_size == 0) idx=0;
		printf("%c",enc[i] ^ key[idx++]);
	}

}

int main(int argc, char* argv[]){

	if(argc != 2){
		perror("Invalid Args\n");
		exit(1);
	}

	if(37 != calc_hamming_dist((unsigned char*)"this is a test",(unsigned char*) "wokka wokka!!!")){
		perror("Hamming distance check failed\n");
		exit(1);
	}
	unsigned char* filearr = file_read("s1c6_decoded.txt");
	struct pair pairs[40];
	int idx = 0;
	for(int i = MIN_KEYSIZE; i < MAX_KEYSIZE + 1; i++){
		float score1 = (1.0 * calc_hamming_dist(take_n_bits(0, i, filearr), take_n_bits(i, i*2, filearr)))/i;
		float score2 = (1.0 * calc_hamming_dist(take_n_bits(i, i*2, filearr), take_n_bits(i*2, i*3, filearr)))/i;
		float score3 = (1.0 * calc_hamming_dist(take_n_bits(i*2, i*3, filearr), take_n_bits(i*3, i*4, filearr)))/i;
		float score4 = (1.0 * calc_hamming_dist(take_n_bits(i*3, i*4, filearr), take_n_bits(i*4, i*5, filearr)))/i;
		float score5 = (1.0 * calc_hamming_dist(take_n_bits(i*4, i*5, filearr), take_n_bits(i*5, i*6, filearr)))/i;

		pairs[idx].keysize = i;
		pairs[idx].score = (score1 + score2 + score3 + score4 + score5) / 5.0;
		idx++;
	}
	qsort(pairs, 40, sizeof(p), compare);

	printf("\n\n");
	/* take the top 10 key sizes */
	for(int i=1; i < 10; i++)
		printf("%s for key %d\n",best_ans(filearr, pairs[i].keysize), pairs[i].keysize);

	printf("\n\n");
	decrypt("Terminator X: Bring the noise",filearr, pairs[6].keysize);

	free(filearr);
	return 0;
}
