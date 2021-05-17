#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "shmem.h"
#include "sem.h"
#include "cbuff_def.h"

semid RD;
semid WR;
cbuff_t* cbuff_ptr;
void cbuff_wr(data_t x);

int main(int argc, char* argv[]) {
	RD = semOpen(CBUFF_SEM_RD);
	WR = semOpen(CBUFF_SEM_WR);
	int fd = shmOpen(CBUFF_SHMEM);
	cbuff_ptr = shmMap(fd, sizeof(cbuff_t));
	srand(time(NULL)+1);

	FILE* fp;
	char* line = NULL;
	size_t len = 0;

	fp = fopen("magazyn.txt", "r");
	if(fp == NULL) {
		perror("producent: couldn't open");
		exit(EXIT_FAILURE);
	}

	while(getline(&line, &len, fp) != -1) {
		data_t x;
		sscanf(line, "%d", &x);
		cbuff_wr(x);
		usleep(10000 * (random()%30));
	}

	cbuff_ptr->eof = 1; 

	semClose(RD);
	semClose(WR);
	shmClose(cbuff_ptr, fd, sizeof(cbuff_t));
}

void cbuff_wr(data_t x) {
	semP(WR);

	cbuff_ptr->data[cbuff_ptr->tail] = x;
	cbuff_ptr->tail += 1;
	cbuff_ptr->tail %= CBUFF_SIZE;
	
	printf("cbuff_wr(%d)\n", x);
	semV(RD);
}
