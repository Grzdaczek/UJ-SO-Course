#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define CHUNK_SIZE_TX 32
#define CHUNK_SIZE_RX 24

int prod_process(int pipe_fd[2], int src_fd);
int kons_process(int pipe_fd[2], int dst_fd);
void print_chunk(const char* msg, char* chunk, int chunk_size);

int main(int argc, char* argv[])
{
	if(argc != 3) {
		errno = EINVAL;
		perror("Invalid argument count");
		exit(EXIT_FAILURE);
	}

	int src_fd = open(argv[1], O_RDONLY);
	int dst_fd = open(argv[2], O_WRONLY);
	if (src_fd == -1 || dst_fd == -1) {
		perror("File could not be opened");
		exit(EXIT_FAILURE);
	}

	srand(time(NULL));

	int pipe_fd[2];
	if(pipe(pipe_fd)) {
		perror("Pipe could not be created");
		exit(EXIT_FAILURE);
	}

	switch(fork()) {
		case -1:
			perror("Fork error");
			exit(EXIT_FAILURE);
		case 0:
			prod_process(pipe_fd, src_fd);
		default:
			kons_process(pipe_fd, dst_fd);
	}

	/* Should never execute */
	exit(EXIT_FAILURE);
}

/*=-------------------------------------------------------------------------=*/

int prod_process(int pipe_fd[2], int src_fd)
{
	close(pipe_fd[0]);
	ssize_t bytes_red = 0;
	ssize_t bytes_written = 0;
	char chunk[CHUNK_SIZE_TX];

	do {
		usleep(10000 * (random()%30));
		bytes_red = read(src_fd, chunk, CHUNK_SIZE_TX);
		bytes_written = write(pipe_fd[1], chunk, bytes_red);
		print_chunk("sent", chunk, bytes_written);
		if(bytes_written == -1 || bytes_red == -1) perror("File error");
	} while(bytes_red > 0);

	close(pipe_fd[1]);
	close(src_fd);
	wait(NULL);
	exit(EXIT_SUCCESS);
}

int kons_process(int pipe_fd[2], int dst_fd)
{
	close(pipe_fd[1]);
	ssize_t bytes_red = 0;
	ssize_t bytes_written = 0;
	char chunk[CHUNK_SIZE_RX];

	do {
		usleep(10000 * (random()%20));
		bytes_red = read(pipe_fd[0], chunk, CHUNK_SIZE_RX);
		bytes_written = write(dst_fd, chunk, bytes_red);
		print_chunk("recived", chunk, bytes_written);
		if(bytes_written == -1 || bytes_red == -1) perror("File error");
	} while(bytes_red > 0);

	close(pipe_fd[0]);
	close(dst_fd);
	exit(EXIT_SUCCESS);
}

void print_chunk(const char* msg, char* chunk, int chunk_size) {
	char buffer[1024];
	sprintf(buffer, "%s\t  %dB\t ", msg, chunk_size);
	for(int i=0; i<chunk_size; i++) 
		sprintf(buffer+strlen(buffer), "%c", isalpha(chunk[i]) ? chunk[i]: '.');
	sprintf(buffer+strlen(buffer), "\n");
	if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1) perror("Print error");
}

