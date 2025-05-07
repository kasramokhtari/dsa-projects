/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{3} 
* FindComponents.c
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
      addArc(G, u, v);
  }

  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");

  List S = newList();
  for(int i = 1; i <= order; i++){
    append(S, i);
  }

  DFS(G, S);

  Graph T = transpose(G);

  DFS(T, S);

  int count = 0;
  for(int i = 1; i <= getOrder(T); i++){
    if(getParent(T, i) == NIL){
      count++;
    }
  }

  fprintf(out, "G contains %d strongly connected components:\n", count);

  int comp = 0;

  List L = newList();
  for(moveBack(S); index(S) != -1; movePrev(S)){
    prepend(L, get(S));

    if(getParent(T, get(S)) == NIL){
      comp++;
      fprintf(out, "Component %d: ", comp);
      printList(out, L);
      if(get(S) != front(S)){
        fprintf(out, "\n");
      }
      clear(L);
    }
  }


  freeList(&S);
  freeList(&L);
  freeGraph(&G);
  freeGraph(&T);

  fclose(in);
  fclose(out);

  return(0);
}