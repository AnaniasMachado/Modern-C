#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <tgmath.h>
#include <float.h>
#include <time.h>

// Calculates a numeric derivative of a given function using the central difference method
// Source: https://en.wikipedia.org/wiki/Finite_difference
// TDLR Explanation: https://math.stackexchange.com/a/888280
double generic_derivative(double (*F) (double), double x) {
    double precision = 0.000000001;
    double (*fn) (double) = F;
    double a = (*fn)(x + precision);
    double b = (*fn)(x - precision);

    return (a-b)/(2*precision);
}

// Calculates the root of a given function using the Newton's method
// Source: https://en.wikipedia.org/wiki/Newton's_method
double newtons_method(double (*F) (double), double x) {
    double precision = 0.000000001;
    double (*fn) (double) = F;
    double guess = x;
    
    while ((*fn)(guess) > precision) {
        guess = guess - (*fn)(guess) / generic_derivative(F, guess);
    }

    return guess;
}

// Function to test Newton's method
double func0(double x) {
    double output = 5*x*x - 25;
    return output;
}

// Another function to test Newton's method
double func1(double x) {
    double output = 4*x*x - 2;
    return output;
}

// gcc -std=c17 -Wall t0.c -o ./bin/t0 -lm
int main(int argc, char* argv[argc+1]) {
    clock_t start = clock();

    //double parametric;
    double param = 8;

    //Testing the generic derivative function
    printf("cos(%lf):\n", param);
    printf("numerical derivate = %lf\n", generic_derivative(&cos, param));
    printf("actual derivative = %lf\n", -sin(param));

    printf("tan(%lf):\n", param);
    printf("numerical derivate = %lf\n", generic_derivative(&tan, param));
    printf("actual derivative = %lf\n", 1/(cos(param)*cos(param)));

    //Testing the Newton's method function
    printf("func0's root: %lf\n", newtons_method(&func0, param));
    printf("func1's root: %lf\n", newtons_method(&func1, param));

    // Time taken
    printf("Time taken: %.8fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}