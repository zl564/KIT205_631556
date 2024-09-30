#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Function to add an edge to the graph
void add_edge(Graph* self, int from, int to, int w) {
    EdgeNodePtr new_node = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    new_node->edge.to_vertex = to;
    new_node->edge.weight = w;
    new_node->next = self->edges[from].head;
    self->edges[from].head = new_node;
}

int main() {
    Graph G;
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(file, "%d", &G.V);
    G.edges = (EdgeList*)malloc(G.V * sizeof(EdgeList));
    for (int v = 0; v < G.V; v++) {
        G.edges[v].head = NULL;
    }

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