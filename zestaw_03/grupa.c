#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void main_process(int send_sig, int target_gid);
void group_process(int handle_sig);

int main(int argc, char* argv[])
{
	const int sig = 2; /* SIGINT */
	int pid = fork();

	switch(pid) {
		case -1:
			perror("Fork error");
			exit(EXIT_FAILURE);
		case 0:
			group_process(sig);
		default:
			main_process(sig, pid);
	}

	/* Should never execute */
	exit(EXIT_FAILURE);
}

void main_process(int send_sig, int target_gid)
{
	sleep(1);
	kill(-target_gid, send_sig);
	wait(NULL);
	exit(EXIT_SUCCESS);
}

void group_process(int handle_sig)
{
	setpgid(0, 0);
	execl("./obsluga.x", "lel?", "p", "2", NULL);
	exit(EXIT_SUCCESS);
}
