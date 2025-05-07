/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{2} 
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
    Graph G = newGraph(6);

    // should print out an empty adjacency list
    printGraph(stdout,G);

    // getSource() test on empty graph
    printf("The source is %d\n", getSource(G)); // prints -1

    // getParent() test on empty graph
    printf("The parent of 4 is %d\n", getParent(G,4)); // prints -1

    // getDist() test on empty graph
    printf("The distance from 1 to 3 is %d\n", getDist(G, 3)); // prints -2

    // // getPath() test on empty graph
    // List L = newList();
    // getPath(L,G,5);
    // printList(stdout, L); // prints error (It does)
    // printf("\n");

    // addEdge() and addArc() (since addEdge() uses addArc())
    addEdge(G,1,2);
    addEdge(G,1,3);
    addEdge(G,1,4);
    addEdge(G,1,6);
    addEdge(G,4,5);
    addEdge(G,5,6);
    addEdge(G,2,6);
    addEdge(G,3,4);
    addEdge(G,5,5);

    // 1: 2 3 4 6
    // 2: 1 6
    // 3: 1 4
    // 4: 1 3 5
    // 5: 4 5 6
    // 6: 1 2 5

    printGraph(stdout, G);

    // BFS() test
    BFS(G, 1);

    // getOrder() test
    printf("The order is %d\n", getOrder(G)); // prints 6

    // getSize() test
    printf("The size is %d\n", getSize(G)); // prints 9 (9 directed edges including 1 self-loop)

    // getSource() test
    printf("The source is %d\n", getSource(G)); // prints 1

    // getParent() test
    printf("The parent of 5 is %d\n", getParent(G, 5)); // prints 4

    // getDist() test
    printf("The distance from 1 to 5 is %d\n", getDist(G, 5)); // prints 2

    // getPath() test
    List L = newList();
    getPath(L,G,5);
    printList(stdout, L); // prints 1 4 5
    printf("\n");

    makeNull(G);

    printGraph(stdout,G);


    // getOrder() test after makeNULL()
    printf("The order is %d\n", getOrder(G)); // prints 6

    // getSize() test after makeNULL()
    printf("The size is %d\n", getSize(G)); // prints 0 

    // getSource() test after makeNULL()
    printf("The source is %d\n", getSource(G)); // prints -1

    // getParent() test after makeNULL()
    printf("The parent of 5 is %d\n", getParent(G, 5)); // prints -1

    // getDist() test after makeNULL()
    printf("The distance from 1 to 5 is %d\n", getDist(G, 5)); // prints -2

    freeList(&L);
    freeGraph(&G);

    return(0);
}
