#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {

    if(argc != 3) {
        perror("err: improper usage. $ ./kopiuj.x <src file> <dist file>");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    size_t red = 0;
    FILE* src_ptr = fopen(argv[1], "r");
    FILE* dst_ptr = fopen(argv[2], "w");

    if (!src_ptr || !dst_ptr) {
        perror("err: could not open the file.");
        exit(1);
    }

    do {
        red = fread(buffer, sizeof(char), BUFFER_SIZE, src_ptr);
        fwrite(buffer, sizeof(char), red, dst_ptr);
    } while (red == BUFFER_SIZE);
    
    return 0;
}