#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "procinfo.h"

int main(int argc, char* argv[]) {
	int child_number = 0;
	
	for (int i = 0; i < 3; i++) {
		int pid = fork();
		switch (pid)
		{
			case -1:
				perror("");
				exit(1);
				break;
			case 0:
				child_number = 0;
				sleep(1);
				break;
			default:
				child_number++;
				break;
		}

		if(!pid) break;
	}
	procinfo(argv[0]);
	while (child_number--) wait(NULL);
}
