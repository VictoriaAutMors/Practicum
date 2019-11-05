#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>

int is_prime(int n)
{
    int i = 2, tmp = n / 2;
    while (i <= tmp) {
        if (n % i == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

void wait_to_end(int num)
{
    for (int i = 0; i < num; i++) {
        wait(NULL);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    int pd[2];
    int i, j, tmp, ans = 0, num = atoi(argv[1]), num_kernel = get_nprocs();
    for (i = 2; i < num; i += num_kernel) {
        if (pipe(pd) < 0) {
            err(1, NULL);
        }
        for (j = 0; j < num_kernel && i + j <= num; j++) {
            if (fork() == 0) {
                int res = is_prime(i + j);
                if (write(pd[1], &res, sizeof(int)) < 0) {
                    err(1, NULL);
                }
                close(pd[1]);
                close(pd[0]);
                return 0;
            }
        }
        wait_to_end(num_kernel);
        for (int c = 0; c < num_kernel; c++) {
            if (read(pd[0], &tmp, sizeof(int)) == -1) {
                err(1, NULL);
            }
            ans += tmp;
        }
        close(pd[1]);
        close(pd[0]);
    }
    printf("%d\n", ans);
    return 0;
}
