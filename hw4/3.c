#include <unistd.h>
#include <fcntl.h>
#include <err.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        write(STDOUT_FILENO, "wrong number of arguments\n", 27);
        return 1;
    }
    ssize_t fd_in, fd_out;
    char ch;
    fd_in = open(argv[1], O_RDONLY);
    if (fd_in < 0) {
        err(STDOUT_FILENO, "failed to open file '%s'", argv[1]);
        return 1;
    }
    fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd_out < 0) {
        err(STDOUT_FILENO, "failed to open '%s'", argv[2]);
        close(fd_in);
        return 1;
    }
    while (read(fd_in, &ch, 1) > 0) {
        if (write(fd_out, &ch, 1) < 0) {
            err(STDOUT_FILENO, "failed to write");
            close(fd_in);
            close(fd_out);
            return 1;
        }
    }
    close(fd_in);
    close(fd_out);
    return 0;
}
