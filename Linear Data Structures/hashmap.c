#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Hashmap implemnented with linked list + separated chaining
// Structure of a complex library: client interface -> implementation -> library interface

/************ CLIENT INTERFACE ***********/
/* client needs to define the following
typedef ______ entry;
typedef ______ key;

key entry_key(entry e)           // get key from entry
int key_hash(key k);             // hashfunction for key
bool key_equiv(key k1, key k2);  // check if two keys are equal
*/

struct student_info {
    int id;
    float gpa;
};

typedef struct student_info* entry;
typedef int key;

// Linear Congruential Generators: a * x + c mod d (a ≠ 0, and c and d relatively prime, d = 2^32)
int lgc(int x) {
    return 1664525 * x + 1013904223;
}

key entry_key(entry e) {
    // Requires e != NULL
    return e->id;
}

int key_hash(key k) {
    return lgc(k);
}

bool key_equiv(key k1, key k2) {
    return k1 == k2;
}

void free_entry(entry e) {
    free(e);
}
/************ CLIENT INTERFACE ***********/



/************* IMPLEMENTATION ************/
// Implementation-side types
typedef struct chain_node chain;
struct chain_node {
    entry data;
    chain* next;
};

struct hdict_header {
    int size; // size >= 0
    int capacity; // capacity > 0
    chain** table; // len(*table) == capapcity
};
typedef struct hdict_header hdict;

// Representation Invariant
bool is_hdict(hdict* H); // Details are skipped

// Implementation of library interface functions
int index_of_key(hdict* H, key k) {
    // Requires is_hdict(H)
    // Ensures 0 <= \result < H->capacity
    return (abs(key_hash(k)) % H->capacity);
}

entry hdict_lookup(hdict* H, key k) {
    // Requires is_hdict(H)
    // Ensures \result == NULL || key_equiv((entry_key(\result), k))

    int i = index_of_key(H, k);

    for (chain* temp = H->table[i]; temp != NULL; temp = temp->next) {
        if (key_equiv(entry_key(temp->data), k)) {
            return temp->data;
        }
    } 
    return NULL;
}

void hdict_insert(hdict* H, entry e) {
    // Requires is_hdict(H)
    // Ensures hdict_lookup(H, entry_key(e)) == e
    // Ensures is_hdict(H)

    key k = entry_key(e);
    int i = index_of_key(H, k);

    for (chain* temp = H->table[i]; temp != NULL; temp = temp->next) {
        if (key_equiv(entry_key(temp->data), k)) {
            entry old_entry = temp->data;
            temp->data = e;
            free_entry(old_entry);
            return;
        }
    }

    // Insert at front of chain
    chain* new = malloc(sizeof(chain));
    new->data = e;
    new->next = H->table[i];
    H->table[i] = new;
    (H->size)++;
}

hdict* hdict_new(int capacity)
// Requires capacity > 0;
// Ensures is_hdict(\result);
{
    hdict* H = malloc(sizeof(hdict));
    H->size = 0;
    H->capacity = capacity;
    H->table = calloc(capacity, sizeof(chain*));
    return H;
}

// Client type
typedef hdict* hdict_t;
/************* IMPLEMENTATION ************/


/*********** LIBRARY INTERFACE ***********/
// typedef ______ *hdict_t;

hdict_t hdict_new(int capacity);
/*@requires capacity > 0; @*/
/*@ensures \result != NULL; @*/ 
entry hdict_lookup(hdict_t D, key k);
/*@requires D != NULL; @*/
/*@ensures \result == NULL
|| key_equiv(entry_key(\result), k); @*/ 
void hdict_insert(hdict_t D, entry e);
/*@requires D != NULL && e != NULL; @*/
/*@ensures hdict_lookup(D, entry_key(e)) == e; @*/ 

/*********** LIBRARY INTERFACE ***********/
