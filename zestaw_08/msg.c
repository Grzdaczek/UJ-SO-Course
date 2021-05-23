#include "msg.h"

mqd_t msgCreate(const char *name) {
	int mqd = mq_open(name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, NULL);
	if(mqd == -1) perror("msglib: create error");
	return mqd;
}

mqd_t msgOpen(const char *name) {
	int mqd = mq_open(name, O_RDWR, S_IRUSR | S_IWUSR, NULL);
	if(mqd == -1) perror("msglib: open error");
	return mqd;
}

void msgClose(mqd_t mqd) {
	int result = mq_close(mqd);
	if(result == -1) perror("msglib: close error");
}

void msgRemove(const char *name) {
	int result = mq_unlink(name);
	if(result == -1) perror("msglib: remove error");
}

void msgSend(mqd_t mqd, void* msg, int msg_size) {
	if(MSG_MAXSIZE < msg_size) {
		perror("msglib: send error: message size too large.");
		return;
	}

	int result = mq_send(mqd, msg, msg_size, 0);
	if(result == -1) perror("msglib: send error");
}

void msgRecv(mqd_t mqd, void* msg, int msg_size) {
	char buff[MSG_MAXSIZE];
	if(MSG_MAXSIZE < msg_size) {
		perror("msglib: reciv error: message size too large.");
		return;
	}

	int result = mq_receive(mqd, buff, MSG_MAXSIZE, NULL);
	if(result == -1) {
		perror("msglib: reciv error");
		return;
	}

	memcpy(msg, buff, msg_size);
}

void msgInfo(mqd_t mqd) {
	struct mq_attr attr;
	int result = mq_getattr(mqd, &attr);
	if(result == -1) {
		perror("msglib: reciv error");
		return;
	}
	printf("flags:\t\t%s\n", attr.mq_flags ? "O_NONBLOCK" : "0");
	printf("max messages:\t%ld\n", attr.mq_maxmsg);
	printf("message size:\t%ld\n", attr.mq_msgsize);
	printf("cur messages:\t%ld\n", attr.mq_curmsgs);
}