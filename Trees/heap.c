#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 // Define the maximum size of the heap

// A structure to represent a Min-Heap
struct MinHeap {
    int *arr;
    int size;
    int capacity;
};

// Function to create a new Min-Heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->arr = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// Function to get the index of the parent node
int parent(int i) {
    return (i - 1) / 2;
}

// Function to get the index of the left child node
int leftChild(int i) {
    return 2 * i + 1;
}

// Function to get the index of the right child node
int rightChild(int i) {
    return 2 * i + 2;
}

// Function to swap two elements
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to heapify the tree at index `i` (recursive)
void heapifyDown(struct MinHeap* minHeap, int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int smallest = i;

    // Check if the left child exists and is smaller than the current node
    if (left < minHeap->size && minHeap->arr[left] < minHeap->arr[smallest])
        smallest = left;

    // Check if the right child exists and is smaller than the current smallest node
    if (right < minHeap->size && minHeap->arr[right] < minHeap->arr[smallest])
        smallest = right;

    // If the smallest is not the root
    if (smallest != i) {
        swap(&minHeap->arr[i], &minHeap->arr[smallest]);
        heapifyDown(minHeap, smallest); // Recursively heapify the affected sub-tree
    }
}

// Function to insert a new key into the Min-Heap
void insertMinHeap(struct MinHeap* minHeap, int key) {
    if (minHeap->size == minHeap->capacity) {
        printf("Overflow: Could not insert key\n");
        return;
    }

    // First insert the new key at the end
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->arr[i] = key;

    // Fix the min-heap property if it is violated
    while (i != 0 && minHeap->arr[parent(i)] > minHeap->arr[i]) {
        swap(&minHeap->arr[i], &minHeap->arr[parent(i)]);
        i = parent(i);
    }
}

// Function to extract the minimum (root) element from the Min-Heap
int extractMin(struct MinHeap* minHeap) {
    if (minHeap->size <= 0)
        return -1; // Heap is empty
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->arr[0];
    }

    // Store the minimum value and remove it from heap
    int root = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    minHeap->size--;
    heapifyDown(minHeap, 0);

    return root;
}

// Function to print the Min-Heap elements
void printMinHeap(struct MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; ++i)
        printf("%d ", minHeap->arr[i]);
    printf("\n");
}

int main() {
    struct MinHeap* minHeap = createMinHeap(MAX_SIZE);

    insertMinHeap(minHeap, 3);
    insertMinHeap(minHeap, 2);
    insertMinHeap(minHeap, 15);
    insertMinHeap(minHeap, 5);
    insertMinHeap(minHeap, 4);
    insertMinHeap(minHeap, 45);

    printf("Min-Heap array: ");
    printMinHeap(minHeap);

    printf("Extracted min: %d\n", extractMin(minHeap));
    printf("Min-Heap after extraction: ");
    printMinHeap(minHeap);

    return 0;
}
