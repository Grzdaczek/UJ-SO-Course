#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define CHUNK_SIZE 24

void print_chunk(char* from, char* to, char* chunk, int chunk_size);

int main(int argc, char* argv[])
{	
	if(argc != 3) {
		errno = EINVAL;
		perror("Invalid argument count");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	int src_fd = open(argv[1], O_RDONLY);
	int dst_fd = open(argv[2], O_WRONLY);

	ssize_t bytes_red = 0;
	ssize_t bytes_written = 0;
	char chunk[CHUNK_SIZE];

	do {
		usleep(10000 * (random()%30));
		bytes_red = read(src_fd, chunk, CHUNK_SIZE);
		bytes_written = write(dst_fd, chunk, bytes_red);
		print_chunk(argv[1], argv[2], chunk, bytes_written);
		if(bytes_written == -1 || bytes_red == -1) perror("File error");
	} while(bytes_red > 0);

	close(src_fd);
	close(dst_fd);
	exit(EXIT_SUCCESS);
}

void print_chunk(char* from, char* to, char* chunk, int chunk_size) {
	char buffer[1024];
	sprintf(buffer, "%s -> %s\t  %dB\t ", from, to, chunk_size);
	for(int i=0; i<chunk_size; i++) 
		sprintf(buffer+strlen(buffer), "%c", isalpha(chunk[i]) ? chunk[i]: '.');
	sprintf(buffer+strlen(buffer), "\n");
	if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1) perror("Print error");
}
