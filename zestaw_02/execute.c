#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    printf("pierwszy komunikat\n");
    execv("potomny.x", NULL);
    printf("drugi komunikat\n");
}
