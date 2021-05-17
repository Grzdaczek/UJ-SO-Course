#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "sem.h"

semid semCreate(const char *name, int val) {
	semid sem = sem_open(name, O_CREAT | O_EXCL, 0644, val);
	if(sem == SEM_FAILED) {
		perror("sem-err: cannot create");
		return NULL;
	} 
	else {
		//printf("sem-inf: created: %s %d\n", name, val);
		return sem;
	}
}

void semRemove(const char *name) {
	int err = sem_unlink(name);
	if(err) {
		perror("sem-err: cannot remove");
	}
	else {
		//printf("sem-inf: removed %s\n", name);	
	}
}

semid semOpen(const char *name) {
	semid sem = sem_open(name, O_RDWR);
	if(sem == SEM_FAILED) {
		perror("sem-err: cannot open");
		return NULL;
	} 
	else {
		//printf("sem-inf: opened: %s\n", name);
		return sem;
	}
}

void semClose(semid sem) {
	int err = sem_close(sem);
	if(err) {
		perror("sem-err: cannot close");
	}
	else {
		//printf("sem-inf: closed\n");
	}
}

void semP(semid sem) {
	int err = sem_wait(sem);
	if(err) {
		perror("sem-err: cannot wait (P)");
	} else {
		//printf("sem-inf: waited (P)\n");
	}
}

void semV(semid sem) {
	int err = sem_post(sem);
	if(err) {
		perror("sem-err: cannot post (V)");
	} else {
		//printf("sem-inf: posted (V)\n");
	}
}

void semInfo(semid sem) {
	int value;
	int err = sem_getvalue(sem, &value);
	if(err) {
		perror("sem-err: cannot get value");
	}
	else {
		printf("sem-inf: value: %d\n", value);
	}
}
