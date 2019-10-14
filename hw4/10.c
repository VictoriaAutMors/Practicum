#include <math.h>
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


int maxfg(int a, int b, int c, int d){
    if(a > b){
        if(a > c){
            if(a > d){
                return a;
            }
            else{
                return d;
            }
        }
        else{
            if(c > d){
                return c;
            }
            else{
                return d;
            }
        }
    }
    else{
        if(b > c){
            if(b > d){
                return b;
            }
            else{
                return d;
            }
        }
        else{
            if(c > d)
            {
                return c;
            }
            else{
                return d;
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        write(STDOUT_FILENO, "wrong arguments\n", 16);
        return 1;
    }
    struct Image img = openImage(argv[1]);
    int **d;
    d = (int **)malloc(sizeof(int *) * img.h);
    for (int i = 0; i < img.h; i++) {
        d[i] = (int *)malloc(sizeof(int) * img.w);
    }
    for (int i = 0; i < img.h; i++) {
        for (int j = 0; j < img.w; j++) {
            d[i][j] = img.pixmap[i][j].r + img.pixmap[i][j].g + img.pixmap[i][j].b;
        }
    }
    int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT,  S_IRUSR | S_IWUSR);
    char *preheader = img.preheader, *postheader = img.postheader;
    int w = img.w, h = img.h;
    write(fd, preheader, sizeof(img.preheader));
    write(fd, &w, sizeof(img.w));
    write(fd, &h, sizeof(img.h));
    write(fd, postheader, sizeof(img.postheader));
    for (int i = 1; i < img.h - 1; i++) {
        for (int j = 1; j < img.w - 1; j++) {
            if (maxfg(abs(d[i][j] - d[i][j + 1]), abs(d[i][j] - d[i][j - 1]), 
            abs(d[i][j] - d[i - 1][j]), abs(d[i][j] - d[i + 1][j])) < *argv[3]){
                img.pixmap[i][j].b = 255,  img.pixmap[i][j].g = 255,  img.pixmap[i][j].r = 255;
            }
            else{
                img.pixmap[i][j].b = 0, img.pixmap[i][j].g = 0, img.pixmap[i][j].r = 0;
            }
        }
    }
    for (int i = 0; i < img.h; i++){
        for (int j = 0; j < img.w; j++) {
            write(fd, &img.pixmap[i][j], sizeof(struct Pixel));
        }
    }
    close(fd);
    for (int i = 0; i < img.h; i++) {
        free(img.pixmap[i]);
    }
    free(img.pixmap);
    for (int i = 0; i < img.h; i++) {
        free(d[i]);
    }
    free(d);
    return 0;
}
