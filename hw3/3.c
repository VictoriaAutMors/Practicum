#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **arr;
    int in;
    scanf("%d", &in);
    arr = (int **)(malloc(in * sizeof(int *)));
    for (int i = 0; i < in; i++) {
        arr[i] = (int *)malloc((i + 1) * sizeof(int *));
        for (int j = 0; j <= i; j++) {
            arr[i][j] = i + j + 2;
        }
    }
    for (int i = 0; i < in; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", arr[i][j]);
        }
        putchar('\n');
    }
    for (int i = 0; i < in; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}
