#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 100005

int heap[MAX_SIZE];
int size = 0;


void swap(int* a, int* b) {
    int temp = *a; *a = *b; *b = temp;
}

void heapifyUp(int i) {
    while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void insert(int val) {
    heap[size++] = val;
    heapifyUp(size - 1);
}

int getMin() {
    return heap[0];
}

void delete(int val) {
        for (int i = 0; i < size; i++) {
        if (heap[i] == val) {
            heap[i] = heap[size - 1];
            size--;
            heapifyDown(i);
            break;
        }
    }
}


int main() {
    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        int type, val;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d", &val);
            insert(val);
        } else if (type == 2) {
            scanf("%d", &val);
            delete(val);
        } else if (type == 3) {
            printf("%d\n", getMin());
        }
    }

         return 0;
}