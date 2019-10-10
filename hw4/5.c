#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int i, num = atoi(argv[1]);
    pid_t pid = fork();
    for (i = 0; i < num; i++) {
        if (pid != 0) {
            break;
        }
        printf("%u %u\n", getpid(), getppid());
        pid = fork();
    }
    return 0;
}
