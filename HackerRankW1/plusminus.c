#include <stdio.h>
#include <stdlib.h>

void plusMinus(int arr_count, int* arr) {
    int positive = 0, negative = 0, zero = 0;

    for (int i = 0; i < arr_count; i++) {
        if (arr[i] > 0)
            positive++;
        else if (arr[i] < 0)
            negative++;
        else
            zero++;
    }

    printf("%.6f\n", (float)positive / arr_count);
    printf("%.6f\n", (float)negative / arr_count);
    printf("%.6f\n", (float)zero / arr_count);
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    plusMinus(n, arr);

    free(arr);
    return 0;
}
