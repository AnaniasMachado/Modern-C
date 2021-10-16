#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<string.h>
#include<time.h>
#include<tgmath.h>

void printsieve(size_t n, size_t A[]) {
    for (size_t i = 0; i < n; ++i) {
        printf("%3d ", i+2);
    }
    printf("\n");
    for (size_t i = 0; i < n; ++i) {
        printf("%3d ", A[i]);
    }
    printf("\n");
}

/* Gets all the prime numbers up to n in the form of a array of
true or false values, where a element is true if its index+2 is
a prime number. */
void sieve_of_eras(size_t n, size_t A[n]) {
    for (size_t i = 0; i < n; ++i)
        A[i] = 1;
    size_t p;
    
    for (size_t i = 2; i < pow(n, 0.5); ++i) {
        if (A[i]) {
            p = i*i;
            while (p < n+2) {
                if (A[p-2])
                    A[p-2] = 0;
                p = p+i;
            }
        }
    }
}

/* Prints out all the prime factors of a given number N */
void factorDo(size_t N) {
    size_t A[N];
    sieve_of_eras(N, A);
    /* Under the assumption that to a arbitrary number N 
    less than half of the number from 0 to N are prime 
    we create this array B to store the primes that we
    encountered with the sieve function. */
    size_t B[N];
    size_t idx = 0;

    /* First we initialize B with 0s */
    for (size_t i = 0; i < N; ++i)
        B[i] = 0;
    
    /* Then we substitute the first values to the primes */
    for (size_t i = 0; i < N-1; ++i) {
        if (A[i]) {
            B[idx] = i+2;
            ++idx;
        }
    }

    size_t ub = N;

    for (size_t j = 0; j < ub; ++j) {
        if (B[j]) {
            size_t rem = N % B[j];
            if (!rem) {
                printf("%zu ", B[j]);
                N = N / B[j];
            }
        }
    }
    printf("\n");
}

/* Executes factorDo to a given list of numbers given by the command line. */
void factor(size_t n, char* A[n]) {
    for (size_t i = 1; i < n; ++i) {
        factorDo(atoi(A[i]));
    }
}

int main(int argc, char* argv[argc+1]) {
    clock_t tStart = clock();
    // Checks if some parameter was passed to be used in the factor function.
    if (argc >= 2)
        factor(argc, argv);
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
