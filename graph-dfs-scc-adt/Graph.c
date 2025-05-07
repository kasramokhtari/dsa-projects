/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{3} 
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
    int* pred;
    int* discoverTime;
    int* finishTime;
    int order; // num vertices
    int size; // num edges
} GraphObj;

/*** Helper Functions ***/
static void graphCheck(Graph G, const char* functionName){
    if(G == NULL){
        fprintf(stderr, "Graph Error: calling %s on NULL Graph reference\n", functionName);
        exit(EXIT_FAILURE);
    }
}

static void indexCheck(Graph G, int var){
    if(!(var >= 1 && var <= getOrder(G))){
        fprintf(stderr, "Vertex value %d is outside the range of possible vertices\n", var);
        exit(EXIT_FAILURE);
    }
}


/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adjList = malloc(sizeof(List)*(n+1));
    G->color = malloc(sizeof(int)*(n+1));
    G->pred = malloc(sizeof(int)*(n+1));
    G->discoverTime = malloc(sizeof(int)*(n+1));
    G->finishTime = malloc(sizeof(int)*(n+1));

    for(int i = 1; i <= n; i++){
        G->adjList[i] = newList();
    }

    for(int i = 1; i <= n; i++){
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
        G->pred[i] = NIL;
    }

    G->order = n;
    G->size = 0;

    return G;
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 1; i <= getOrder(*pG); i++){
            freeList(&((*pG)->adjList[i]));
        }
        free((*pG)->adjList);
        free((*pG)->color);
        free((*pG)->pred);
        free((*pG)->discoverTime);
        free((*pG)->finishTime);
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


int getParent(Graph G, int u){
    graphCheck(G, "getParent()");
    indexCheck(G, u);
    return G->pred[u];
}

int getDiscover(Graph G, int u){
    graphCheck(G, "getParent()");
    indexCheck(G, u);
    return G->discoverTime[u];
}

int getFinish(Graph G, int u){
    graphCheck(G, "getParent()");
    indexCheck(G, u);
    return G->finishTime[u];
} 



/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v){
    graphCheck(G, "addArc()");
    indexCheck(G, u);
    indexCheck(G, v);

    List U = G->adjList[u];

    if(isEmpty(U)){
        append(U, v);
        G->size++;
        return;
    }

    for(moveFront(U); index(U) != -1; moveNext(U)){
        if(get(U) == v){
            return;
        }
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

void visit(Graph G, int x, int* time, List S){
    G->discoverTime[x] = ++(*time);
    G->color[x] = 1;

    List L = G->adjList[x];

    for(moveFront(L); index(L) != -1; moveNext(L)){
        int curr = get(L);
        if(G->color[curr] == 0){
            G->pred[curr] = x;
            visit(G, curr, time, S);
        }
    }
    G->color[x] = 2;
    G->finishTime[x] = ++(*time);
    prepend(S, x);
}


void DFS(Graph G, List S){
    List temp = copyList(S);
    clear(S);

    for(int i = 1; i <= getOrder(G); i++){
        G->color[i] = 0;
        G->pred[i] = NIL;
    }

    int time = 0;

    for(moveFront(temp); index(temp) != -1; moveNext(temp)){
        int x = get(temp);
        if(G->color[x] == 0){
            visit(G, x, (&time), S);
        }
    }

    freeList(&temp);
}


/*** Other operations ***/
Graph transpose(Graph G){
    Graph N = newGraph(getOrder(G));
    N->size = G->size;

    for(int i = 1; i <= getOrder(G); i++){
        List C = G->adjList[i];
        for(moveFront(C); index(C) != -1; moveNext(C)){
            append(N->adjList[get(C)], i);
        }
    }

    return N;
}


Graph copyGraph(Graph G){
    Graph N = newGraph(getOrder(G));
    N->size = G->size;

    for(int i = 1; i <= getOrder(G); i++){
        List C = G->adjList[i];
        List nC = N->adjList[i];
        for(moveFront(C); index(C) != -1; moveNext(C)){
            append(nC, get(C));
        }
    }

    return N;
}


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