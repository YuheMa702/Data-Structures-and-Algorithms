/*
Binary search tree dictionary
Each node has at most 2 children
Each node's left child <= node <= right child
Node with zero child is a leaf
Guaranteed O(logn) for lookup, insert, and find_min
Terms: root, subtree, inner node, leaf, left child, right child, parent
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


/*********** CLIENT INTERFACE ************/

typedef struct student_info* entry;
typedef int key;

struct student_info {
    int id;
    float gpa;
};

key entry_key(entry e) {
    return e->id;
}

// res < 0: k1 < k2, res == 0: k1 == k2, res > 0: k1 > k2
int key_compare(key k1, key k2) {
    return (k1 - k2);
}

void entry_free(entry e) {
    free(e);
}

/*********** CLIENT INTERFACE ************/



/************ IMPLEMENTATION *************/
// BST and auxiliary functions
typedef struct tree_node tree;
struct tree_node {
    entry data;
    tree* left;
    tree* right;
};


entry bst_lookup(tree* T, key k) 
/*
Requires is_bst(T)
Ensures \result == NULL || key_compare(entry_key(\result), k) == 0
*/
{
    // code for empty tree
    if (T == NULL) return NULL;

    // code for non-empty tree
    int cmp = key_compare(k, entry_key(T->data));
    if (cmp < 0) return bst_lookup(T->left, k);
    else if (cmp == 0) return T->data;
    else return bst_lookup(T->right, k);
}

tree* leaf(entry e) 
/*
Requires e != NULL
Ensures is_bst(\result) && \result != NULL
*/
{
    tree* new = malloc(sizeof(tree));
    new->data = e;
    new->left = NULL;
    new->right = NULL;
    return new;
}

tree* bst_insert(tree* T, entry e) {
    // code for empty tree
    if (T == NULL) return leaf(e);

    // For non-empty tree, update entry if key already exists
    int cmp = key_compare(entry_key(e), entry_key(T->data));
    if (cmp < 0) T->left = bst_insert(T->left, e);
    else if (cmp == 0) {
        entry_free(T->data);
        T->data = e;
    } else T->right = bst_insert(T->right, e);
    return T;
}

entry find_min(tree* T) {
    if (T == NULL) return NULL;
    
    if (T->left == NULL) return T->data;
    return find_min(T->left);
}


// Representation Invariant

// This is a minimal function, cuz we need to check acyclicity
bool is_tree(tree* T) {
    if (T == NULL) return true;
    return T->data != NULL && is_tree(T->left) && is_tree(T->right);
}

// Idea: for each node with subtree(s), the subtree's data must fall within a range (lo, hi)
bool is_ordered(tree* T, entry lo, entry hi) {
    if (T == NULL) return true;

    key k = entry_key(T->data);
    return (lo == NULL || key_compare(entry_key(lo), k) < 0) &&
    (hi == NULL || key_compare(k, entry_key(hi)) < 0) &&
    is_ordered(T->left, lo, T->data) &&
    is_ordered(T->right, T->data, hi);
}

bool is_bst(tree* T) {
    return is_tree(T) && is_ordered(T, NULL, NULL);
}


// Implementing the dictionary
// Concrete type
typedef struct dict_header dict;
struct dict_header {
    tree* root;
};

// Representation Invariant
bool is_dict(dict* D) {
    return D != NULL && is_bst(D->root);
}

entry dict_lookup(dict* D, key k) {
    return bst_lookup(D->root, k);
}

void dict_insert(dict* D, entry e) {
    D->root = bst_insert(D->root, e);
}

entry dict_min(dict* D) {
    return find_min(D->root);
}

dict* dict_new() {
    dict* new = malloc(sizeof(dict));
    new->root = NULL;
    return new;
}


// Client type
typedef dict* dict_t;


/************ LIBRARY INTERFACE *************/
// typedef ______* dict_t;
dict_t dict_new();
/*@ensures \result != NULL; @*/ 
entry dict_lookup(dict_t D, key k);
/*@requires D != NULL; @*/
/*@ensures \result == NULL
|| key_compare(entry_key(\result), k) == 0; @*/ 
void dict_insert(dict_t D, entry e);
/*@requires D != NULL && e != NULL; @*/
/*@ensures hdict_lookup(D, entry_key(e)) == e; @*/ 
entry dict_min(dict_t D);
/*@requires D != NULL; @*/ 
/************ LIBRARY INTERFACE *************/


