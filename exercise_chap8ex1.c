#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>
#include<string.h>
#include<time.h>
#include<tgmath.h>

/* Converts a given number in the form of a string to a double */
double my_strtod(char* s) {
    double n = 0;
    char *sa;
    int dot = 0; /* Flag to check if there was a dot */ 
    int divs = 0; /* Count how many times we will need to divide by 10 later */
    for (sa = s; *sa != '\0'; sa++) { /* Iterates through the string using a pointer */
        if (!dot) { /* If we didn't get to a dot, then we just do this */
            if (*sa != '.') {
                n = n*10 + (*sa - '0'); /* The " - '0' "" converts the string to a int */
            }
            else { /* Flag */
                dot = 1;
            }
        }
        else { /* Increases n as if we were dealing the a non decimal double */
            n = n*10 + (*sa - '0');
            ++divs; /* However, we are keep tracking of how many times will need to divide by 10 
                    to have a decimal part */
        }
    }
    while (divs) { /* Divides by 10 as much as necessary */
        n = n / 10;
        --divs;
    }
    return n;
}

int main(int argc, char* argv[argc+1]) {
    clock_t tStart = clock();
    if (argc >= 2)
        printf("argv[1]: %lf\n", my_strtod(argv[1]));
    printf("Time taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
