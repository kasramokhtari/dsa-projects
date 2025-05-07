/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{2} 
* FindPath.c
* Main file program
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){

    FILE *in, *out;

    if( argc != 3 ){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if( in==NULL ){
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }

    char buffer[1024];

    int order;

    fgets(buffer, sizeof(buffer), in);

    sscanf(buffer, "%d", &order);

    Graph G = newGraph(order);

    int u;
    int v;

    while(fgets(buffer, sizeof(buffer), in)){
        sscanf(buffer, "%d %d", &u, &v);
        if(u == 0 && v == 0){
            break;
        }
        addEdge(G, u, v);
    }

    printGraph(out, G);
    fprintf(out, "\n");

    int s;
    int d;

    bool first = true;

    while(fgets(buffer, sizeof(buffer), in)){
        sscanf(buffer, "%d %d", &s, &d);
        if(s == 0 && d == 0){
            break;
        }

        if(!first){
            fprintf(out, "\n\n");
        }
        first = false;

        BFS(G, s);

        if(getDist(G, d) == INF){
            fprintf(out, "The distance from %d to %d is infinity\n", s, d);
            fprintf(out, "No %d-%d path exists", s, d);
            continue;
        }
        fprintf(out, "The distance from %d to %d is %d\n", s, d, getDist(G, d));

        List path = newList();
        getPath(path, G, d);
        fprintf(out, "A shortest %d-%d path is: ", s, d);
        printList(out, path);
        freeList(&path);
    }
    freeGraph(&G);


    fclose(in);
    fclose(out);
    return(0);
}