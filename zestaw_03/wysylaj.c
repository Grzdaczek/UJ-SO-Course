#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    //if(argc != 3) {
    //    errno = EINVAL;
    //    perror("Invalid argument count");
    //    exit(EXIT_FAILURE);
    //}

    //int sig;
    //sscanf(argv[2], "%d", &sig);
    //printf("%d\n", sig);

    int pid = fork();

    execl("obsluga.x", "obsluga.x", "p", "18", NULL);

    sleep(1);
    printf("pid: %d\n", pid);
    
    switch(pid) {
        case -1:
            perror("Fork error");
            break;
        case 0:
            printf("I'm child!");
            //execl("./obsluga.x", "./obsluga.x", "p", "18");
            break;
        default:
            if(kill(pid, 0) != -1) {
                kill(pid, 18);
            }
            else {
                perror("Could not send signal");
            }
    }

    return 0;
}
