#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stddef.h>

void printarray(int n, int A[]) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void printarraychar(int n, char A[]) {
    for (int i = 0; i < n; ++i) {
        printf("%c ", A[i]);
    }
    printf("\n");
}

/*
Create two arrays. One array stores whether a certain element was visited or not and the other one
stores the list of elements to visit. Then, take a and put a in the list of elements visited, check 
the connections that a has and put then in the list of elements to visit. Then, take the first element 
from the array and put it in the list of visited elements, check the connections that this element has
and if its connections aren't in the list of visited or in the array of elements to visit, put them in
the array of elements to visit. Each time you take some element from the list of elements to visited,
check if this element is b. If so, then there is a path from a to b. Else, continue until the list in
empty. If empty, return false. It means that there is not a path from a to b.
*/
bool bfs_find(int n, int A[][n], int a, int b) {
    if (a > n || b > n || a < 0 || b < 0)
        return false;
    int toVisit[n];
    int visited[n];
    int visiting;
    int finding = 1;

    for (int i = 0; i < n; ++i) {
        toVisit[i] = 0;
        visited[i] = 0;
    }

    toVisit[a] = 1;
    while (finding) {
        for (int i = 0; i < n; ++i) {
            if (toVisit[i] && !visited[i]) {
                visiting = i;
                break;
            }
            else if (i+1 == n) {
                finding = 0;
                break;
            }
        }
        if (finding) {
            if (A[visiting][b])
                return true;
            for (int i = 0; i < n; ++i) {
                if (A[visiting][i]) {
                    toVisit[i] = 1;
                }
            }
            visited[visiting] = 1;
        }
    }
    return false;
}

/*
Very similar to the bfs_find, the main difference is that dfs_path returns the path between a to b. To do so is
necessary to give it a array of char to register the path and create a new variable called step to keep track of
each step from a to b which is being registered in the given array.
*/
void dfs_path(int n, int A[][n], int a, int b, char B[]) {
    if (a > n || b > n || a < 0 || b < 0)
        return;
    int toVisit[n];
    int visited[n];
    int visiting;
    int finding = 1;
    int step = -1;

    for (int i = 0; i < n; ++i) {
        toVisit[i] = 0;
        visited[i] = 0;
    }

    toVisit[a] = 1;
    while (finding) {
        for (int i = 0; i < n; ++i) {
            if (toVisit[i] && !visited[i]) {
                //Converts the number to a char and adds it to B
                B[++step] = i + '0';
                visiting = i;
                break;
            }
            else if (i+1 == n) {
                finding = 0;
                break;
            }
        }
        if (finding) {
            if (A[visiting][b]) {
                B[++step] = b + '0';
                return;
            }
            for (int i = 0; i < n; ++i) {
                if (A[visiting][i]) {
                    toVisit[i] = 1;
                }
                else if (i+1 == n) {
                    --step;
                }
            }
            visited[visiting] = 1;
        }
    }
}

/*
We have a adjacency matrix A and we wish to find a spanning tree of the graph that this adjacency matrix
represents, if possible. We are passing to more arrays, B and C, which will be used to create the spanning tree.
B will represent the edges of the graph and C will represent the parent of each edge. Initially, we don't know
how our spanning tree will be, so the parent's array will be initialized with -1, indicating that they are all
unconnected.
*/
void spanning_tree(int n, int A[][n], int C[]) {
    //Initializing the parent array with 0's.
    for (int i = 0; i < n; ++i)
        C[i] = 1 * -1;
    int toVisit[n];
    int visited[n];
    int visiting = 0;
    int finding = 1;
    int count = 1;

    for (int i = 0; i < n; ++i) {
        toVisit[i] = 0;
        visited[i] = 0;
    }

    toVisit[0] = 1;
    while (finding) {
        visited[visiting] = 1;
        printf("In the while finding with visiting = %d\n", visiting);
        for (int i = 0; i < n; ++i) {
            if (A[visiting][i] && !visited[i]) {
                printf("visiting = %d\n", visiting);
                C[i] = visiting;
                toVisit[i] = 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (toVisit[i] && !visited[i]) {
                printf("Inside the for loop\n");
                printf("count = %d\n", count);
                visiting = i;
                ++count;
                break;
            }
            else if (i+1 == n && count < n) {
                printf("count = %d\n", count);
                printf("There is not a spanning tree\n");
                finding = 0;
                return;
            }
        }
        if (count == n)
            return;
    }
}

// int main(int argc, char* argv[argc+1])
int main(void) {
    int A[][4] = {
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 0}
    };
    int n = 4;
    int a = 0;
    int b = 3;
    char B[] = "tttt";
    int C[4] = {0};
    // For all the tests is necessary to provide proper variables
    // Testing for bfs_find
    // if (bfs_find(n, A, a, b))
    //     printf("There is a connection");
    // else
    //     printf("There is not a connection");
    // Testing for dfs_path
    // dfs_path(n, A, a, b, B);
    // printarraychar(n, B);
    spanning_tree(n, A, C);
    for (int i = 0; i < n; ++i)
        printf("%d ", i);
    printf("\n");
    printarray(n, C);
}
