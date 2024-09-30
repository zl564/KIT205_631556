#ifndef graph.h
#define graph.h

typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

typedef struct graph {
    int V;
    EdgeList* edges;
} Graph;

void add_edge(Graph* self, int from, int to, int w);
void insert_at_front(EdgeList* list, Edge edge);

#endif // GRAPH_H