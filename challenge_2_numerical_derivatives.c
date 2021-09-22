#include<stdio.h>
#include<stdlib.h>

double f(double x);
double F(double x);

int main() {
    /* this is the point in which the derivative of F(x) will be calculated */
    double x = 2;

    printf("%.3f", f(x));

    return EXIT_SUCCESS;
}

/* f(x) calculates the numerical derivative of F(x) */
/* the method used to calculate the numerical derivate is the central difference */
/* I discarded the error since I can decide the value of h in the usual expression */
double f(double x) {
    /* this is the value of h in the usual expression. It can be made smaller to make the derivative more precise */
    double precision = 0.00001;
    double a = F(x+precision);
    double b = F(x-precision);

    return (a-b)/(2*precision);
}

/* F(x) is the function whose derivate will be calculated */
double F(double x) {
    /* the function in question can be changed at ease */
    double y = x*x + 4*x;
    return y;
}
