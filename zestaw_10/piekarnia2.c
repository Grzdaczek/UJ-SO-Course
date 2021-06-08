#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_NUMBER 5
#define TASK_NUMBER 1000000

volatile int counter = 0;
volatile unsigned int tickets[THREAD_NUMBER];
volatile unsigned int choose[THREAD_NUMBER]; 

void* task(int* id);

int main(int argc, char* argv[]) {
	
	pthread_t td[THREAD_NUMBER];

	for(int i=0; i<THREAD_NUMBER; i++) {
		choose[i] = 0;
		tickets[i] = 0;
	}

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

	printf("expected: %d, got: %d, %s\n", THREAD_NUMBER*TASK_NUMBER, counter,
		   THREAD_NUMBER*TASK_NUMBER==counter ? "SUCCESS" : "FAILURE");
}

//-----------------------------------------------------------------------------

int find_ticket() {
	unsigned int max = 0;
	for(int id=0; id<THREAD_NUMBER; id++) {
		if(max < tickets[id]) max = tickets[id];
	}
	return max + 1;
}

void lock(int id) {
	choose[id] = 1;
	__sync_synchronize();
	tickets[id] = find_ticket();
	choose[id] = 0;

	__sync_synchronize();
	for (int other=0; other<THREAD_NUMBER; other++) {
		while(choose[other] == 1);
		while(tickets[other] != 0 && (tickets[other] < tickets[id] || (tickets[other] == tickets[id] && other < id)));
	}
}

void unlock(int id) {
	// __sync_synchronize();
	tickets[id] = 0;
}

void* task(int* id) {
	for (int i=0; i<TASK_NUMBER; i++) {
		// begin critical section
		lock(*id);
		int c = counter;
		c++;
		counter = c;
		unlock(*id);
		// end critical section
	}

	free(id);
	return NULL;
}
