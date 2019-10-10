#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd, fd2, ch;
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(STDOUT_FILENO, "open error\n", 11);
        return 1;
    }
    while (read(fd, &ch, 1)) {
        write(fd2, &ch, 1);
    }
    close(fd);
    close(fd2);
    return 0;
}
