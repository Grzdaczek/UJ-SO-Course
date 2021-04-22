#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "sem.h"

#define SEM_NAME "/semaforzasty"

int main(int argc, char* argv[]) {
	if(argc != 2) {
		errno = EINVAL;
		perror("Invalid argument count");
		exit(EXIT_FAILURE);
	}

	semid sem = NULL;

	switch(argv[1][0]) {
		case 'i': ;
			sem = semCreate(SEM_NAME, 1);
			semClose(sem);
			break;
		case 'r': ;
			semRemove(SEM_NAME);
			break;
		case 'p': ;
			sem = semOpen(SEM_NAME);
			semP(sem);
			semClose(sem);
			break;
		case 'v': ;
			sem = semOpen(SEM_NAME);
			semV(sem);
			semClose(sem);
			break;
		case 'q': ;
			sem = semOpen(SEM_NAME);
			semV(sem);
			semClose(sem);
			break;
		default:
			errno = EINVAL;
			perror("Command not implemented");
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
