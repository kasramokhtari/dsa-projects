/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{1} 
* ListText.c
* Test cases for List ADT
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List L = newList();

   assert(length(L) == 0);

   append(L, 10); // List: 10
   prepend(L, 20); // List: 20 10

   moveFront(L); // Cursor -> 20
   insertBefore(L, 30); // List: 30 20 10
   assert(length(L) == 3);

   deleteFront(L); // List: 20 10
   assert(length(L) == 2);

   moveBack(L); // Cursor -> 10
   deleteBack(L); // List: 20
   assert(length(L) == 1);

   
   assert(front(L) == 20);
   assert(back(L) == 20);

   // 20
   printList(stdout,L); 
   printf("\n");

   clear(L);

// -------------------------------


   append(L, 1); // List: 1
   append(L, 2); // List: 1 2
   append(L, 3); // List: 1 2 3

   
   moveFront(L); // Cursor -> 1
   moveNext(L); // Cursor -> 2
   insertBefore(L, 5); // List: 1 5 2 3
   movePrev(L); // Cursor -> 1
   insertAfter(L, 6); // List: 1 5 6 2 3

   delete(L); // List: 1 6 2 3

   // 1 6 2 3
   printList(stdout,L); 
   printf("\n");

   assert(front(L) == 1);
   assert(back(L) == 3);

   clear(L);


   // -----------------------------------

   append(L, 10);
   append(L, 20);
   append(L, 30); // List: 10 20 30

   List Q = copyList(L);

   // Check that both lists have the same elements
   assert(length(L) == length(Q));
   moveFront(L);
   moveFront(Q);
   while(index(L) >= 0 && index(Q) >= 0){
      assert(get(L) == get(Q));
      moveNext(L);
      moveNext(Q);
   }

   // Check that modifying Q doesn't affect L
   append(Q, 40);
   assert(length(L) == 3);
   assert(length(Q) == 4);

   // 10 20 30
   printList(stdout,L); 
   printf("\n");

   // 10 20 30 40 
   printList(stdout,Q); 
   printf("\n");

   clear(L);
   clear(Q);


   //---------------------------------------

   for(int i = 1; i <= 10; i++){
      append(L, i); 
   }

   // Replace every even number with 99
   moveFront(L);
   while(index(L) != -1){
      if(get(L) % 2 == 0){
         set(L,99);
      }
      moveNext(L);
   } 

   // 1 99 3 99 5 99 7 99 9
   printList(stdout,L); 
   printf("\n");


  //------------------------------------------


   List A = newList();
   List B = newList();
   List C = NULL;

   for(int i = 1; i <= 5; i++){
      append(A,i);
      prepend(B,i);
   }

   // 1 2 3 4 5
   // 5 4 3 2 1
   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");


   // 1 2 3 4 5 80
   moveFront(A);
   moveNext(A);
   moveNext(A);
   moveNext(A);
   moveNext(A);
   insertAfter(A, 80);
   printList(stdout,A); 
   printf("\n");


   // 15 300 1 2 3 4 5 80
   moveFront(A);
   insertBefore(A, 15);
   insertBefore(A, 300);
   printList(stdout,A); 
   printf("\n");


   // 15 300 2 3 4 5 80
   delete(A);
   printList(stdout,A); 
   printf("\n");


   // false
   // true
   // false
   // true
   C = copyList(B);
   List D = newList(); // Empty
   List E = newList(); // Empty
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");
   printf("%s\n", equals(D,E)?"true":"false");


   // 5 7 3 2 1
   moveFront(C);
   moveNext(C);
   set(C, 7);
   printList(stdout,C); 
   printf("\n");


   // 5 7 26 3 19 2 1
   moveBack(C);
   movePrev(C);
   movePrev(C);
   insertAfter(C, 19);
   insertBefore(C, 26);
   printList(stdout,C); 
   printf("\n");


   // prints nothing
   clear(A);
   printList(stdout,A); 
   printf("\n");

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);
   freeList(&E);
   freeList(&L);
   freeList(&Q);

   return(0);
   
}