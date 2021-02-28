#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	int same=0;
	printf("blocks are %d",(int)strlen((const char*)filearr));
        /* 32 bytes sized blocks */
	for(int i=0; i < (int)strlen((const char*)filearr)/32; i+=1){
		printf("i is %d\n", i);
		int pi = (i == 0) ? 0 : (i * 32);
		int idx = pi + 32;
		int bool = 0;
		int iter = 0;
	        while(idx < (int)strlen((const char*)filearr)-1){
			iter++;
			printf("idx is %d -> %c - %c po is %d \n ", idx,filearr[pi%32], filearr[idx],pi);
			if(filearr[pi%32] == filearr[idx])
			{
				printf("same for %d %c bool %d\n", idx, filearr[idx],bool);
				if((idx+1) % 32 == 0 && idx != i+32 ){
					bool++;
					if(bool == 32){
						printf("count %d\n\n\n----------------------------",same+1),same+=1;
					}
					bool=0;
					pi=0;
					idx ++;
				}
				else{
					bool++;
					idx++;
					pi++;
				}
			}else
			{
				/* if(idx %32 ==0) */
				/* 	break; */
				pi=0,bool=0,idx += (idx%32);
			}
		}
		printf("I is %d\n\n", i);
	}
	printf("--%d",same);
	return 0;
}
