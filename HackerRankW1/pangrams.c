#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

char* pangrams(char* s) {
    bool alphabet[26] = { false };

    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) {
            char ch = tolower(s[i]); // Convert to lowercase
            alphabet[ch - 'a'] = true;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!alphabet[i]) {
            return "not pangram";
        }
    }

    return "pangram";
}

int main() {
    char s[1001];
    fgets(s, sizeof(s), stdin);

    // Remove newline character if present
    s[strcspn(s, "\n")] = '\0';

    char* result = pangrams(s);
    printf("%s\n", result);

    return 0;
}
