//Mayah Vandertuig
//5/29/18
//Lab9: File Performance Measurement
//Step 2: read file with buffer size N as parameter  

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

char *FileName;
int BUF_SIZE; 
FILE *rb; 

void *t_file(void *arg){
	char buf[BUF_SIZE];
	char newFile[20];
	sprintf(newFile, "%s.out%d", FileName, (int) arg);
//	FILE *rb = fopen(FileName, "rb");
        FILE *wb = fopen(newFile, "wb");
        while(fread(buf,BUF_SIZE,1,rb))
                fwrite(buf,BUF_SIZE,1,wb);
	//fclose(rb);
	fclose(wb); 
}

int main(int argc, char *argv[]) { 
	BUF_SIZE = atoi(argv[2]); 
	FileName = argv[1]; 
	int NUM_THREADS = atoi(argv[3]);
        rb = fopen(FileName, "rb");

	pthread_t thread[NUM_THREADS];        
	for(int i=0; i<NUM_THREADS; i++) {
		pthread_create(&thread[i], NULL, t_file, (void*)i);
	}
	for(int i=0; i<NUM_THREADS; i++) 
		pthread_join(thread[i],NULL); 
	fclose(rb);
	return 0;

}

