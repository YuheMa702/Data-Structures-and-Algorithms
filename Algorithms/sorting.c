/*
bubble sort vs merge sort vs quicksort
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define ARRAY_SIZE 100000
#define TEST_NUMS 10
/*

With ARRAY_SIZE = 10000, TEST_NUMS = 100
Bub_sort time: 9585
Merge_sort time: 518
Quick_sort time: 55

With ARRAY_SIZE = 10000, TEST_NUMS = 10
Bub_sort time: 943    O(n^2)
Merge_sort time: 52   O(nlogn)
Quick_sort time: 6    O(nlogn)

With ARRAY_SIZE = 100000, TEST_NUMS = 10
Bub_sort time: 167759
Merge_sort time: 3408
Quick_sort time: 66
*/




void print_arr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// O(n^2) Compare pairs of numbers and large value bubbles from left to right
void bub_sort(int* arr, int n) {
    int i, j, left, right;

    for (int i = 0; i < n - 1; i++) {
        // last ith item is already sorted
        for (j = 0; j < n - 1 - i; j++) {
            // Swap if left elem greater than right elem
            left = arr[j];
            right = arr[j+1];
            if (left > right) {
                arr[j] = right;
                arr[j+1] = left;
            }
        }
    }
}

/*********** Merge Sort ***********/
void merge(int* arr, int lo, int mid, int hi, int len) {
    int i = 0, j = 0;
    int idx;
    int n1 = mid - lo;
    int n2 = hi - mid;
    int* temp = calloc(len, sizeof(int));

    // Compare left and right segments and insert into temp
    while(i < n1 && j < n2) {
        int left = arr[lo + i];
        int right = arr[mid + j];
        idx = lo + i + j;
        if (right < left) {
            temp[idx] = right;
            j++;
        } else {
            temp[idx] = left;
            i++;
        }
    }

    // Insert the remaining elems into temp
    while (i < n1) {
        idx = lo + i + j;
        temp[idx] = arr[lo + i];
        i++;
    }
    while (j < n2) {
        idx = lo + i + j;
        temp[idx] = arr[mid + j];
        j++;
    }

    // Copy sorted section back into arr
    for (int k = lo; k < hi; k++) {
        arr[k] = temp[k];
    }
    free(temp); // clean up
}


void merge_sort(int* arr, int lo, int hi, int len) {
    if (hi - lo <= 1) return; // Already sorted
    int mid = lo + (hi - lo) / 2;
    
    merge_sort(arr, lo, mid, len);
    merge_sort(arr, mid, hi, len);
    merge(arr, lo, mid, hi, len);
}



/*********** QuickSort ***********/
/*
Pick a pivot, move smaller number to the left and larger to the right
O(log(n)) amortized, assume pivot is the median, O(n^2) if unlucky
*/
// O(hi-lo), in place
int partition(int* arr, int lo, int hi) {

    int p = lo + (hi - lo) / 2;
    int pvt = arr[p];
    int i = lo;
    int j = hi - 1;
    while(i < j) {
        int left = arr[i];
        int right = arr[j];
        if (right < pvt) {
            // Update pvt's position
            if (i == p) p = j;
            else if (j == p) p = i;
            // Swap: move smaller to the left
            // Left ith elem fixed
            arr[j] = left;
            arr[i] = right;
            i++;
        } else {
            // Right jth elem
            j--;
        }
    }
    return p;
}
void quick_sort(int* arr, int lo, int hi) {
    if (hi - lo <= 1) return; // Already sorted

    int p = partition(arr, lo, hi);
    quick_sort(arr, lo, p);
    quick_sort(arr, p, hi);
}

void arr_copy(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        arr2[i] = arr1[i];
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    int* arr = malloc(sizeof(int)*ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand();
    }

    int* cp = malloc(sizeof(int)*ARRAY_SIZE);
    clock_t start, end;
    clock_t sum = 0;
    for(int i = 0; i < TEST_NUMS; i++) {
        arr_copy(arr, cp, ARRAY_SIZE);
        start = clock();
        bub_sort(cp, ARRAY_SIZE);
        end = clock();
        sum += (end - start);
    }
    printf("Bub_sort time: %d\n", sum);

    sum = 0;
    for(int i = 0; i < TEST_NUMS; i++) {
        arr_copy(arr, cp, ARRAY_SIZE);
        start = clock();
        merge_sort(cp, 0, ARRAY_SIZE, ARRAY_SIZE);
        end = clock();
        sum += (end - start);
    }
    printf("Merge_sort time: %d\n", sum);

    sum = 0;
    for(int i = 0; i < TEST_NUMS; i++) {
        arr_copy(arr, cp, ARRAY_SIZE);
        start = clock();
        quick_sort(cp, 0, ARRAY_SIZE);
        end = clock();
        sum += (end - start);
    }
    printf("Quick_sort time: %d\n", sum);
    free(arr);
    free(cp);
    return 0;
}


