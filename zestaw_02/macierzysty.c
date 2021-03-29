#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "procinfo.h"

int main(int argc, char* argv[]) {
	int child_number = 0;
	
	for (int i = 0; i < 3; i++) {
		switch (fork())
		{
			case -1:
				perror("");
				exit(1);
				break;
			case 0:
                execv("potomny.x", NULL);
			default:
				child_number++;
				break;
		}
	}
    
	procinfo(argv[0]);
	while (child_number--) wait(NULL);
}
