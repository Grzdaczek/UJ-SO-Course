#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "msg.h"

typedef struct {
	char data[256];
} msg_t;

int main(int argc, char* argv[]) {

	if(argc != 3) {
		errno = EINVAL;
		perror("Invalid argument number");
		exit(EXIT_FAILURE);
	}

	msg_t m;
	mqd_t mqd;
	char* name = argv[2];
	
	switch(argv[1][0]) {

		case 'c': ;
			msgCreate(name);
			break;

		case 'd': ;
			msgRemove(name);
			break;

		case 'r': ;
			mqd = msgOpen(name);
			msgRecv(mqd, &m, sizeof(msg_t));
			printf("%s\n", (char*)&m);
			break;

		case 'w': ;
			int result = read(STDIN_FILENO, &m, sizeof(m));
			if(result ==  -1) {
				perror("Couldn't read");
				exit(EXIT_FAILURE);
			}
			mqd = msgOpen(name);
			msgSend(mqd, &m, sizeof(msg_t));
			break;

		case 'i': ;
			mqd = msgOpen(name);
			if(mqd != -1) msgInfo(mqd);
			break;

		default: ;
			errno = EINVAL;
			perror("Command not implemented");
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
