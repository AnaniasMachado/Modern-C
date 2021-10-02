#include<stdio.h>

/* vector to vector product */
void vec2vec_prod(int A[], int B[], int n) {
    for (int i = 0; i < n; ++i)
        A[i] *= B[i];
}

/* matrix to vector product */
/* let's suppose that A is a m x n matrix and B is a n x 1 vector */
void matrix2vec_prod(int m, int n, int A[][n], int B[]) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            A[i][j] *= B[j];
    }
}

/* copy the values from row A to row B */
void copy_row(int n, double A[], double B[]) {
    for (int i = 0; i < n; ++i)
        B[i] = A[i];
}

/* prints the elements of a m x n matrix A*/
void print_matrix(int m, int n, double A[][n]) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            printf("A[%d][%d] = %3.3lf\t", i, j, A[i][j]);
        printf("\n");
    }
}

/* swap the values of two rows (aka arrays) */
void swap_rows(double A[], double B[], int n) {
    for (int i = 0; i < n; ++i) {
        unsigned temp = A[i];
        A[i] = B[i];
        B[i] = temp;
    }
}

/* multiply each value of a row (aka array) by a non-zero constant c */
void mult_row(double A[], int n, double c) {
    if (c != 0) {
        for (int i = 0; i < n; ++i)
            A[i] *= c;
    }
}

/* add the respective values of row (aka array) B to row A */
void add_rows(double A[], double B[], int n) {
    for (int i = 0; i < n; ++i)
        A[i] += B[i];
}

/* searches for a row where the element in the designated column is not 0 */
int find_pivot(int m, int n, double A[][n], int col, int start) {
    for (int i = start; i < m; ++i) {
        if (A[i][col] != 0.0) {
            return i;
        }
    }
    return -1;
}

/* does the gaussian elimination in a given matrix m x n A */
void gaussian_elimination(int m, int n, double A[][n]) {
    int p;
    /* if the number of rows in matrix A is equal or greater than the number of columns */
    if (m >= n)
        p = n;
    /* if the number of columns is greater than the number of rows */
    else
        p = m;
    
    int row = 0;
    int col = 0;
    while (p) {
        /* pr stands for pivot row */
        int pr = find_pivot(m, n, A, col, row);
        /* if there is not pivot in this column, search in the next column for a pivot */
        if (pr == -1) {
            --p;
            ++col;
            continue;
        }
        /* swaps the pivot row to the current value of row if necessary*/
        if (pr != row)
            swap_rows(A[row], A[pr], n);
        /* pivot value now is 1 */
        mult_row(A[row], n, (1.0/A[row][col]));

        /* reduce to 0 the value of all elements below the pivot column
        if the element is already 0, no need to do something */
        for (int i = row+1; i < m; ++i) {
            if (!A[i][col])
                continue;
            else {
                /* makes the element on the column below the pivot -1 to add the pivot row right after */
                mult_row(A[i], n, (-1.0/A[i][col]));
                add_rows(A[i], A[row], n);
            }
        }
        for (int i = 0; i < row; ++i) {
            if (!A[i][col])
                continue;
            else {
                double B[n];
                copy_row(n, A[row], B);
                mult_row(B, n, (-A[i][col]/A[row][col]));
                add_rows(A[i], B, n);
            }
        }
        --p;
        ++row;
        ++col;
        //print_matrix(n, n, A);
    }
}

/* Creates a matrix B where B = [A I], where I is the identity matrix */
void extended_matrix(int n, double A[][n], double B[][2*n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2*n; ++j) {
            if (i < n && j < n)
                B[i][j] = A[i][j];
            else {
                if (i == (j-n))
                    B[i][j] = 1.0;
                else
                    B[i][j] = 0.0;
            }
        }
    }
}

/* calculates the matrix inversion of a given matrix A of order n */
void matrix_inversion(int n, double A[][n]) {
    double B[n][2*n];
    /* B = [A I] */
    extended_matrix(n, A, B);
    /* when using the gaussian elimination in B, we will get B = [I A^(-1)]*/
    gaussian_elimination(n, 2*n, B);

    /* now the just modify A so that A is inverted */
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = B[i][j+n];
        }
    }
}

int main() {
    double A[][5] = {
        {2.0, 4.0, 6.1, 4.2, 3.3},
        {7.0, 5.0, 6.1, 1.2, 9.3},
        {31.0, 84.0, 6.1, 44.2, 1.3},
        {4.2, 6.1, 6.1, 63.2, 54.3}
    };
    double D[][2] = {
        {2.0, 0.0},
        {0.0, 4.0}
    };
    double E[2][4];
    matrix_inversion(2, D);
    print_matrix(2, 2, D);
}
