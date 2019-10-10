#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd, ch, i;
    for (i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            write(STDOUT_FILENO, "open error\n", 11);
            return 1;
        }
        while (read(fd, &ch, 1)) {
            write(STDOUT_FILENO, &ch, 1);
        }
        close(fd);
    }
    return 0;
}
