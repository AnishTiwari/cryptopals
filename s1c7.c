#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include<openssl/aes.h>

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

int
decrypt_aes_ecb(unsigned char * ciphertext, int ciphertext_length,
                unsigned char * key, unsigned char * plaintext)
{
	int plaintext_length = 0;
	int length = 0;

	EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
	if (!ctx) {
		perror("EVP_CIPHER_CTX_new()");
		exit(-1);
	}
	EVP_CIPHER_CTX_set_padding(ctx, 0);
	EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
	EVP_DecryptUpdate(ctx, plaintext, &length, ciphertext, ciphertext_length);
		plaintext_length += length;

	EVP_DecryptFinal_ex(ctx, plaintext +length, &length);
	plaintext_length += length;
	printf("%s",plaintext);

	EVP_CIPHER_CTX_free(ctx);
	return plaintext_length;
}

int main(){
	unsigned char* key= (unsigned char*)"YELLOW SUBMARINE";
	unsigned char* filearr = file_read("s1c7_decoded.txt");
	unsigned char* plain_text = malloc(sizeof(unsigned char) * 1610);
	if(plain_text == NULL)
		printf("MALLOC:\n"),exit(-1);

	decrypt_aes_ecb(filearr, (int)strlen((char*)filearr),key,plain_text);
	return 0;
}
