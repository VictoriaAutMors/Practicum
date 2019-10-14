#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>

struct Pixel{
    unsigned char r, g, b;
};

struct Image {
    char preheader[18];
    int w, h;
    char postheader[28];
    struct Pixel **pixmap;
};

struct Image openImage(char *filename) {
    struct Image img;
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        err(STDOUT_FILENO, NULL);
        return img;
    }
    read(fd, img.preheader, sizeof(img.preheader));
    read(fd, &(img.w), sizeof(img.w));
    read(fd, &(img.h), sizeof(img.h));
    read(fd, img.postheader, sizeof(img.postheader));
    img.pixmap = (struct Pixel**)malloc(img.h * sizeof(struct Pixel*));
    for (int j = 0; j < img.h; j++) {
        img.pixmap[j] = (struct Pixel*)malloc(img.w * sizeof(struct Pixel));
        if (!img.pixmap[j]) {
            err(STDOUT_FILENO, "cant allocate memory");
            close(fd);
            return img;
        }
    }
    for (int i = 0; i < img.h; i++) {
        for (int j = 0; j < img.w; j++) {
            read(fd, &(img.pixmap[i][j]), sizeof(img.pixmap[i][j]));
        }
    }
    close(fd);
    return img;
}

void saveImage(struct Image img, char *filename) {
    int fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        err(STDOUT_FILENO, NULL);
        return;
    }
    char *preheader = img.preheader, *postheader = img.postheader;
    int w = img.w, h = img.h;
    write(fd, preheader, sizeof(img.preheader));
    write(fd, &w, sizeof(img.w));
    write(fd, &h, sizeof(img.h));
    write(fd, postheader, sizeof(img.postheader));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct Pixel* pixel = &(img.pixmap[h - i - 1][w - j - 1]);
            write(fd, pixel, sizeof(struct Pixel));
        }
    }
    close(fd);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        err(STDOUT_FILENO, NULL);
        return 1;
    }
    struct Image img = openImage(argv[1]);
    saveImage(img, argv[2]);
    for (int j = 0; j < img.h; j++) {
        free(img.pixmap[j]);
    }
    free(img.pixmap);
    return 0;
}
