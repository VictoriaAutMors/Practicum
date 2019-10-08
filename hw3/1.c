#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int **arr;
    int in, sum;
    scanf("%d", &in);
    arr = (int **)(malloc(in * sizeof(int *)));
    for (int i = 0; i < in; i++) {
        arr[i] = malloc(in * sizeof(int *));
        for (int j = 0; j < in; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = 0; i < in; i++) {
        sum = 0;
        for (int j = 0; j < in; j++) {
            sum += abs(arr[i][j]);
        }
        printf("%d ", sum);
    }
    for (int i = 0; i < in; i++) {
        free(arr[i]);
    }
    free(arr);
    putchar('\n');
    return 0;
}
