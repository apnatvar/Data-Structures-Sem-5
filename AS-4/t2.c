#include "t2.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_DISTANCE 999999999

int graph[MAX_VERTICES][MAX_VERTICES];
int nodes;

Graph* create_graph(int num_nodes){
	nodes = num_nodes;
	num_nodes--;
	Graph *toReturn = (Graph*)malloc(sizeof(Graph));
	toReturn->vertice = num_nodes;
	toReturn->next = NULL;
	Graph *newNode;
	while(num_nodes){
		newNode =  (Graph*)malloc(sizeof(Graph));
		newNode->vertice = num_nodes;
		newNode->next = toReturn;
		toReturn = newNode;
		num_nodes--;
	}
	return toReturn;
}

void add_edge(Graph *g, int from, int to, int weight){
	graph[from][to] = weight;
	graph[to][from] = weight;
}

int minDistance(int dist[], int sptSet[]){
    int min = MAX_DISTANCE, min_index;
	int v;
    for (v = 0; v < nodes; v++){
        if (sptSet[v] == 0 && dist[v] < min){
            min = dist[v];
				min_index = v;
				}
			}
    return min_index;
}
 
// A utility function to print the constructed distance array
void printSolution(int dist[], int n){
	int i;
    for (i = 0; i < nodes; i++)printf("\nThe length of the shortest path between %c and %c is %d",n + 'A', i + 'A', dist[i]);
}

void dijkstra(Graph* g, int origin){
	//bfs(origin);
	int dist[nodes];
   int sptSet[nodes];
	int i;
    for (i = 0; i < nodes; i++){
        dist[i] = MAX_DISTANCE;//random large integer
		sptSet[i] = 0;
	}
    dist[origin] = 0;
	int count;
	int v;
	int u;
    for (count = 0; count < nodes; count++) {
        u = minDistance(dist, sptSet);
        sptSet[u] = 1;
			printf("%c ", u + 'A');
        for (v = 0; v < nodes ; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != MAX_DISTANCE && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    printSolution(dist, origin);
}//adapted from geeksforgeeks

void delete_graph(Graph* g){
	Graph *temp;
	while (g != NULL){
		temp = g;
		g = g->next;
		free(temp);
	}
}