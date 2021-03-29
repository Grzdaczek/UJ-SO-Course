#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	switch (fork()) {
		case -1:
			perror("");
			exit(1);
			break;
		case 0:
			sleep(3);
			exit(0);
			break;
		default:
			sleep(6);
			break;
	}
}
