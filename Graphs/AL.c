/*
Graphs implemented via adjacency linked lists
v = vertex, e = edge
A v-element array of adjacency lists
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef unsigned int vertex;

typedef struct adjlist_node adjlist;
struct adjlist_node {
    vertex vert;
    adjlist *next;
};

typedef struct graph_header graph;
struct graph_header {
    unsigned int size; // size = # of vertex
    adjlist **adj;
};

// Turtle vs Hare
bool is_acyclic(adjlist* L) {
    if (L == NULL) return true;
    adjlist* t = L;
    adjlist* h = t->next;
    while (t != h) {
        if (h == NULL || h->next == NULL) return true; // Hare reaches null faster
        t = t->next;
        h = h->next->next;
    }
    return false;
}

bool is_vertex(graph *G, vertex v) {
    // REQUIRES(G != NULL);
    return v < G->size;
}

bool is_in_adjlist(adjlist* L, vertex v) {
    if (L == NULL) return false;
    for (adjlist* temp = L; temp != NULL; temp = temp->next) {
        if (v == temp->vert) return true;
    }
    return false;
}


bool is_adjlist(graph* G, vertex v, adjlist* L) {
    if (!is_acyclic(L)) return false; // check acyclicity
    // check each vertex
    while(L != NULL) {
        vertex w = L->vert;
        if (!is_vertex(G, w)) return false; // neighbors are legal vertex
        if (w == v) return false; // no self-edge

        if (!is_in_adjlist(G->adj[w], v)) return false; // Edge is double-arrowed
        if (is_in_adjlist(L->next, w)) return false; // No duplicated edge
        L = L->next;
    }
    return true;
}


// Representation Invariant
bool is_graph(graph* G) {
    if (G == NULL) return false;
    // Check len(G->adj) == G->size but cannot do this in C
    for (int v = 0; v < G->size; v++) {
        if (!is_adjlist(G, v, G->adj[v])) return false;
    }
    return true;
}


// Interface

unsigned int graph_size(graph* G) {
    // Requries is_graph(G)
    return G->size;
}

graph* graph_new(unsigned int size) {
    graph* new = malloc(sizeof(graph));
    new->size = size;
    new->adj = calloc(size, sizeof(adjlist*));
    // Ensures is_graph(new)
    return new;
}

void graph_free(graph* G) {
    // Requires is_graph(G)
    // Free each node for each adjlist
    for (int v = 0; v < G->size; v++) {
        adjlist* curr = G->adj[v];
        while(curr != NULL) {
            adjlist* old = curr;
            curr = curr->next;
            free(old);
        }
    }
    free(G->adj); // Free adjlist* matrix
    free(G); // Free the graph
}

// O(min(v, e))
bool graph_hasedge(graph* G, vertex v, vertex w) {
    // Requires is_graph(G)
    for(adjlist* temp = G->adj[v]; temp != NULL; temp = temp->next) {
        if (temp->vert == w) return true;
    }
    return false;
}

void graph_addedge(graph* G, vertex v, vertex w) {
    // Requires is_graph(G)
    // Requires v != w and !graph_hasedge(G, v, w)
    adjlist* L;
    L = malloc(sizeof(adjlist));
    L->vert = v;
    L->next = G->adj[w];
    G->adj[w] = L;

    L = malloc(sizeof(adjlist));
    L->vert = w;
    L->next = G->adj[v];
    G->adj[v] = L;
    // Ensures is_graph(G) && graph_hasedge(G, v, w)
}

typedef struct neighbor_header neighbors;
struct neighbor_header {
    adjlist* next_neighbor;
};

neighbors* graph_get_neighbors(graph* G, vertex v) {
    neighbors* nbors = malloc(sizeof(neighbors));
    nbors->next_neighbor = G->adj[v];
    return nbors;
}

vertex graph_next_neighbor(neighbors* nbors) {
    vertex v = nbors->next_neighbor->vert;
    nbors->next_neighbor = nbors->next_neighbor->next;
    return v;
}

bool graph_hasmore_neighbors(neighbors* nbors) {
    return nbors->next_neighbor != NULL;
}

void graph_free_neighbors(neighbors* nbors) {
    free(nbors); // Do not free individual adjlists
}

typedef struct neighbor_header* neighbors_t;

// O(v*min(v, e))
void graph_print(graph* G) {
    for (vertex v = 0; v < G->size; v++) {
        printf("Vertex %u connected to:");
        neighbors_t nbors = graph_get_neighbors(G, v);
        while(graph_hasmore_neighbors(nbors)) {
            printf(" %u", graph_next_neighbor(nbors));
        }
        graph_free_neighbors(nbors);
        printf("\n");
    }
}
