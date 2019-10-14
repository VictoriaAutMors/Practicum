#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

typedef struct image Image;

struct image {
    char preheader[18];
    int w, h;
};

Image openImage(char *filename) {
    Image img;
    int fd = open(filename, O_RDONLY);
    assert(fd >= 0 && "fail to open file");
    read(fd, &img.preheader, sizeof(img.preheader));
    read(fd, &img.w, sizeof(img.w));
    read(fd, &img.h, sizeof(img.h));
    assert(close(fd) >= 0 && "fail to close file");
    return img;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("no arguments\n");
        return 1;
    }
    Image imgur = openImage(argv[1]);
    printf("%d %d\n", imgur.w, imgur.h);
    return 0;
}

