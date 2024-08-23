#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Stack implemented with null-terminated singly linked-list, pop and push at the top, no dummy node

typedef struct list_node node;

struct list_node {
    int data;
    node* next;
};

typedef struct stack_header stack;

struct stack_header {
    node* top;
};

stack* stack_new() {
    // Ensures res != NULL
    stack* new = malloc(sizeof(stack));
    new->top = NULL;\
    return new;
}

bool is_empty(stack* S) {
    // Requires S != NULL
    return S->top == NULL;
}

void push(stack* S, int n) {
    node* new_top = malloc(sizeof(node));
    new_top->data = n;
    new_top->next = S->top;
    S->top = new_top;
}

// Need to clean popped node
int pop(stack* S) {
    node* temp = S->top;
    int res = temp->data;
    S->top = temp->next;
    free(temp);
    return res;
}

void stack_free(stack* S) {
    node* curr = S->top;
    while(curr != NULL) {
        node* old = curr;
        curr = curr->next;
        free(old); // Free each node
    }
    free(S); // Free the stack
}

