#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "sem.h"
#include "prog_def.h"

int main(int argc, char* argv[]) {
	if(argc != 2) {
		errno = EINVAL;
		perror("prog: invalid argument count");
		exit(EXIT_FAILURE);
	}

	const int critResources = atoi(argv[1]);
	semid sem = semOpen(SEM_NAME);

	/* begin critical section -------------------------------- */
	for(int i=0; i<critResources; i++) semP(sem);

   	int fd = open(FILE_NAME, O_RDONLY);
	char value = 0;
	int bytes = read(fd, &value, 1);
	if(bytes == -1) perror("prog");
	close(fd);
	
	printf("prog: %d, begin critical section\n", value);
	sleep(1);
	printf("prog: %d, end critical section\n", value);

   	fd = open(FILE_NAME, O_WRONLY);
	value++;
	bytes = write(fd, &value, 1);
	if(bytes == -1) perror("prog");
	close(fd);

	for(int i=0; i<critResources; i++) semV(sem);
	/* end critical section ---------------------------------- */
}
