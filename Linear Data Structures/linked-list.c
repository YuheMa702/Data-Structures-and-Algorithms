#include <stdio.h>
#include <stdlib.h>

typedef struct singly_node node1;

// Singly linked list
struct singly_node {
    int data;
    node1* next;
};

typedef struct doubly_node node2;

// Doubly linked list
struct doubly_node {
    int data;
    node2* prev;
    node2* next;
};

// Circular linked list: tail's next points to head