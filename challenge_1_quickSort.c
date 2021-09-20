#include<stdio.h>

void quickSort(int A[], int lbound, int ubound);
int partition(int A[], int lbound, int ubound);

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

    quickSort(A,0,7);
    for (int i = 0; i < 8; ++i) {
        printf("%d\n",A[i]);
    }

    return 0;
}


/* quickSort algorithm */
void quickSort(int A[], int lbound, int ubound) {
    if (lbound < ubound) {
        int loc = partition(A,lbound,ubound);
        quickSort(A,lbound,loc-1);
        quickSort(A,loc+1,ubound);
    }
}

/* back-bone of quickSort algorithm, uses the first element from the subarray as the pivot */
int partition(int A[], int lbound, int ubound) {
    int pivot = A[lbound];
    int start = lbound;
    int end = ubound;

    while (start < end) {
        /* the ideia is that every element lesser than the pivot element must be on the left of the pivot element */
        /* and every element greater than the pivot element must be on the right of the pivot element */
        while (A[start] <= pivot) {
            ++start;
        }
        while (A[end] > pivot) {
            --end;
        }
        if (start < end) {
            int t = A[start];
            A[start] = A[end];
            A[end] = t;
        }
    }
    /* when start >= end, it means that at this point, if we swap the pivot element with the end element, the subarray will be as we want */
    int t = A[lbound];
    A[lbound] = A[end];
    A[end] = t;
    return end;
}
