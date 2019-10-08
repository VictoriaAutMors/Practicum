#include <stdio.h>
#include <stdlib.h>

int num;
int *ans;

void print_ans(void) {
    for (int i = 0; i < num; i++) {
        printf("%d ", *(ans + i));
    }
    putchar('\n');
}

void make_sum(int sum, int num, int* ans) {
    if (sum == 0) {
        print_ans();
        return;
    }
    for (int i = 1; i <= sum; i++) {
        *ans = i;
        make_sum(sum - i, num, ans + 1);
    }
}

int main(void) {
    int sum;
    scanf("%d %d", &sum, &num);
    ans = (int*)malloc(num * sizeof(int));
    make_sum(sum, num, ans);
    free(ans);
    return 0;
}
