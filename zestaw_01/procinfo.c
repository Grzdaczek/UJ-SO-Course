#include "procinfo.h"

int procinfo(const char* name) {

    int uid = getuid();
    int gid = getgid();
    int pid = getpid();
    int ppid = getppid();
    int pgid = getpgid(pid);

    printf("Name=%s, UID=%d, GID=%d, PID=%d, PPID=%d, PGID=%d\n", name, uid, gid, pid, ppid, pgid);
    return 0;
}
