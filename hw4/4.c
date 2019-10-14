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
    for (i = 0; i < num; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("%u %u\n", getpid(), getppid());
            return 0;
        } else {
            wait(NULL);
        }
    }
    return 0;
}
