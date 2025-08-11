#include <stdio.h>
#include <stdlib.h>

int* dynamicArray(int n, int queries_rows, int queries_columns, int** queries, int* result_count) {
    int** seqList = malloc(n * sizeof(int*));   
    int* seqSizes = calloc(n, sizeof(int));     
    int lastAnswer = 0;

    for (int i = 0; i < n; i++) {
        seqList[i] = NULL; 
    }

    int* results = malloc(queries_rows * sizeof(int)); 
    *result_count = 0;

    for (int i = 0; i < queries_rows; i++) {
        int type = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];

        int idx = (x ^ lastAnswer) % n;

        if (type == 1) {
            seqList[idx] = realloc(seqList[idx], (seqSizes[idx] + 1) * sizeof(int));
            seqList[idx][seqSizes[idx]++] = y;
        }
        else if (type == 2) {
            int size = seqSizes[idx];
            lastAnswer = seqList[idx][y % size];
            results[*result_count] = lastAnswer;
            (*result_count)++;
        }
    }

    for (int i = 0; i < n; i++) {
        free(seqList[i]);
    }
    free(seqList);
    free(seqSizes);

    return results;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int** queries = malloc(q * sizeof(int*));
    for (int i = 0; i < q; i++) {
        queries[i] = malloc(3 * sizeof(int));
        scanf("%d %d %d", &queries[i][0], &queries[i][1], &queries[i][2]);
    }

    int result_count;
    int* result = dynamicArray(n, q, 3, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }

    for (int i = 0; i < q; i++) {
        free(queries[i]);
    }
    free(queries);
    free(result);

    return 0;
}
