#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("err: improper usage. \n$./kopiuj.x <src file> <dist file>\n");
        exit(1);
    }

    int src = open(argv[1], O_RDONLY);
    int dst = open(argv[2], O_WRONLY);

    if (src == -1 || dst == -1) {
        perror("err");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_red = 0;
    ssize_t bytes_written = 0;

    do {
        bytes_red = read(src, buffer, BUFFER_SIZE);
        bytes_written = write(dst, buffer, bytes_red);

        if (bytes_red != bytes_written || bytes_red == -1 || bytes_written == -1) {
            perror("err");
            exit(1);
        }
    } while (bytes_red);

    close(src);
    close(dst);
    
    return 0;
}
