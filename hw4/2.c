#include <unistd.h>
#include <fcntl.h>
#include <err.h>

void print(int num) {
    if (num == 0) {
        return;
    }
    print(num / 10);
    char ch = num % 10 + '0';
    if (write(STDOUT_FILENO, &ch, 1) < 0) {
        err(STDOUT_FILENO, NULL);
        return;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        write(STDOUT_FILENO, "wrong number of arguments\n", 27);
        return 1;
    }
    ssize_t fd;
    int state = 1;
    int bytes = 0;
    int words = 0;
    int newline = 0;
    char ch;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        err(STDOUT_FILENO, "failed to open file");
        return 1;
    }
    while (read(fd, &ch, 1)) {
        bytes++;
        if (ch == ' ' || ch =='\t') {
            state = 1;
        } else if (ch == '\n') {
            newline++;
            state = 1;
        } else if (state) {
            words++;
            state = 0;
        }
    }
    print(newline);
    write(STDOUT_FILENO, " ", 1);
    print(words);
    write(STDOUT_FILENO, " ", 1);
    print(bytes);
    write(STDOUT_FILENO, "\n", 1);
    if (close(fd) < 0) {
        err(STDOUT_FILENO, "failed to close file");
        return 1;
    }
    return 0;
}
