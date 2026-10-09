#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
typedef struct {
    struct timespec start;
    struct timespec end;
} timer_t;

void timer_start(timer_t *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->start);
}

long long timer_end(timer_t *timer) {
    clock_gettime(CLOCK_MONOTONIC, &timer->end);

    long long start_ns = timer->start.tv_sec * 1000000000LL + timer->start.tv_nsec;
    long long end_ns = timer->end.tv_sec * 1000000000LL + timer->end.tv_nsec;

    return end_ns - start_ns;
}

void print_time(long long nanoseconds) {
    if (nanoseconds < 1000000) {
        printf("%.2f ns", (double)nanoseconds);
    } else if (nanoseconds < 1000000000) {
        printf("%.2f ms", (double)nanoseconds / 1000000.0);
    } else {
        printf("%.2f s", (double)nanoseconds / 1000000000.0);
    }
}

// ============================================================================
// BIG INTEGER FUNCTIONS
// ============================================================================

int compare_bigint(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;

    return strcmp(a, b);
}

void subtract_bigint(char *result, const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = len_a > len_b ? len_a : len_b;

    int *num_a = (int*)calloc(max_len + 1, sizeof(int));
    int *num_b = (int*)calloc(max_len + 1, sizeof(int));
    int *num_result = (int*)calloc(max_len + 1, sizeof(int));

    for (int i = 0; i < len_a; i++) {
        num_a[len_a - 1 - i] = a[i] - '0';
    }
    for (int i = 0; i < len_b; i++) {
        num_b[len_b - 1 - i] = b[i] - '0';
    }

    int borrow = 0;
    for (int i = 0; i < max_len; i++) {
        int diff = num_a[i] - num_b[i] - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        num_result[i] = diff;
    }

    int start = max_len - 1;
    while (start > 0 && num_result[start] == 0) start--;

    int idx = 0;
    for (int i = start; i >= 0; i--) {
        result[idx++] = num_result[i] + '0';
    }
    result[idx] = '\0';

    free(num_a);
    free(num_b);
    free(num_result);
}

void mod_bigint(char *result, const char *a, const char *b) {
    strcpy(result, a);

    while (compare_bigint(result, b) >= 0) {
        char temp[1000];
        subtract_bigint(temp, result, b);
        strcpy(result, temp);
    }
}

int is_zero(const char *num) {
    return strcmp(num, "0") == 0;
}

// ============================================================================
// ALGORITM 1: EUCLIDEAN
// ============================================================================

