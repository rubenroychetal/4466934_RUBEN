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
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0) return false;
    return true;
}

void generate_primes(int* primes, int q) {
    int count = 0, num = 2;
    while (count < q) {
        if (is_prime(num)) {
            primes[count++] = num;
        }
        num++;
    }
}

typedef struct {
    int* data;
    int top;
} Stack;

void push(Stack* s, int val) {
    s->data[++(s->top)] = val;
}

int pop(Stack* s) {
    return s->data[(s->top)--];
}

bool is_empty(Stack* s) {
    return s->top == -1;
}


int* waiter(int number_count, int* number, int q, int* result_count) {
    int* primes = malloc(q * sizeof(int));
    generate_primes(primes, q);

    Stack* A = malloc(sizeof(Stack));
    A->data = malloc(number_count * sizeof(int));
    A->top = -1;

    for (int i = 0; i < number_count; i++)
        push(A, number[i]);

    int* answers = malloc(number_count * sizeof(int));
    int ans_index = 0;

    for (int i = 0; i < q; i++) {
        Stack* B = malloc(sizeof(Stack));
        B->data = malloc(number_count * sizeof(int));
        B->top = -1;

        Stack* next_A = malloc(sizeof(Stack));
        next_A->data = malloc(number_count * sizeof(int));
        next_A->top = -1;

        while (!is_empty(A)) {
            int val = pop(A);
            if (val % primes[i] == 0)
                push(B, val);
            else
                push(next_A, val);
        }

        while (!is_empty(B))
            answers[ans_index++] = pop(B);

        free(A->data);
        free(A);
        free(B->data);
        free(B);

        A = next_A;
    }

    while (!is_empty(A))
        answers[ans_index++] = pop(A);

    free(A->data);
    free(A);
    free(primes);

    *result_count = ans_index;
    return answers;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int q = parse_int(*(first_multiple_input + 1));

    char** number_temp = split_string(rtrim(readline()));

    int* number = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int number_item = parse_int(*(number_temp + i));

        *(number + i) = number_item;
    }

    int result_count;
    int* result = waiter(n, number, q, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
