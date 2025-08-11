#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_occurrences(char **strings, int strings_count, char *query) {
    int count = 0;
    for (int i = 0; i < strings_count; i++) {
        if (strcmp(strings[i], query) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    char **strings = malloc(n * sizeof(char *));
    
    for (int i = 0; i < n; i++) {
        strings[i] = malloc(101 * sizeof(char));
        scanf("%s", strings[i]);
    }

    int q;
    scanf("%d", &q);
    char **queries = malloc(q * sizeof(char *));
    
    for (int i = 0; i < q; i++) {
        queries[i] = malloc(101 * sizeof(char));
        scanf("%s", queries[i]);
    }

    for (int i = 0; i < q; i++) {
        int result = count_occurrences(strings, n, queries[i]);
        printf("%d\n", result);
    }

    for (int i = 0; i < n; i++) free(strings[i]);
    for (int i = 0; i < q; i++) free(queries[i]);
    free(strings);
    free(queries);

    return 0;
}
