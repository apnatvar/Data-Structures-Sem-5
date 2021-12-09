#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

int visited[26];
int nextQ[26];

Graph* create_graph(int num_nodes){
num_nodes--;
Graph* newNode;
Graph* toReturn;
toReturn = (Graph*)malloc(sizeof(Graph));
toReturn->vertice = num_nodes;
toReturn->connectedV = NULL;
toReturn->nextV = NULL;
while(num_nodes){
	num_nodes--;
	newNode = (Graph*)malloc(sizeof(Graph));
	newNode->vertice = num_nodes;
	newNode->connectedV = NULL;
	newNode->nextV = toReturn;
	toReturn = newNode;
}
return toReturn;
}

Graph* getNode(Graph *sample, int v){
	Graph *temp = sample;
	while (temp != NULL){
		if (temp->vertice == v)return temp;
		temp = temp->nextV;
	}
	return NULL;
}

void add_edge(Graph *g, int from, int to){
	Graph* newNode = (Graph*)malloc(sizeof(Graph));
	newNode->vertice = to;
	newNode->nextV = NULL;
	Graph* temp = getNode(g, from);
	if (temp->connectedV == NULL){
		temp->connectedV = newNode;
		newNode->connectedV = NULL;
	}
	else{
		newNode->connectedV = temp->connectedV;
		temp->connectedV = newNode;
	}
}

void reset(){
	int i = 0;
	for (; i<26; i++){
		visited[i] = 0;
		nextQ[i] = 0;
	}
}

void printbfs(Graph* g, int o){
	static int start = 0;
	static int end = 0;
	Graph *temp = getNode(g,o);
	while(temp != NULL){
		if (!visited[temp->vertice]){
			printf(" %c ",temp->vertice+'A');
			visited[temp->vertice] = 1;
			nextQ[end] = temp->vertice;
			end++;
		}
		temp = temp->connectedV;
	}
	start++;
	int k = nextQ[start];
	if (start != end)printbfs(g, k);
}


void bfs(Graph* g, int origin){
	reset();
	printf("BFS ");
	printbfs(g, origin);
	printf("\n");
}

void printdfs(Graph* g, int o){
	Graph *temp = getNode(g, o);
	printf(" %c ",o+'A');
	visited[o] = 1;
	while(temp!=NULL){
		if (!visited[temp->vertice]){
			printdfs(g, temp->vertice);
		}
		temp = temp->connectedV;
	}
}

void dfs(Graph* g, int origin){
	reset();
	printf("DFS:");
	printdfs(g, origin);
	printf("\n");
}

void delete_graph(Graph* g){
	Graph *temp;
	Graph *tempG;
	Graph *toDelete;
	while(g != NULL){
		tempG = g;
		temp = g->connectedV;
		g = g->nextV;
		while(temp != NULL){
			toDelete = temp;
			temp = temp->connectedV;
			free(toDelete);
		}
		free(tempG);
	}
}