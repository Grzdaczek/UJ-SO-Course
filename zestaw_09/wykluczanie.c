#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define THREAD_COUNT 10

pthread_mutex_t id_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

int last_id = 0;
int task_counter = 0;

void* task(void* ptr);

//-----------------------------------------------------------------------------

int main(int argc, char* argv[]) {
	
	pthread_t td[THREAD_COUNT];
	srand(time(NULL));
	printf("\033c");
	fflush(stdout);

	for(int i=0; i<THREAD_COUNT; i++) {
		int result = pthread_create(&td[i], NULL, (void*(*)())task, NULL);
		if(result == -1) perror("error: pthread_create");
	}
	
	for(int i=0; i<THREAD_COUNT; i++) {
		int result = pthread_join(td[i], NULL);
		if(result == -1) perror("error: pthread_join");
	}

	printf("\033[%d;1H", THREAD_COUNT+1);

	exit(EXIT_SUCCESS);
}

inline void printat(char* message, int x, int y, int mod) {
	// pthread_mutex_lock(&stdout_mutex);
	printf("\033[%d;%dH\033[%dm", y, x, mod);
	printf("%s", message);
	fflush(stdout);
	// pthread_mutex_unlock(&stdout_mutex);
}

//-----------------------------------------------------------------------------

void* task(void* ptr) {
	char buff[64];

	pthread_mutex_lock(&id_mutex);
	int id = last_id++;
	pthread_mutex_unlock(&id_mutex);

	usleep(1000*(random() % 9 + 1));

	sprintf(buff, "%d: waiting", id);
	printat(buff, 1, id+1, 33);
	
	// begin critical section
	pthread_mutex_lock(&counter_mutex);
	int c = task_counter;
	c++;

	sprintf(buff, "%d:              critical (%d/%d)", id, c, THREAD_COUNT);
	printat(buff, 1, id+1, 31);
	
	sleep(1);

	task_counter = c;
	pthread_mutex_unlock(&counter_mutex);
	// end critical section

	sprintf(buff, "%d: done                         ", id);
	printat(buff, 1, id+1, 34);

	return NULL;
}
