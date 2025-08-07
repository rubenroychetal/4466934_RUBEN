#include <stdio.h>
#include <string.h>

int main() {
    char s[1001], t[1001];
    scanf("%s", s);
    scanf("%s", t);

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == t[i])
            putchar('0');
        else
            putchar('1');
    }
    putchar('\n');
    return 0;
}
