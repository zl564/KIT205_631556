#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void add_edge(Graph* self, int from, int to, int weight);
void init_graph(Graph* G, int V);

int main() {
    Graph G;
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return -1;  // Return with error code
    }

    // Read the number of vertices
    fscanf(file, "%d", &G.V);
    G.edges = malloc(sizeof(EdgeList) * G.V);
    if (G.edges == NULL) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return -1;  // Return with error code
    }

    // Initialize the graph
    init_graph(&G, G.V);

    // Read the edges from file and add to the graph
    int from, to, weight;
    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        add_edge(&G, from, to, weight);
    }

    fclose(file);  // Close the file

    // Your code to interact with the graph would go here

    // Free memory
    for (int i = 0; i < G.V; i++) {
        EdgeNodePtr current = G.edges[i].head;
        while (current != NULL) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(G.edges);

    return 0;  // Successful execution
}

void add_edge(Graph* self, int from, int to, int weight) {
    EdgeNodePtr newNode = malloc(sizeof(struct edgeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->edge.to_vertex = to;
    newNode->edge.weight = weight;
    newNode->next = self->edges[from].head;
    self->edges[from].head = newNode;
}

void init_graph(Graph* G, int V) {
    for (int i = 0; i < V; i++) {
        G->edges[i].head = NULL;
    }
}