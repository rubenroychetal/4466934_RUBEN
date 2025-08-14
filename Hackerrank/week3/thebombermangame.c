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
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);


static char** make_full_grid(int r, int c) {
    char** g = (char**)malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        g[i] = (char*)malloc((c + 1) * sizeof(char));
        for (int j = 0; j < c; j++) g[i][j] = 'O';
        g[i][c] = '\0';
    }
    return g;
}

static char** copy_grid(char** grid, int r, int c) {
    char** g = (char**)malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        g[i] = (char*)malloc((c + 1) * sizeof(char));
        memcpy(g[i], grid[i], c + 1);
    }
    return g;
}

static char** detonate(char** grid, int r, int c) {
    char** res = make_full_grid(r, c);       
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'O') {
                res[i][j] = '.';
                if (i > 0)       res[i-1][j] = '.';
                if (i+1 < r)     res[i+1][j] = '.';
                if (j > 0)       res[i][j-1] = '.';
                if (j+1 < c)     res[i][j+1] = '.';
            }
        }
    }
    return res;
}


char** bomberMan(int n, int r, char** grid, int* result_count) {
    int c = (int)strlen(grid[0]);
    *result_count = r;

    if (n == 1)                 return copy_grid(grid, r, c);
    if (n % 2 == 0)             return make_full_grid(r, c);

    char** first = detonate(grid, r, c);
    if (n % 4 == 3)             return first;

    char** second = detonate(first, r, c);
    for (int i = 0; i < r; i++) free(first[i]);
    free(first);
    return second;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int r = parse_int(*(first_multiple_input + 0));
    int c = parse_int(*(first_multiple_input + 1));
    int n = parse_int(*(first_multiple_input + 2));

    char** grid = (char**)malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        char* grid_item = readline();
        grid[i] = grid_item;
    }

    int result_count;
    char** result = bomberMan(n, r, grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", result[i]);
        if (i != result_count - 1) fprintf(fptr, "\n");
    }
    fprintf(fptr, "\n");

    // free allocations
    for (int i = 0; i < r; i++) free(grid[i]);
    free(grid);
    for (int i = 0; i < result_count; i++) free(result[i]);
    free(result);

    fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024, data_length = 0;
    char* data = (char*)malloc(alloc_length);
    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = (char*)realloc(data, alloc_length);
        if (!data) break;
    }
    if (data_length > 0 && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = (char*)realloc(data, data_length);
    } else {
        data = (char*)realloc(data, data_length + 1);
        data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = (char**)realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) return splits;
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = (int)strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
