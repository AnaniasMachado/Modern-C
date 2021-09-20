#include<stdio.h>

void mergeSort(int A[],int B[],int lbound, int ubound);
void merge(int A[],int B[],int lbound, int mid, int ubound);
void copy(int A[],int B[],int n);

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
    /* divide in half until cannot anymore, then proceeds to merge the "array" of one element */
    if (lbound < ubound) {
        mergeSort(A,B,lbound,mid);
        mergeSort(A,B,mid+1,ubound);
    }
    /* the merge occurs adding in array B the elements from array A in a sorted way */
    merge(A,B,lbound,mid,ubound);
    /* copy the contents of array B to array A, since the array B is an sorted, array A will also be */
    copy(A,B,ubound);
}

/* the merge occurs adding in array B the elements from array A in a sorted way */
void merge(int A[],int B[],int lbound, int mid, int ubound) {
    int i = lbound;
    int j = mid + 1;
    int k = lbound;
    /* stating from the beginning of each domain, we check which one is smaller and add it to the begin of array B */
    /* then we increment the starting point in the domain from which was the smaller element and repeat the process until one of the domains is exhausted */
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
    /* when one of the domains is exhausted, we chech which one is not and then we add the remaining elements from it to the array B */
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

/* copy elements from array B to array A */
void copy(int A[],int B[],int n) {
    for (int i = 0; i <= n; ++i) {
        A[i] = B[i];
    }
}
