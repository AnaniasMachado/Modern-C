#include<stdio.h>
//#include<stdlib.h>
//#include<stdbool.h>

void mergeSort(int A[],int B[],int lbound, int ubound);
void merge(int A[],int B[],int lbound, int mid, int ubound);
void copy(int A[],int B[],int n);

/* There is some error in the mergeSort or merge functions that is making the program return an
 erroneous array. Take a look at it later and solve it. */

int main() {
    int A[8] = {
        A[0] = 6,
        A[1] = 3,
        A[2] = 9,
        A[3] = 4,
        A[4] = 2,
        A[5] = 0,
        A[6] = 1,
        A[7] = 7,
    };
    int B[8];

    mergeSort(A,B,0,7);
    for (int i = 0; i < 8; ++i) {
        printf("%d\n",B[i]);
    }

    return 0;
}

void mergeSort(int A[],int B[],int lbound, int ubound) {
    int mid = (lbound+ubound)/2;
    if (lbound < ubound) {
        mergeSort(A,B,lbound,mid);
        mergeSort(A,B,mid+1,ubound);
    }
    merge(A,B,lbound,mid,ubound);
    copy(A,B,ubound);
}

void merge(int A[],int B[],int lbound, int mid, int ubound) {
    int i = lbound;
    int j = mid + 1;
    int k = lbound;
    while (i <= mid && j <= ubound) {
        if (A[i] <= A[j]) {
            B[k] = A[i];
            ++i;
        }
        else {
            B[k] = A[j];
            ++j;
        }
        ++k;
    }
    if (i > mid) {
        while (j <= ubound) {
            B[k] = A[j];
            ++j;
            ++k;
        }
    }
    else {
        while (i <= mid) {
            B[k] = A[i];
            ++i;
            ++k;
        }
    }
}

void copy(int A[],int B[],int n) {
    for (int i = 0; i <= n; ++i) {
        A[i] = B[i];
    }
}