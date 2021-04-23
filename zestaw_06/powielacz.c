#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <wait.h>
#include "sem.h"
#include "prog_def.h"

void exit_handler();

int main(int argc, char* argv[]) {
	if(argc != 4) {
		errno = EINVAL;
		perror("powielacz: invalid argument count");
		_exit(EXIT_FAILURE);
	}

	const int progInstances = atoi(argv[2]);
	const int critResources = atoi(argv[3]);
	
	atexit(exit_handler);
	signal(SIGINT, exit_handler);
	semCreate(SEM_NAME, critResources);
	srand(time(NULL));

   	int fd = open(FILE_NAME, O_WRONLY | O_CREAT, 0644);
	char value = 0;
	int bytes = write(fd, &value, 1);
	if(bytes == -1) perror("powielacz");
	close(fd);
	int instNumber = 0;

	for(int i=0; i<progInstances; i++) {
		switch(fork()) {
			case -1:
				perror("powielacz: fork eror");
				exit(EXIT_FAILURE);
			case 0:
				execl("./prog.x", argv[1], argv[3], NULL);
				perror("powielacz: execl error");
				exit(EXIT_FAILURE);
			default:
				instNumber++;
		}
		usleep(100*1000*(rand()%10));
	}

	while(instNumber--) wait(NULL);

   	fd = open(FILE_NAME, O_RDONLY);
	bytes = read(fd, &value, 1);
	if(bytes == -1) perror("powielacz");
	printf("powielacz: "FILE_NAME" == %d, status: %s\n", value, value==progInstances ? "OK" : "ERR");
	close(fd);
}

void exit_handler() {
	semRemove(SEM_NAME);
}