unsigned long long gcd_euclidean(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void gcd_euclidean_bigint(char *result, const char *a, const char *b) {
    char num_a[1000], num_b[1000];
    strcpy(num_a, a);
    strcpy(num_b, b);

    while (!is_zero(num_b)) {
        char temp[1000];
        mod_bigint(temp, num_a, num_b);
        strcpy(num_a, num_b);
        strcpy(num_b, temp);
    }

    strcpy(result, num_a);
}

// ============================================================================
// ALGORITM 2: BINARY GCD
// ============================================================================

unsigned long long gcd_binary(unsigned long long a, unsigned long long b) {
    if (a == 0) return b;
    if (b == 0) return a;

    int shift = 0;
    while (((a | b) & 1) == 0) {
        a >>= 1;
        b >>= 1;
        shift++;
    }

    while ((a & 1) == 0) {
        a >>= 1;
    }

    do {
        while ((b & 1) == 0) {
            b >>= 1;
        }

        if (a > b) {
            unsigned long long temp = a;
            a = b;
            b = temp;
        }

        b = b - a;
    } while (b != 0);

    return a << shift;
}

// ============================================================================
// ALGORITM 3: SUBTRACTION
// ============================================================================

unsigned long long gcd_subtraction(unsigned long long a, unsigned long long b) {
    if (a == 0) return b;
    if (b == 0) return a;

    while (a != b) {
        if (a > b) {
            a = a - b;
        } else {
            b = b - a;
        }
    }
    return a;
}

void gcd_subtraction_bigint(char *result, const char *a, const char *b) {
    char num_a[1000], num_b[1000];
    strcpy(num_a, a);
    strcpy(num_b, b);

    while (compare_bigint(num_a, num_b) != 0) {
        if (compare_bigint(num_a, num_b) > 0) {
            char temp[1000];
            subtract_bigint(temp, num_a, num_b);
            strcpy(num_a, temp);
        } else {
            char temp[1000];
            subtract_bigint(temp, num_b, num_a);
            strcpy(num_b, temp);
        }
    }

    strcpy(result, num_a);
}

// ============================================================================

void test_algorithms(unsigned long long a, unsigned long long b) {
    timer_t timer;
    long long total_time1 = 0, total_time2 = 0, total_time3 = 0;
    int iterations = 1000;

    printf("\n========================================\n");
    printf("Testing with a = %llu, b = %llu\n", a, b);
    printf("Iterations: %d\n", iterations);
    printf("========================================\n");

    // Test Euclidean
    for (int i = 0; i < iterations; i++) {
        timer_start(&timer);
        unsigned long long result1 = gcd_euclidean(a, b);
        long long elapsed = timer_end(&timer);
        total_time1 += elapsed;
    }
    printf("1. Euclidean Algorithm:     GCD = %llu\n", gcd_euclidean(a, b));
    printf("   Total time (%d iterations): ", iterations);
    print_time(total_time1);
    printf("\n   Average per iteration:     ");
    print_time(total_time1 / iterations);
    printf("\n");

    // Test Binary
    for (int i = 0; i < iterations; i++) {
        timer_start(&timer);
        unsigned long long result2 = gcd_binary(a, b);
        long long elapsed = timer_end(&timer);
        total_time2 += elapsed;
    }
    printf("2. Binary GCD (Stein):      GCD = %llu\n", gcd_binary(a, b));
    printf("   Total time (%d iterations): ", iterations);
    print_time(total_time2);
    printf("\n   Average per iteration:     ");
    print_time(total_time2 / iterations);
    printf("\n");

    // Test Subtraction
    int iter_sub = iterations;
    if (a > 1000000 || b > 1000000) {
        iter_sub = 10;
    }

    for (int i = 0; i < iter_sub; i++) {
        timer_start(&timer);
        unsigned long long result3 = gcd_subtraction(a, b);
        long long elapsed = timer_end(&timer);
        total_time3 += elapsed;
    }
    printf("3. Subtraction Method:      GCD = %llu\n", gcd_subtraction(a, b));
    printf("   Total time (%d iterations): ", iter_sub);
    print_time(total_time3);
    printf("\n   Average per iteration:     ");
    print_time(total_time3 / iter_sub);
    printf("\n");
}

void test_bigint_algorithms(const char *a, const char *b) {
    char result[1000];
    timer_t timer;
    long long total_time1 = 0;
    int iterations = 100;

    printf("\n========================================\n");
    printf("Testing BIG INTEGERS\n");
    printf("a = %s\n", a);
    printf("b = %s\n", b);
    printf("========================================\n");

    // Test Euclidean
    timer_start(&timer);
    gcd_euclidean_bigint(result, a, b);
    long long elapsed = timer_end(&timer);
    total_time1 += elapsed;

    gcd_euclidean_bigint(result, a, b);
    printf("1. Euclidean Algorithm:     GCD = %s\n", result);
    printf("   Total time: ");
    print_time(total_time1);
    printf("\n");
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    printf("PUBLIC KEY CRYPTOGRAPHY - Lab 1\n");
    printf("Greatest Common Divisor (GCD) - 3 Algorithms\n");

    test_algorithms(48, 18);
    test_algorithms(1071, 462);
    test_algorithms(123456, 789012);
    test_algorithms(1547, 560);
    test_algorithms(123456789, 987654321);
    test_algorithms(17, 19);
    test_algorithms(100, 25);
    test_algorithms(999999, 999999);
    test_algorithms(42, 0);
    test_algorithms(89, 55);

    printf("\n\n");
    printf("========================================\n");
    printf("TESTING WITH ARBITRARY LARGE NUMBERS\n");
    printf("========================================\n");

    test_bigint_algorithms("123456789012345678901234567890",
                          "987654321098765432109876543210");

    printf("\n\n========================================\n");
    printf("COMPARATIVE ANALYSIS SUMMARY\n");
    printf("========================================\n");
    
    return 0;
}
