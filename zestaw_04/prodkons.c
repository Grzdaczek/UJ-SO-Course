#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>

#define CHUNK_SIZE 8

void prod_process(int pipe_fd[2], int src_fd);
void kons_process(int pipe_fd[2], int dst_fd);

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

/*
    do {
        bytes_red = read(src, buffer, BUFFER_SIZE);
        bytes_written = write(dst, buffer, bytes_red);

        if (bytes_red != bytes_written || bytes_red == -1 || bytes_written == -1) {
            perror("err");
            exit(1);
        }
    } while (bytes_red);
*/

void prod_process(int pipe_fd[2], int src_fd)
{
    int* rx_fd = &pipe_fd[0];
    int* tx_fd = &pipe_fd[1];

    close(*rx_fd);

    /* transmit data through pipe */

    close(*tx_fd);
    close(src_fd);
    wait(NULL);
    exit(EXIT_SUCCESS);
}

void kons_process(int pipe_fd[2], int dst_fd)
{
    int* rx_fd = &pipe_fd[0];
    int* tx_fd = &pipe_fd[1];

    close(*tx_fd);

    char buffer[1024];
    write(STDIN_FILENO, "lel\n", 4);


    /* recive data through pipe */

    close(*rx_fd);
    close(dst_fd);
    exit(EXIT_SUCCESS);
}
