#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

#include "shmem.h"
#include "sem.h"
#include "cbuff_def.h"

void constructor();
void destructor();
void exit_handler();
void sigint_handler(int signo);

int main(int argc, char* argv[]) {

	signal(SIGINT, sigint_handler);
	atexit(exit_handler);
	constructor();

	switch(fork()) {
		case -1:
			perror("glowny: error");
			exit(EXIT_FAILURE);
		case 0:
			execl("./producent.x", "", NULL);
			perror("glowy: error");
			exit(EXIT_FAILURE);
	}

	switch(fork()) {
		case -1:
			perror("glowny: error");
			exit(EXIT_FAILURE);
		case 0:
			execl("./konsument.x", "", NULL);
			perror("glowy: error");
			exit(EXIT_FAILURE);
	}

	wait(NULL);
	wait(NULL);

	exit(EXIT_SUCCESS);
}

void constructor() {
	semCreate(CBUFF_SEM_RD, 0);
	semCreate(CBUFF_SEM_WR, CBUFF_SIZE);
	int fd = shmCreate(CBUFF_SHMEM, sizeof(cbuff_t));
	cbuff_t* cbuff_ptr = shmMap(fd, sizeof(cbuff_t));
	cbuff_ptr->head = 0;
	cbuff_ptr->tail = 0;
}

void destructor() {
	shmRemove(CBUFF_SHMEM);
	semRemove(CBUFF_SEM_RD);
	semRemove(CBUFF_SEM_WR);
}

void sigint_handler(int signo) {
	exit(EXIT_FAILURE);
}

void exit_handler() {
	destructor();
}
