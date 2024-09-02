#include <stdlib.h>
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4};
    int* harr = calloc(4, sizeof(int));

    int s1 = sizeof(arr);
    int s2 = sizeof(harr);

    printf("Size of stack arr is %d, heap arr is %d", s1, s2);
    // Sizeof can get the actual size of data like arr on stack, but not ones on the heap
    return 0;
}