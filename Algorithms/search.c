/*
linear search vs binary search
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define ARRAY_SIZE 1000000
#define MAX_INCR 10
#define RUN_TIME 10000


// O(n)
bool lin_search(int* arr, int target, int length) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == target) return true;
    }
    return false;
}

// O(log(n))
bool bin_search(int* arr, int target, int length) {
    // Requires arr sorted
    int lo = 0;
    int mid = length / 2;
    int hi = length;

    while(lo < hi) {
        if (arr[mid] == target) return true;
        else if (arr[mid] < target) lo = mid + 1;
        else hi = mid;
        mid = lo + (hi - lo) / 2; // Avoid overflow
    }
    return false;
}


int main() {

    int* arr = malloc(sizeof(int)*ARRAY_SIZE);
    srand(time(0)); // Seed the random # generator

    arr[0] = rand() % MAX_INCR; // Set the 1st number

    for (int i = 1; i < ARRAY_SIZE; i++) {
        arr[i] = arr[i-1] + rand() % MAX_INCR;
    }

    int target = arr[ARRAY_SIZE - 1]; // The last elem

    // Run each search function RUN_TIME times
    clock_t lin_t1 = clock();
    for(int i = 0; i < RUN_TIME; i++) {
        assert(lin_search(arr, target, ARRAY_SIZE));
    }
    clock_t lin_t2 = clock();
    clock_t bin_t1 = clock();
    for(int i = 0; i < RUN_TIME; i++) {
        assert(bin_search(arr, target, ARRAY_SIZE));
    }
    clock_t bin_t2 = clock();

    int lin_t = lin_t2 - lin_t1;
    int bin_t = bin_t2 - bin_t1;
    printf("For an arr[%d], lin_search takes %d clk cycles whereas bin_search takes %d clk cycles", 
            ARRAY_SIZE, lin_t, bin_t);
    // For an arr[100000], lin_search takes 813 clk cycles whereas bin_search takes 0 clk cycles
    // For an arr[1000000], lin_search takes 8585 clk cycles whereas bin_search takes 1 clk cycles
    free(arr); // Clean up
    return 0;
}