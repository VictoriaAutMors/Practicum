#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        write(STDOUT_FILENO, "wrong number of arguments\n", 27);
        return 1;
    }
    char *out;
    char flag1[] = "-Wall";
    char flag2[] = "-Werror";
    int len = strlen(argv[1]) - 2;
    out = (char *)calloc(len, sizeof(argv[1]));
    if (out == NULL) {
        err(STDOUT_FILENO, "failed to allocate memory");
        return 1;
    }
    strncpy(out, argv[1], len);
    if (execlp("gcc", "gcc", argv[1], "-o", out, flag1, flag2, NULL) < 0) {
        err(STDOUT_FILENO, NULL);
        return 1;
    }
    free(out);
    return 0;
}
