#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
Unbounaded Array:
Keep tracks of size, limit, and data arr
When size reaches limit, double the size of data arr
Insertion and deletion has amortized cost of O(1)
Amortization: most cheap operations pay for rare and rarer expensive ones
*/

typedef struct uba_header uba;

struct uba_header {
    int size;   // 0 <= size < limit
    int limit;  // 0 < limit
    int* data;  // len(data) == limit
};


bool is_uba(uba* A) {
    return A->size >= 0 && A->size < A->limit 
    && A->limit > 0 && (sizeof(A->data) / sizeof(*(A->data))) == A->limit;
}

int uba_len(uba* A) {
    return A->size;
}

void uba_set(uba* A, int i, int n) {
    A->data[i] = n;
}

int uba_get(uba* A, int i) {
    return A->data[i];
}

uba* uba_new(int size) {
    uba* new = malloc(sizeof(uba));
    new->limit = size == 0 ? 1 : size * 2;
    new->size = size;
    new->data = malloc(sizeof(int)*new->limit);
    return new;
}

void uba_resize(uba* A, int new_limit) {
    int* new_data = malloc(sizeof(int)*new_limit);
    for (int i = 0; i < A->size; i++) {
        new_data[i] = A->data[i];
    }
    A->limit = new_limit;
    free(A->data); // clean up old array memory
    A->data = new_data;
}

void uba_add(uba* A, int n) {
    A->data[A->size] = n;
    (A->size)++;
    if (A->size < A->limit) return;
    uba_resize(A, A->size * 2);
}

void uba_rem(uba* A) {
    // Requires A non-empty
    if (A->size <= 0) return;
    (A->size)--;
    if (A->size < A->limit / 2) uba_resize(A, A->limit / 2);
}

void uba_print(uba* A) {
    printf("uba[%d]: ", A->limit);
    for (int i = 0; i < A->size; i++) {
        printf("%d ", A->data[i]);
    }
    for (int i = 0; i < A->limit - A->size; i++) {
        printf("X ");
    }
    printf("\n");
}


// Parse array in a function
void printMatrix(int m[3][3]) {
    for (int i = 0; i < 3; i++) {
        printf("[");
        for (int j = 0; j < 3; j++) {
            if (j == 2) {
                printf("%d", m[i][j]);
            } else {
                printf("%d, ", m[i][j]);
            }
        }
        printf("]\n");
    }
}

int main() {
    // Declare arrays on the stack
    int nums[] = {72, 9, -12, 520, 0};
    int fourNums[4]; // Declare an int array of size 4

    // Set values for an array via a loop
    for (int i = 0; i < 4; i++) {
        fourNums[i] = i;
        printf("%d\n", fourNums[i]);
    }

    // 2D array
    int matrix[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    printf("Matrix[1][2] is %d\n", matrix[1][2]); // 6
    printMatrix(matrix);

    // unbounded array
    uba* A = uba_new(0);
    uba_print(A);
    uba_add(A, 0);
    printf("Added 0 to A\n");
    uba_print(A);
    uba_add(A, 1);
    uba_add(A, 2);
    uba_add(A, 3);
    printf("Added 1, 2, 3 to A\n");
    uba_print(A);
    printf("The 2nd elem of uba A is %d\n", uba_get(A, 2));
    uba_set(A, 2, 702);
    printf("After uba_set(A, 2, 702) the 2nd elem is %d\n", uba_get(A, 2));
    uba_rem(A);
    printf("Called uba_rem(A)\n");
    uba_print(A);
    uba_rem(A);
    uba_rem(A);
    printf("Called uba_rem(A) twice\n");
    uba_print(A);
    uba_rem(A);
    printf("Called uba_rem(A)\n");
    uba_print(A);     
}
