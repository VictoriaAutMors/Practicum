#include <unistd.h>
#include <fcntl.h>

void print(int num) {
    if (num == 0) {
        return;
    }
    print(num / 10);
    char ch = num % 10 + '0';
    write(STDOUT_FILENO, &ch, 1);
}

int main(int argc, char **argv) {
    int fd, state = 1;
    char ch;
    int bytes = 0;
    int words = 0;
    int newline = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        write(STDOUT_FILENO, "open error\n", 11);
        return 1;
    }
    while (read(fd, &ch, 1)) {
        bytes++;
        if (ch == ' ' || ch =='\t') {
            state = 1;
        } else if (ch == '\n') {
            newline++;
            state = 1;
        } else if(state) {
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
    close(fd);
    return 0;
}
