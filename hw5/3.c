#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>

void wait_to_end(int num)
{
    for (int i = 0; i < num; i++) {
        wait(NULL);
    }
}

int main(void)
{
    DIR *fd;
    int len, num_kernel = get_nprocs();
    struct dirent *dir = NULL;
    char *name = NULL;
    fd = opendir(".");
    while ((dir = readdir(fd)) != NULL) {
        for (int j = 0; j < num_kernel && dir != NULL; j++) {
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
            }
            dir = readdir(fd);
        }
        wait_to_end(num_kernel);
    }
    closedir(fd);
    puts("Completed");
    return 0;
}