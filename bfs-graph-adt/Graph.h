/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{2} 
* Graph.h
* Function declarations for Graph ADT 
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

#define NIL -1
#define INF -2


typedef struct GraphObj* Graph;



/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);


/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);


/*** Manipulation procedures ***/
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);


/*** Other operations ***/
void printGraph(FILE* out, Graph G);