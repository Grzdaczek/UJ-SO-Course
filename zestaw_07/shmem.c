#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "shmem.h"

int shmCreate(const char* name, int size) {
	int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0660);
	if(fd == -1) {
		perror("libshmem: error");
		return -1;
	}

	int result = ftruncate(fd, size);
	if(result == -1) {
		perror("libshmem: error");
		return -1;
	}

	return fd;
}

int shmOpen(const char* name) {
	int fd = shm_open(name, O_RDWR, 0660);
	if(fd == -1) perror("libshmem: error");
	return fd;
}

void shmRm(const char* name) {
	int result = shm_unlink(name);
	if(result == -1) perror("libshmem: error");
}

void* shmMap(int fd, int size) {
	void* shmem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(shmem == MAP_FAILED) {
		perror("libshmem: error");
		return NULL;
	}
	return shmem;
}

void shmClose(void* ptr, int fd, int size) {
	int result = munmap(ptr, size);
	if(result == -1) perror("libshmem: error");
	result = close(fd);
	if(result == -1) perror("libshmem: error");
}

int shmSize(int fd) {
	struct stat s;
	fstat(fd, &s);
	return s.st_size;
}

void shmInfo(int fd) {
	struct stat s;
	fstat(fd, &s);
	printf("mode:\t%o\n", s.st_mode);
	printf("owner:\t%u\n", s.st_uid);
	printf("size:\t%ld\n", s.st_size);
}

