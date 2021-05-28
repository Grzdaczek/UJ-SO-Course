#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUMBER 10

// for output formatting purposes only
pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

volatile int counter = 0;
volatile unsigned int ticket_last = 1;
volatile unsigned int tickets[THREAD_NUMBER];

void* task(int* id);

int main(int argc, char* argv[]) {
	
	pthread_t td[THREAD_NUMBER];
	printf("\033c");
	fflush(stdout);

	for(int i=0; i<THREAD_NUMBER; i++) tickets[i] = 0;

	for(int i=0; i<THREAD_NUMBER; i++) {
		int* id_ptr = malloc(sizeof(int));
		*id_ptr = i;
		int result = pthread_create(&td[i], NULL, (void*(*)())task, id_ptr);
		if(result == -1) perror("error: pthread_create");
	}
	
	for(int i=0; i<THREAD_NUMBER; i++) {
		int result = pthread_join(td[i], NULL);
		if(result == -1) perror("error: pthread_join");
	}

	printf("\033[%d;1H", THREAD_NUMBER+1);
	printf("expected: %d, got: %d, %s\n", THREAD_NUMBER, counter,
		   THREAD_NUMBER==counter ? "SUCCESS" : "FAILURE");
}

//-----------------------------------------------------------------------------

inline void printat(char* message, int x, int y, int mod) {
	pthread_mutex_lock(&stdout_mutex);
	printf("\033[%d;%dH\033[%dm", y, x, mod);
	printf("%s", message);
	fflush(stdout);
	pthread_mutex_unlock(&stdout_mutex);
}

void lock(int id) {
	tickets[id] = ticket_last++;
	// should reuse tickets. Won't work in case of overflow.
	for (int other=0; other<THREAD_NUMBER; other++) {
		while((tickets[other] != 0 && tickets[other] < tickets[id]) || 
			  (tickets[other] == tickets[id] && other < id));
	}
}

void unlock(int id) {
	tickets[id] = 0;
}

void* task(int* id) {
	char buff[64];

	sprintf(buff, "%d: waiting", *id);
	printat(buff, 1, (*id)+1, 33);

	// begin critical section
	lock(*id);
	int c = counter;
	c++;

	sprintf(buff, "%d:              critical (%d/%d)", *id, c, THREAD_NUMBER);
	printat(buff, 1, (*id+1), 31);
	
	sleep(1);

	counter = c;
	unlock(*id);
	// end critical section

	sprintf(buff, "%d: done                         ", *id);
	printat(buff, 1, (*id)+1, 34);

	free(id);
	return NULL;
}
