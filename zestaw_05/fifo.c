#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>

#define PIPE_NAME "fifo"

typedef struct {
	void* NEVER;
	char* prod_p;
	char* src_p;
	char* cons_p;
	char* dst_p;
} arg_t;

void exit_handler();

int main(int argc, char* argv[])
{
	arg_t* arg = (arg_t*)argv;
	atexit(exit_handler);

	if(argc != 5) {
		errno = EINVAL;
		perror("Invalid argument count");
		_exit(EXIT_FAILURE);
	}

	if(mkfifo(PIPE_NAME, 0644)) {
		perror("Could not create FIFO");
		_exit(EXIT_FAILURE);
	}
	
	
	switch(fork()) {
		case -1:
			perror("Fork error");
			exit(EXIT_FAILURE);
		case 0:
			execl(arg->prod_p, "producer", arg->src_p, PIPE_NAME, NULL);
			perror("Could not execude");
			_exit(EXIT_FAILURE);
	}

	switch(fork()) {
		case -1:
			perror("Fork error");
			exit(EXIT_FAILURE);
		case 0:
			execl(arg->cons_p, "consument", PIPE_NAME, arg->dst_p, NULL);
			perror("Could not execude");
			_exit(EXIT_FAILURE);
	}

	wait(NULL);
	wait(NULL);

	exit(EXIT_SUCCESS);
}

void exit_handler() {
	if(unlink(PIPE_NAME)) {
		perror("Could not remove FIFO");
		exit(EXIT_FAILURE);
	}
}
