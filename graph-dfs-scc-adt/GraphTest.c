/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{3} 
* GraphTest.c
* Test cases for Graph ADT
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"


int main(int argc, char* argv[]){

    // newGraph() tests
    Graph G = newGraph(12);

    // should print out an empty adjacency list
    printGraph(stdout,G);

    // getParent() test on empty graph
    printf("The parent of 4 is %d\n", getParent(G,4)); // prints -1

    // getOrder() test on empty graph
    printf("The order of G is %d\n", getOrder(G)); // prints 12

    // addArc() tests
    addArc(G,1,2);
    addArc(G,2,3);
    addArc(G,2,5);
    addArc(G,3,4);
    addArc(G,3,7);
    addArc(G,4,8);
    addArc(G,5,1);
    addArc(G,5,6);
    addArc(G,5,9);
    addArc(G,6,2);
    addArc(G,6,7);
    addArc(G,6,10);
    addArc(G,7,10);
    addArc(G,7,11);
    addArc(G,8,3);
    addArc(G,8,7);
    addArc(G,8,12);
    addArc(G,10,9);
    addArc(G,10,11);
    addArc(G,11,12);
    addArc(G,12,7);


    // getSize() test 
    printf("The size of G is %d\n", getSize(G)); // prints 12

    // 1: 2
    // 2: 3 5
    // 3: 4 7
    // 4: 8
    // 5: 1 6 9
    // 6: 2 7 10
    // 7: 10 11
    // 8: 3 7 12
    // 9: 
    // 10: 9 11
    // 11: 12
    // 12: 7
    printGraph(stdout, G);

    List S = newList();
    for(int i = 1; i <= getOrder(G); i++){
    append(S, i);
  }

    // DFS() and transpose test
    DFS(G, S);

    // make sure the stack is updating correctly
    printList(stdout, S); // prints 1 2 5 6 3 4 8 7 10 11 12 9
    printf("\n");

    // getDiscover() test 
    printf("The discover time of 1 is %d\n", getDiscover(G, 1)); // prints 1

    // getDiscover() test 
    printf("The discover time of 12 is %d\n", getDiscover(G, 12)); // prints 11

    // getFinish() test 
    printf("The finish time of 1 is %d\n", getFinish(G, 1)); // prints 24

    // getFinish() test 
    printf("The finish time of 4 is %d\n", getFinish(G, 4)); // prints 17

    // getFinish() test 
    printf("The finish time of 9 is %d\n", getFinish(G,9)); // prints 9

    // getFinish() test 
    printf("The finish time of 12 is %d\n", getFinish(G,12)); // prints 12

    // getFinish() test 
    printf("The finish time of 11 is %d\n", getFinish(G,11)); // prints 13


    Graph T = transpose(G);
    
    DFS(T, S);

    // make sure the stack is updating correctly
    printList(stdout, S); // prints 9 7 12 11 10 3 8 4 1 5 2 6
    printf("\n");

    // getDiscover() test 
    printf("The discover time of 1 is %d\n", getDiscover(T, 1)); // prints 1

    // getDiscover() test 
    printf("The discover time of 12 is %d\n", getDiscover(T, 12)); // prints 16

    // getFinish() test 
    printf("The finish time of 1 is %d\n", getFinish(T, 1)); // prints 8

    // getFinish() test 
    printf("The finish time of 4 is %d\n", getFinish(T, 4)); // prints 12

    // getFinish() test 
    printf("The finish time of 11 is %d\n", getFinish(T,11)); // prints 20

    // getFinish() test 
    printf("The finish time of 12 is %d\n", getFinish(T,12)); // prints 21

    // getFinish() test 
    printf("The finish time of 9 is %d\n", getFinish(T,9)); // prints 24

    // copyGraph()
    // Output below; should be the same as graph G.
    // 1: 2
    // 2: 3 5
    // 3: 4 7
    // 4: 8
    // 5: 1 6 9
    // 6: 2 7 10
    // 7: 10 11
    // 8: 3 7 12
    // 9: 
    // 10: 9 11
    // 11: 12
    // 12: 7
    Graph C = copyGraph(G);

    printGraph(stdout, C);

    freeList(&S);
    // freeGraph() test
    freeGraph(&C);
    freeGraph(&G);
    freeGraph(&T);

    return(0);
}
