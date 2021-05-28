#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUMBER 10

volatile int counter = 0;
volatile unsigned int ticket_last = 1;
volatile unsigned int tickets[THREAD_NUMBER];

void* task(int* id);

int main(int argc, char* argv[]) {
	
	pthread_t td[THREAD_NUMBER];

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

	printf("expected: %d==%d, %s\n", THREAD_NUMBER, counter,
		   THREAD_NUMBER==counter ? "SUCCESS" : "FAILURE");
	exit(THREAD_NUMBER==counter ? EXIT_SUCCESS : EXIT_FAILURE);
}

//-----------------------------------------------------------------------------

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

	// begin critical section
	lock(*id);
	printf("%d: entering critical section\n", *id);
	int c = counter;
	c++;

	printf("%d: working", *id);
	for(int i=0; i<20; i++) {
		usleep(50000);
		printf(".");
		fflush(stdout);
	}
	printf("\n");
	
	counter = c;
	printf("%d: leaving critical section\n\n", *id);
	unlock(*id);
	// end critical section

	free(id);
	return NULL;
}
