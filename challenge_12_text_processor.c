/* The "blob" of text is here represented with a doubly linked list and some functions that
   works with the doubly linked list nodes and does the necessary funcionalities. Each of
   the doubly linked list functions starts with "dll_".
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "doubly_linked_list.c"

void checks_nullpointer(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "malloc could not allocate memory\n");
        abort();
    }
}

// gcc -std=c17 -Wall t3.c -o ./bin/t3 -lm
int main(int argc, char* argv[argc+1]) {
    clock_t start = clock();

    // Initializing a new doubly linked list
    dll_Node *head = (dll_Node*) malloc(sizeof(dll_Node));
    dll_Init(head);

    // Checking if malloc was able to allocate memory
    checks_nullpointer(head);

    // Inserting some string blobs
    dll_Insert(head, "Abra");
    dll_Insert(head, "Kadabra");
    dll_Insert(head, "Alakazam");
    dll_Insert(head, "Mega Alakazam");;

    // Printing one blob per line
    dll_Print(head);

    // Removing the last node
    dll_Remove(head);

    // Checking if it was really removed
    dll_Print(head);

    // Spliting the string of a blob in a given index
    dll_SplitIndex(head, 1);

    // Checking if it really worked
    dll_Print(head);

    // Merging two consecutive string blobs
    dll_JoinNext(head);

    // Checking if it really worked
    dll_Print(head);

    // Inserting many string blobs
    for (int i = 0; i < 20; ++i)
        dll_Insert(head, "Alakazam");

    // Prints one terminal line of string blobs
    dll_PrintOneLine(head);

    // Freeing allocated memory
    dll_Free(head);

    // Time taken
    printf("Time taken: %.8fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}