#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <err.h>

int main(void) {
    char cmd[10];
    while (1) {
        fgets(cmd, 10, stdin);
        cmd[strlen(cmd) - 1] = '\0';
        if (!strcmp(cmd, "exit") || !strcmp(cmd, "quit")) {
            return 0;
        }
        pid_t pid = fork();
        if (pid == 0) {
            if (execlp(cmd, cmd, NULL) < 0) {
                err(STDOUT_FILENO, NULL);
                return 1;
            }
            return 0;
        }
        //wait(NULL);
    }
    return 0;
}
