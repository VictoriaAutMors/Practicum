#include <unistd.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        write(STDOUT_FILENO, "No arguments\n", sizeof("No arguments\n"));
        return 1;
    }
    ssize_t fd;
    int i;
    char ch;
    for (i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            err(STDOUT_FILENO, "failed to open file '%s'", argv[1]);
            return 1;
        }
        while (read(fd, &ch, 1) > 0) {
            if (write(STDOUT_FILENO, &ch, 1) < 0) {
                close(fd);
                err(STDOUT_FILENO, "failed to write");
            }
        }
        if (close(fd) < 0) {
            err(STDOUT_FILENO, "failed to close");
            return 1;
        }
    }
    return 0;
}
