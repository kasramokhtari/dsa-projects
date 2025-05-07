/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{2} 
* Graph.c
* Function defintions for Graph ADT 
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

typedef struct GraphObj{
    List* adjList;
    int* color;
    int* dist; 
    int* pred;
    int order; // num vertices
    int size; // num edges
    int source; // last source
} GraphObj;

/*** Helper Functions ***/
static void graphCheck(Graph G, const char* functionName){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling %s on NULL Graph reference\n", functionName);
        exit(EXIT_FAILURE);
    }
}

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adjList = malloc(sizeof(List)*(n+1));
    G->color = malloc(sizeof(int)*(n+1));
    G->dist = malloc(sizeof(int)*(n+1));
    G->pred = malloc(sizeof(int)*(n+1));

    for(int i = 1; i <= n; i++){
        G->adjList[i] = newList();
    }

    G->order = n;
    G->size = 0;
    G->source = NIL;

    return G;
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 1; i <= getOrder(*pG); i++){
            freeList(&((*pG)->adjList[i]));
        }
        free((*pG)->adjList);
        free((*pG)->color);
        free((*pG)->dist);
        free((*pG)->pred);
        free(*pG);
        *pG = NULL;
    }
}



/*** Access functions ***/
int getOrder(Graph G){
    graphCheck(G, "getOrder()");
    return G->order;
}

int getSize(Graph G){
    graphCheck(G, "getSize()");
    return G->size;
}

int getSource(Graph G){
    return G->source;
}

int getParent(Graph G, int u){
    graphCheck(G, "getParent()");
    if(G->source == NIL){
        return NIL;
    }
    return G->pred[u];
}

int getDist(Graph G, int u){
    graphCheck(G, "getDist()");
    if(G->source == NIL){
        return INF;
    }
    return G->dist[u];
}

void getPath(List L, Graph G, int u){
    graphCheck(G, "getPath()");
    if (getSource(G) == NIL) {
        printf("BFS must be called before calling getPath()\n");
        exit(EXIT_FAILURE);
    }
    if(G->source == u){
        append(L, G->source);
    }
    else if(G->pred[u] == NIL){
        clear(L);
        append(L, NIL);
    }
    else{
        getPath(L, G, G->pred[u]);
        append(L, u);
    }
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
    graphCheck(G, "makeNull()");
    for(int i = 1; i <= getOrder(G); i++){
        clear(G->adjList[i]);
        G->color[i] = 0;
        G->dist[i] = INF;
        G->pred[i] = NIL;
    }

    G->size = 0;
    G->source = NIL;
}

void addEdge(Graph G, int u, int v){
    graphCheck(G, "addEdge()");
    if(u == v){
        addArc(G, u, v);
        return;
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}


void addArc(Graph G, int u, int v){
    graphCheck(G, "addArc()");
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        printf("Vertex values are outside the range of possible vertices.\n");
        exit(EXIT_FAILURE);
    }

    List U = G->adjList[u];

    if(isEmpty(U)){
        append(U, v);
        G->size++;
        return;
    }

    int inserted = 0;
    moveFront(U);

    for(int i = 0; i < length(U); i++){
        if(v < get(U)){
            insertBefore(U, v);
            inserted = 1;
            break;
        }
        moveNext(U);
    }
    if(!inserted){
        moveBack(U);
        insertAfter(U, v);
    }

    G->size++;
}

void BFS(Graph G, int s){
    graphCheck(G, "BFS()");
    if(s < 1 || s > getOrder(G)){
        printf("Source vertex is outside the range of possible vertices.\n");
        exit(EXIT_FAILURE);
    }

    G->source = s;

    List Q = newList();
    for(int i = 1; i <= getOrder(G); i++){
        if(i == s){
            continue;
        }
        G->color[i] = 0;
        G->dist[i] = INF;
        G->pred[i] = NIL;
    }
    G->color[s] = 1;
    G->dist[s] = 0;
    G->pred[s] = NIL;

    append(Q, s);

    while(!isEmpty(Q)){
        int curr = front(Q);
        deleteFront(Q);

        List C = G->adjList[curr];
        moveFront(C);
        
        for(int i = 0; i < length(C); i++){
            int v = get(C);
            if(G->color[v] == 0){
                G->color[v] = 1;
                G->dist[v] = G->dist[curr]+1;
                G->pred[v] = curr;

                append(Q, v);
            }
            moveNext(C);
        }
        G->color[curr] = 2;
    }

    freeList(&Q);
}



/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    graphCheck(G, "printGraph()");
    for(int i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d:", i);

        List C = G->adjList[i];
        moveFront(C);

        while(index(C) != -1){
            fprintf(out, " %d", get(C));
            moveNext(C);
        }

        fprintf(out, "\n");
    }
}