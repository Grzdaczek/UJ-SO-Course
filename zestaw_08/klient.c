#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "msg.h"
#include "defs.h"

mqd_t client_mqd;
mqd_t server_mqd;
char msg_clientname[256];

void handle_exit();
void handle_sigint(int sig);

int main(int argc, char* argv[]) {
	
	atexit(handle_exit);
	signal(SIGINT, handle_sigint);

	request_t req;
	response_t res;

	req.pid = getpid();
	sprintf(msg_clientname, "/%d" , req.pid);

	mqd_t server_mqd = msgOpen(MSG_SERVERNAME);
	if(server_mqd == -1) _exit(EXIT_FAILURE);
	
	mqd_t client_mqd = msgCreate(msg_clientname);
	if(client_mqd == -1) exit(EXIT_FAILURE);

	msgInfo(client_mqd);

	char* line = NULL;
	ssize_t read;
	size_t len = 0;
	
	printf("> ");

	while ((read = getline(&line, &len, stdin)) != -1) {
		
		int result = sscanf(line, "%f %c %f", &req.dat_a, &req.opcode, &req.dat_b);
		if(result != 3) {
			printf("error: couuldn't parse\n> ");
			continue;
		}

		msgSend(server_mqd, &req, sizeof(request_t));
		msgRecv(client_mqd, &res, sizeof(response_t));
		
		printf("%f\n", res.result);
		printf("> ");
	}

	exit(EXIT_SUCCESS);
}

void handle_sigint(int sig) {
	exit(EXIT_SUCCESS);
}

void handle_exit() {
	msgRemove(msg_clientname);
}
