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
data_t cbuff_rd();

int main(int argc, char* argv[]) {
	RD = semOpen(CBUFF_SEM_RD);
	WR = semOpen(CBUFF_SEM_WR);
	int fd = shmOpen(CBUFF_SHMEM);
	cbuff_ptr = shmMap(fd, sizeof(cbuff_t));
	srand(time(NULL));
	
	FILE* fp;
	fp = fopen("schowek.txt", "w+");
	if(fp == NULL) {
		perror("konsument: couldn't open");
		exit(EXIT_FAILURE);
	}

	while(1) {
		data_t x = cbuff_rd();
		if(!x) break;
		fprintf(fp, "%d\n", x);
		usleep(10000 * (random()%25));
	}

	fclose(fp);
	semClose(RD);
	semClose(WR);
	shmClose(cbuff_ptr, fd, sizeof(cbuff_t));
}

data_t cbuff_rd() {
	semP(RD);

	data_t x = cbuff_ptr->data[cbuff_ptr->head];
	cbuff_ptr->head += 1;
	cbuff_ptr->head %= CBUFF_SIZE;
	
	printf("cbuff_rd(%d)\n", x);
	semV(WR);
	return x;
}
