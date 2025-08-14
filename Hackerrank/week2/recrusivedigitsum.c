#include <stdio.h>
#include <string.h>

long long superDigit(long long num) {
    if (num < 10) return num; 
    long long sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return superDigit(sum);
}

int main() {
    char n[100001]; 
    long long k;
    scanf("%s %lld", n, &k);

    long long sum = 0;
    for (int i = 0; i < strlen(n); i++) {
        sum += (n[i] - '0');
    }

    long long initial = sum * k; 
    printf("%lld\n", superDigit(initial));

    return 0;
}
