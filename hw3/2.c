#include <stdio.h>
#include <stdlib.h>

int** mtrx_sqr(int in, int **arr, int **ans) {
    for (int i = 0; i < in; i++){
        for (int j = 0; j < in; j++){
            for (int k = 0; k < in; k++) {
                ans[i][j] += arr[i][k] * arr[k][j];
            }
        }
    }
    return ans;
}

void print(int in, int **arr) {
    for (int i = 0; i < in; i++) {
        for (int j = 0; j < in; j++) {
            printf("%d ", arr[i][j]);
        }
        putchar('\n');
    }
}

int main(void) {
    int **arr, **ans;
    int in;
    scanf("%d", &in);
    arr = (int **)(malloc(in * sizeof(int *)));
    ans = (int **)(malloc(in * sizeof(int *)));
    for (int i = 0; i < in; i++) {
        arr[i] = (int *)malloc(in * sizeof(int *));
        ans[i] = (int *)calloc(in, sizeof(int *));
        for (int j = 0; j < in; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    ans = mtrx_sqr(in, arr, ans);
    print(in, ans);
    for (int i = 0; i < in; i++) {
        free(arr[i]);
        free(ans[i]);
    }
    free(arr);
    free(ans);
    return 0;
}
