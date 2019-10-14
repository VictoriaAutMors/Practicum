#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("no arguments\n");
        return 1;
    }
    int i, num = atoi(argv[1]);
    pid_t pid = fork();
    for (i = 0; i < num; i++) {
        if (pid != 0) {
            wait(NULL);
            return 0;
        }
        printf("%u %u\n", getpid(), getppid());
        pid = fork();
    }
    return 0;
}
