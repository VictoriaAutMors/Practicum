#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    int i, num = atoi(argv[1]);
    for (i = 0; i < num; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("%u %u\n", getpid(), getppid());
            break;
        }
    }
    return 0;
}
