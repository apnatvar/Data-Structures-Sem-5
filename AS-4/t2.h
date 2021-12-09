#ifndef T2_H_
#define T2_H_

#define MAX_VERTICES 10 // you can assume that the graph has at most 10 vertex
typedef struct Graph{
	int vertice;
	struct Graph *next;
} Graph;

Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to, int weight); // adds a weighted edge

void dijkstra(Graph* g, int origin);
void delete_graph(Graph* g);

#endif