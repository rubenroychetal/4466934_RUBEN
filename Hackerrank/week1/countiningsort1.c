#include <stdio.h>
#include <stdlib.h>

int* countingSort(int arr_count, int* arr, int* result_count) {
    // Always return frequency array of size 100
    *result_count = 100;
    int* freq = calloc(100, sizeof(int)); // initialize to 0

    for (int i = 0; i < arr_count; i++) {
        freq[arr[i]]++;
    }

    return freq;
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int result_count;
    int* result = countingSort(n, arr, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d", result[i]);
        if (i != result_count - 1) printf(" ");
    }
    printf("\n");

    free(arr);
    free(result);

    return 0;
}
