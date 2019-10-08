#include <stdio.h>
#include <stdlib.h>

void print(int in, int **arr) {
    for (int i = 0; i < in; i++) {
        for (int j = 0; j < in; j++) {
            printf("%d ", arr[i][j]);
        }
        putchar('\n');
    }
}

int main(void) {
    int **arr;
    int in;
    int *temp;
    scanf("%d", &in);
    arr = (int **)(malloc(in * sizeof(int *)));
    for (int i = 0; i < in; i++) {
        arr[i] = (int *)malloc(in * sizeof(int *));
        for (int j = 0; j < in; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    temp = arr[0];
    arr[0] = arr[in - 1];
    arr[in - 1] = temp;
    print(in, arr);
    for (int i = 0; i < in; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}
