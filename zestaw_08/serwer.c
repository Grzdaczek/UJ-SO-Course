#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include "msg.h"
#include "defs.h"

void handle_sigint(int sig);
void handle_exit();
float calc_request(request_t* request);

int main(int argc, char* argv[]) {
	srand(time(NULL));
	atexit(handle_exit);
	signal(SIGINT, handle_sigint);
	
	mqd_t server_mqd = msgCreate(MSG_SERVERNAME);
	if(server_mqd == -1) _exit(EXIT_FAILURE);
	msgInfo(server_mqd);

	while(1) {

		request_t request;
		msgRecv(server_mqd, &request, sizeof(request_t));

		char name[256];
		sprintf(name, "/%d" , request.pid);
		
		mqd_t client_mqd = msgOpen(name);
		response_t response = { calc_request(&request) };
		msgSend(client_mqd, &response, sizeof(response_t));
		msgClose(client_mqd);
	}

}

void handle_sigint(int sig) {
	exit(EXIT_SUCCESS);
}

void handle_exit() {
	msgRemove(MSG_SERVERNAME);
}

float calc_request(request_t* r) {
	float result;
	printf("%d:\t%f %c %f = ", r->pid, r->dat_a, r->opcode, r->dat_b);
	fflush(stdout);
	
	switch (r->opcode) {
		case '+':
			result = r->dat_a + r->dat_b;
			break;

		case '-':
			result = r->dat_a - r->dat_b;
			break;

		case '*':
			result = r->dat_a * r->dat_b;
			break;

		case '/':
			result = r->dat_a / r->dat_b;
			break;

		default:
			result = 0.0 / 0.0 ; // NaN
			break;
	}

	sleep(rand() % 3 + 3);
	printf("%f\n", result);

	return result;
}
