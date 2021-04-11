#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc != 3) {
       errno = EINVAL;
       perror("Invalid argument count");
       exit(EXIT_FAILURE);
    }

    int sig = atoi(argv[2]);
    int pid = fork();

    switch(pid) {
        case -1:
            perror("Fork error");
            exit(EXIT_FAILURE);
            break;
        case 0:
            execl("./obsluga.x", argv[0], argv[1], argv[2], NULL);
            break;
        default:
            sleep(1);
            if(kill(pid, 0) != -1) {
                kill(pid, sig);
            }
            else {
                perror("Could not send signal");
                exit(EXIT_FAILURE);
            }
    }

    wait(NULL);
    return 0;
}
