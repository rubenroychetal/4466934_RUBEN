#include <stdio.h>

// Function to flip all 32 bits of the given unsigned integer
unsigned int flippingBits(unsigned int n) {
    return ~n; // Bitwise NOT flips all bits (1s to 0s and 0s to 1s)
}

int main() {
    int q;
    scanf("%d", &q); // Read number of queries

    for (int i = 0; i < q; i++) {
        unsigned int n;
        scanf("%u", &n); // Read each unsigned 32-bit integer
        unsigned int result = flippingBits(n);
        printf("%u\n", result); // Print the flipped result
    }

    return 0;
}
