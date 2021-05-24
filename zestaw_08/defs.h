#ifndef _DEFS_H
#define _DEFS_H

#define MSG_SERVERNAME "/server_queue"

typedef struct {
	int pid;
	float dat_a;
	float dat_b;
	char opcode;
} request_t;

typedef struct {
    float result;
} response_t;

#endif // _DEFS_H
