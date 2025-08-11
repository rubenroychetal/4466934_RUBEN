#include <stdio.h>
#include <stdlib.h>

// Comparator for ascending sort (A)
int compareAsc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparator for descending sort (B)
int compareDesc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

// Function to check if condition is satisfied
char* twoArrays(int k, int A[], int B[], int n) {
    qsort(A, n, sizeof(int), compareAsc);
    qsort(B, n, sizeof(int), compareDesc);

    for (int i = 0; i < n; i++) {
        if (A[i] + B[i] < k)
            return "NO";
    }
    return "YES";
}

int main() {
    int q;
    scanf("%d", &q);  // number of queries

    while (q--) {
        int n, k;
        scanf("%d %d", &n, &k);

        int A[n], B[n];

        // Read array A
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
        }

        // Read array B
        for (int i = 0; i < n; i++) {
            scanf("%d", &B[i]);
        }

        // Output result
        printf("%s\n", twoArrays(k, A, B, n));
    }

    return 0;
}