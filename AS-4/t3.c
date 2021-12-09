#include "t3.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_DISTANCE 99999999
#define MAX_VERTICES 8000
#define MAX_BUFFER 20
int graph[MAX_VERTICES][MAX_VERTICES];
int numV;
vertice arr[MAX_VERTICES];

int next( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

void verticeUtility(  FILE *csv, vertice *p){
	char buf[MAX_BUFFER];
	next( csv, buf, MAX_BUFFER);
	p->id = atoi(buf);
	next( csv, p->name, MAX_BUFFER );
	next( csv, buf, MAX_BUFFER );
	p->longitude = atof(buf); 
	next( csv, buf, MAX_BUFFER );
	p->latitude = atof(buf);                 
}

int load_vertices( char *fname ){
	FILE *f = fopen(fname,"r");
	int count = 0;
	int rCount = 0;
	int temp;
	verticeUtility(f, &arr[count]);
	while (!feof(f)){
		count++;
		rCount++;
		verticeUtility(f, &arr[count]);
		temp = arr[count].id;
		if (count != temp){
			arr[temp] = arr[count];
			arr[count] = arr[0];
			count = temp;
		}
	}
	fclose(f);
	numV = count+1;
	printf("Loaded %d vertices\n",rCount);
	return rCount;
}

void add_edge(int from, int to, int weight){
	graph[from][to] = weight;
	graph[to][from] = weight;
}
void edgeUtility(FILE *csv, int c){
	if (c){
	char buf[MAX_BUFFER];
	next( csv, buf, MAX_BUFFER );
	int f = atoi(buf);
	next( csv, buf, MAX_BUFFER );
	int t = atoi(buf);
	next( csv, buf, MAX_BUFFER );
	int w = atoi(buf);
	
	add_edge(f,t,w);
	}
}
int load_edges( char *fname ){
	FILE *f = fopen(fname,"r");
	edgeUtility(f, 0);
	int count = -1;
	while (!feof(f)){
		edgeUtility(f,1);
		count++;
	}
	fclose(f);
	printf("Loaded %d edges\n",count);
	return count;
}

int minDistance(int dist[], int sptSet[]){
    int min = MAX_DISTANCE, min_index;
	int v;
    for (v = 0; v < numV; v++){
        if (sptSet[v] == 0 && dist[v] < min){
            min = dist[v];
				min_index = v;
				}
			}
    return min_index;
}

void printPath(int parent[], int u){
    // Base Case : If j is source
    if (parent[u] == - 1)
        return;
    printPath(parent, parent[u]);
    printf("%d %s\n", arr[u].id, arr[u].name);
}

void shortest_path(int startNode, int endNode){
	/*int kj = 0;
	for(;kj < numV ; kj++){
	printf("%d - %4d %20s %f %f\n", kj, arr[kj].id, arr[kj].name, arr[kj].longitude, arr[kj].latitude);}*/
	int dist[numV];
   int sptSet[numV];
	int parent[numV];
	parent[0] = -1;
	int i;
    for (i = 0; i < numV; i++){
        dist[i] = MAX_DISTANCE;//random large integer
sptSet[i] = 0;
}
    dist[startNode] = 0;
	int count;
	int v;
	int u;
    for (count = 0; count < numV; count++) {
        u = minDistance(dist, sptSet);
        sptSet[u] = 1;
			//printf("%4d %20s %f %f\n", arr[u].id, arr[u].name, arr[u].longitude, arr[u].latitude);
			//if (u == endNode)return ;
        for (v = 0; v < numV ; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != MAX_DISTANCE && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
						parent[v] = u;
						}
    }
		printPath(parent, endNode);
   //printSolution(dist, parent, startNode, end);
}//adapted from geeksforgeeks

void free_memory ( void ){
	//printf("");
}