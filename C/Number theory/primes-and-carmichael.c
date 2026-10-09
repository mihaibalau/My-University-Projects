
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// problema 4
// lab 3

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int is_prime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int* get_prime_factors(int n, int* count) {
    int* factors = (int*)malloc(sizeof(int) * 32);
    *count = 0;

    if (n % 2 == 0) {
        factors[*count] = 2;
        (*count)++;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors[*count] = i;
            (*count)++;
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        factors[*count] = n;
        (*count)++;
    }

    return factors;
}

int is_square_free(int n) {
    if (n % 4 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % (i * i) == 0) {
            return 0;
        }
    }
    return 1;
}

void sieve_of_eratosthenes(int n) {
    if (n < 2) {
        printf("Doesn't exist prime numbers lower than %d.\n", n);
        return;
    }

    char* is_prime_arr = (char*)malloc(n);
    memset(is_prime_arr, 1, n);

    is_prime_arr[0] = is_prime_arr[1] = 0;

    for (int i = 2; i * i < n; i++) {
        if (is_prime_arr[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime_arr[j] = 0;
            }
        }
    }

    printf("The prime numbers lower than %d are:\n[ ", n);

    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime_arr[i]) {
            printf("%d ", i);
            count++;
        }
    }
    printf("]\n");
    printf("Total: %d prime numbers\n", count);

    free(is_prime_arr);
}

void carmichael_numbers(int n) {
    if (n < 561) {
        printf("Doesn't exist Carmichael numbers lower than %d.\n", n);
        return;
    }

    printf("\nCarmichael numbers lower than %d:\n[ ", n);

    int carmichael_count = 0;

    for (int num = 561; num < n; num += 2) {

        if (is_prime(num)) continue;
        if (!is_square_free(num)) continue;


        int factor_count = 0;
        int* prime_factors = get_prime_factors(num, &factor_count);

        // Carmichael: (p-1) | (n-1)
        int is_carmichael = 1;
        for (int i = 0; i < factor_count; i++) {
            int p = prime_factors[i];
            if ((num - 1) % (p - 1) != 0) {
                is_carmichael = 0;
                break;
            }
        }

        if (is_carmichael && factor_count > 1) {
            printf("%d ", num);
            carmichael_count++;
        }

        free(prime_factors);
    }

    printf("]\n");
    printf("Total: %d Carmichael numbers\n", carmichael_count);
}

int main() {
    int bound;

    printf("Enter the bound: ");

    scanf("%d", &bound);

    sieve_of_eratosthenes(bound);
    carmichael_numbers(bound);


    return 0;
}
