#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

int cmp_int(const void *a, const void *b){ return (*(int*)a - *(int*)b); }

char* isValid(char* s) {
    int freq[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) freq[s[i]-'a']++;

    int a[26]; int m = 0;
    for (int i = 0; i < 26; i++) if (freq[i] > 0) a[m++] = freq[i];

    if (m <= 1) return "YES";
    qsort(a, m, sizeof(int), cmp_int);

    int x = a[0], y = a[m-1];
    if (x == y) return "YES";

    int cx = 0; while (cx < m && a[cx] == x) cx++;
    int cy = 0; while (cy < m && a[m-1-cy] == y) cy++;

    if (x == 1 && cx == 1 && a[1] == y) return "YES";
    if (y == x + 1 && cy == 1 && a[m-2] == x) return "YES";

    return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    char* s = readline();
    char* result = isValid(s);
    fprintf(fptr, "%s\n", result);
    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024, data_length = 0;
    char* data = malloc(alloc_length);
    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) { data = '\0'; break; }
    }
    if (data_length > 0 && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) data = '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) data = '\0';
        else data[data_length] = '\0';
    }
    return data;
}
