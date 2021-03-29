#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "procinfo.h"

int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) {
        if (!fork()) sleep(1);
    }
    procinfo(argv[0]);
    while (wait(NULL) != -1);
}
