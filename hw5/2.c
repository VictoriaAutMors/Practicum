#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <err.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    DIR *fd;
    int len;
    struct dirent *dir = NULL;
    char *name = NULL;
    fd = opendir(".");
    while ((dir = readdir(fd)) != NULL) {
        if (strstr(dir -> d_name, ".c") != NULL) {
            if (fork() == 0) {
                len = strlen(dir -> d_name) - 2;
                name = (char *)malloc(len + 1);
                strncpy(name, dir -> d_name, len);
                name[len] = 0;
                if (execlp("gcc", "gcc", dir -> d_name, "-o", name, NULL) < 0) {
                    perror(NULL);
                }
                free(name);
                return EXIT_SUCCESS;
            }
            wait(NULL);
        }
    }
    closedir(fd);
    puts("Completed");
    return 0;
}
