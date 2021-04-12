#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "procinfo.h"

void main_process(int send_sig, int target_pgid);
void gmaster_process(int handle_sig);

int main(int argc, char* argv[])
{
	const int sig = 2; /* SIGINT */
	const int pid = fork();

	switch(pid) {
		case -1:
			perror("Fork error");
			exit(EXIT_FAILURE);
		case 0:
			gmaster_process(sig);
		default:
			main_process(sig, pid);
	}

	/* Should never execute */
	exit(EXIT_FAILURE);
}

void main_process(int send_sig, int target_pgid)
{
	sleep(1);

	if(kill(-target_pgid, 0) != -1) {
		kill(-target_pgid, send_sig);
	}
	else {
		perror("Could not send signal");
		exit(EXIT_FAILURE);
	}

	wait(NULL);
	exit(EXIT_SUCCESS);
}

void gmaster_process(int handle_sig)
{
	int child_number = 0;
	setpgid(0, 0);
	procinfo("group_master");
	signal(handle_sig, SIG_IGN);

	for(int i=0; i<5; i++) {
		switch(fork()) {
			case -1:
				perror("Fork error");
				exit(EXIT_FAILURE);
			case 0:
				execl("./obsluga.x", "group_child", "p", "2", NULL);
			default:
				child_number++;
		}
	}

	while(child_number--) {
		int status;
		wait(&status);
		printf("Waited successfully: %d\n", status);
	}

	exit(EXIT_SUCCESS);
}