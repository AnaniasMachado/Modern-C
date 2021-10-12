#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>

void printarray(size_t n, size_t A[]) {
    for (size_t i = 0; i < n; ++i) {
        printf("%3d ", i);
    }
    printf("\n");
    for (size_t i = 0; i < n; ++i) {
        printf("%3d ", A[i]);
    }
    printf("\n");
}

/*Initialize the array A with -1 indicating that all the nodes are singleton*/
void Parent(size_t n, size_t A[]) {
    for (int i = 0; i < n; ++i)
        A[i] = -1;
}

/*Finds the root of the set which element a belongs*/
size_t Find(size_t A[], size_t a) {
    size_t ra = a;
    while (A[ra] != -1)
        ra = A[ra];
    return ra;
}

/*Union the sets which elements a and b belongs, if those sets arent the same*/
void Union(size_t A[], size_t a, size_t b) {
    size_t ra = Find(A, a);
    size_t rb = Find(A, b);
    if (ra != rb)
        A[ra] = rb;
}

/*Given a element of the set, it changes the parents of all elements from this element to the root (including), 
to a specific value*/
void FindReplace(size_t A[], size_t a, size_t np)  {
    size_t ra = a;
    while (A[ra] != -1) {
        size_t temp = A[ra];
        A[ra] = np;
        ra = temp;
    }
    A[ra] = np;
}

/*Finds the root of a given element and changes the parent of all elements from this element to the root 
(excluding), to the root*/
size_t FindCompress(size_t A[], size_t a) {
    size_t ra = a;
    while (A[ra] != -1) {
        A[ra] = FindCompress(A, A[ra]);
    }
    return ra;
}

// int main(int argc, char* argv[argc+1])
int main(void) {
    size_t n = 8;
    size_t A[8];

    Parent(n, A);
    Union(A, 2, 3);
    Union(A, 1, 5);
    Union(A, 7, 4);
    Union(A, 0, 1);
    //FindCompress(A, 0);
    FindReplace(A, 1, 12);

    printarray(n, A);
}
