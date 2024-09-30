#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to add a new edge to the graph
void add_edge(Graph* self, int from, int to, int w) {
    Edge newEdge = { to, w };
    insert_at_front(&self->edges[from], newEdge);
}

// Function to insert at the front of an edge list
void insert_at_front(EdgeList* list, Edge edge) {
    EdgeNodePtr newNode = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    newNode->edge = edge;
    newNode->next = list->head;
    list->head = newNode;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read the number of vertices
    Graph G;
    fscanf(file, "%d", &G.V);

    // Allocate memory for edges array
    G.edges = (EdgeList*)malloc(G.V * sizeof(EdgeList));

    // Initialize each edge list
    for (int v = 0; v < G.V; v++) {
        G.edges[v].head = NULL;
    }

    // Read and add each edge from the file
    int from, to, weight;
    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        add_edge(&G, from, to, weight);
    }

    fclose(file);

    // Calculate in-degrees
    int* in_degrees = (int*)calloc(G.V, sizeof(int));
    for (int v = 0; v < G.V; v++) {
        EdgeNodePtr current = G.edges[v].head;
        while (current != NULL) {
            in_degrees[current->edge.to_vertex]++;
            current = current->next;
        }
    }

    // Print in-degrees
    for (int v = 0; v < G.V; v++) {
        printf("Vertex %d: In-degree %d\n", v, in_degrees[v]);
    }

    // Free allocated memory
    free(in_degrees);
    for (int v = 0; v < G.V; v++) {
        EdgeNodePtr current = G.edges[v].head;
        while (current != NULL) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(G.edges);

    return 0;
}