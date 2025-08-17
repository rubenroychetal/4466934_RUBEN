#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char* text;
char* history[MAX_HISTORY];
int history_top = -1;

void save_state() {
    history[++history_top] = strdup(text);
}

void undo() {
    if (history_top >= 0) {
        strcpy(text, history[history_top]);
        free(history[history_top]);
        history_top--;
    }
}


int main() {
    int Q;
    scanf("%d", &Q);
    text = calloc(MAX_LEN + 1, sizeof(char));

    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            char W[100001];
            scanf("%s", W);
            save_state();
            strcat(text, W);
        } else if (type == 2) {
            int k;
            scanf("%d", &k);
            save_state();
            int len = strlen(text);
            if (k <= len)
                text[len - k] = '\0';
        } else if (type == 3) {
            int k;
            scanf("%d", &k);
            if (k > 0 && k <= strlen(text))
                printf("%c\n", text[k - 1]);
        } else if (type == 4) {
            undo();
        }
    }

    free(text);
    

   
    return 0;
}