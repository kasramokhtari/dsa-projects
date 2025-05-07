/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{4} 
* ListTest.c
* Test cases for List ADT
***/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <assert.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   // Testing the creation of a newList(), length(), and isEmpty()
   List A = newList();
   assert(A != NULL);
   assert(length(A) == 0);
   assert(isEmpty(A) == true);

   // should print nothing
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }

   // testing prepend(), append(), front(), back(), and length()
   List B = newList();
   int w = 200, z = 400;
   prepend(B, &w); 
   assert(*(int *)front(B) == w);

   append(B, &z); 
   assert(*(int *)back(B) == z);
   assert(length(B) == 2);


   // testing moveFront(), moveBack(), moveNext(), movePrev(), and index()
   List C = newList();

   int a = 5, b = 10, c = 15, u = -5;
   append(C, &a);
   append(C, &b);
   append(C, &c);

   moveFront(C);
   assert(*(int *)get(C) == a);

   moveNext(C);
   assert(*(int *)get(C) == b);

   assert(index(C) == 1);

   moveBack(C);
   assert(*(int *)get(C) == c);

   movePrev(C);
   assert(*(int *)get(C) == b);

   movePrev(C);
   assert(*(int *)get(C) == a);

   set(C, &u);
   assert(*(int *)get(C) == u);


   List D = newList();
   int r = 5, e = 10, q = 15, k = 30;

   append(D, &r); 
   append(D, &q); // List: 5, 15
   moveFront(D);
   insertAfter(D, &k); // List: 5, 30, 15
   moveNext(D); 
   insertBefore(D, &e); // List 5, 10, 30, 15

   assert(*(int *)front(D) == r);
   assert(*(int *)get(D) == k);
   assert(*(int *)back(D) == q);

   assert(length(D) == 4);

   deleteFront(D); // deletes 5
   deleteBack(D); // deletes 15

   // prints 10 30
   for(moveFront(D); index(D)>=0; moveNext(D)){
      printf("%d ", *(int*)get(D));
   }
   printf("\n");

   moveBack(D);
   delete(D);

   // prints 10
   for(moveFront(D); index(D)>=0; moveNext(D)){
      printf("%d ", *(int*)get(D));
   }
   printf("\n");

   List E = copyList(D);

   assert(length(E) == 1);

   // also prints 10 (copy of D)
   for(moveFront(D); index(D)>=0; moveNext(D)){
      printf("%d ", *(int*)get(D));
   }
   printf("\n");

   clear(D);
   assert(length(D) == 0);

   // prints nothing
   for(moveFront(D); index(D)>=0; moveNext(D)){
      printf("%d ", *(int*)get(D));
   }


   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);
   freeList(&E);

   return(0);
}