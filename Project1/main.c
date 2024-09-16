#include <stdio.h>
#include <stdlib.h>

// Define the structure for a graph
typedef struct {
    int numVertices;
    int** adjMatrix;
} Graph;

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adjMatrix[src][dest] = weight;
}

int main() {
    // Declare a variable called G that is a Graph
    Graph* G = createGraph(7);

    // Add edges to the graph
    addEdge(G, 0, 6, 1);
    addEdge(G, 0, 3, 1);
    addEdge(G, 1, 4, 4);
    addEdge(G, 2, 4, 2);
    addEdge(G, 2, 3, 1);
    addEdge(G, 2, 0, 3);
    addEdge(G, 4, 3, 2);
    addEdge(G, 5, 6, 2);
    addEdge(G, 5, 3, 4);
    addEdge(G, 5, 2, 1);
    addEdge(G, 5, 0, 3);
    addEdge(G, 6, 5, 2);
    addEdge(G, 6, 4, 1);
    addEdge(G, 6, 3, 4);

    // Print the adjacency matrix
    for (int i = 0; i < G->numVertices; i++) {
        for (int j = 0; j < G->numVertices; j++) {
            printf("%d ", G->adjMatrix[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < G->numVertices; i++) {
        free(G->adjMatrix[i]);
    }
    free(G->adjMatrix);
    free(G);

    return 0;
}
