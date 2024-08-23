#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Implement queue using singly linked list with a dummy node, enq at front, deq at back

typedef struct list_node node;
struct list_node {
    int data;
    node* next;
};

typedef struct queue_header queue;
struct queue_header {
    node* front;
    node* back;
};

queue* queue_new() {
    // Ensures res != NULL
    queue* new = malloc(sizeof(queue));
    new->front = malloc(sizeof(node));  // dummy node
    new->back = new->front;
}

bool is_empty(queue* Q) {
    return Q->front == Q->back;
}

void enq(queue* Q, int n) {
    Q->back->data = n;
    Q->back->next = malloc(sizeof(node)); // create a new dummy node
    Q->back = Q->back->next;
}

int deq(queue* Q) {
    node* temp = Q->front;
    int res = temp->data;
    Q->front = temp->next;
    free(temp);
    return res;
}

void queue_free(queue* Q) {
    node* curr = Q->front;
    while(curr != Q->back) {
        node* old = curr;
        curr = curr->next;
        free(old);
    }
    free(Q->back);
    free(Q);
}
