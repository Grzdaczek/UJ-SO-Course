#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "shmem.h"

#define SHMEM_NAME "/dzielona_but_d_is_silent"

int main(int argc, char* argv[]) {

	if(argc <= 1) {
		printf("./shmuse.x <option> [size]\n");
		printf("Options:\n");
		printf("c  create shared memory segment of [size] bytes\n");
		printf("d  remove shared memory segment\n");
		printf("r  read shared memory contents and write it to the stdout\n");
		printf("w  write to the shared memory from stdin\n");
		printf("i  display info about shared memory segment\n");
		exit(EXIT_SUCCESS);
	}

	int fd = 0;
	int size = 0;
	int n = 0;
	char *shmem = NULL;
	
	switch(argv[1][0]) {

		case 'c': ;
			// Tworzy segment pamięci dzielonej o rozmiarze size bajtów.
			if(argc != 3) {
				errno = EINVAL;
				perror("Invalid argument count");
				exit(EXIT_FAILURE);
			}
			sscanf(argv[2], "%d", &size);
			shmCreate(SHMEM_NAME, size);
			break;

		case 'd': ;
			// Usuwa segment pamięci dzielonej.
			shmRm(SHMEM_NAME);
			break;

		case 'r': ;
			// Wypisuje zawartość pamięci dzielonej na standardowe wyjście.
			fd = shmOpen(SHMEM_NAME);
			size = shmSize(fd);
			shmem = shmMap(fd, size);
			n = write(STDOUT_FILENO, shmem, size);
			if(n == -1) perror("Write error");
			break;

		case 'w': ;
			// Kopiuje zawartość standardowego wejścia do pamięci dzielonej.
			fd = shmOpen(SHMEM_NAME);
			size = shmSize(fd);
			shmem = shmMap(fd, size);
			n = read(STDIN_FILENO, shmem, size);
			if(n == -1) perror("Read error");
			break;

		case 'i': ;
			// Wypisuje informacje o pamięci dzielonej.
			fd = shmOpen(SHMEM_NAME);
			shmInfo(fd);
			break;

		default: ;
			errno = EINVAL;
			perror("Command not implemented");
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
