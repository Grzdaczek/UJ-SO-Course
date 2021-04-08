#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include "procinfo.h"

void signal_handler(int sig);

int main(int argc, char* argv[]) 
{
    if(argc != 3) {
        errno = EINVAL;
        perror("Invalid argument count");
        exit(EXIT_FAILURE);
    }

    char* name = argv[0];
    char cmd = *argv[1];
    int sig;
    sscanf(argv[2], "%d", &sig);

    procinfo(name);

    switch(cmd) {
        case 'd':
            signal(sig, SIG_DFL);
            break;
        case 'i':
            signal(sig, SIG_IGN);
            break;
        case 'p':
            signal(sig, signal_handler);
            break;
        default:
            errno = EINVAL;
            perror("First argument should be {d|i|p}");
            exit(EXIT_FAILURE);
    }

    pause();
    return 0;
}

void signal_handler(int sig)
{
    printf("Signal Recived: %d\n", sig);
}
