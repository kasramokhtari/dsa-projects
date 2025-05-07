/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{4} 
* MatrixTest.c
* Test cases for Matrix ADT
***/ 

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=1000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   
   Matrix H, C, D, E, F, G, Q, Z, J, X;

   changeEntry(A, 1,1,1); 
   changeEntry(A, 1,2,2); 
   changeEntry(A, 1,3,-3); 
   changeEntry(A, 2,1,4); 
   changeEntry(A, 2,2,5); 
   changeEntry(A, 2,3,-6); 
   changeEntry(A, 3,1,7); 
   changeEntry(A, 3,2,-8); 
   changeEntry(A, 3,3,9); 

   changeEntry(B, 1,1,9);
   changeEntry(B, 1,2,8);
   changeEntry(B, 1,3,-7);
   changeEntry(B, 2,1,6);
   changeEntry(B, 2,2,5);
   changeEntry(B, 2,3,-4);
   changeEntry(B, 3,1,3);
   changeEntry(B, 3,2,2);
   changeEntry(B, 3,3,-1);

   // Making sure that it prents 
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   printf("Scalar\n");
   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   printf("Sum\n");
   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   printf("Diff A-A:\n");
   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   freeMatrix(&E);

   printf("Diff A-B:\n");
   E = diff(A, B);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   printf("Transpose B:\n");
   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   freeMatrix(&F);

   printf("Transpose A:\n");
   F = transpose(A);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   freeMatrix(&F);


   printf("Product\n");
   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   freeMatrix(&G);


   printf("Copy\n");
   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   printf("\n");
   printf("\n");
   printf("\n");
   printf("\n");

   // testing changeEntry and equals
   Q = newMatrix(n);
   Z = newMatrix(n);
   changeEntry(Q, 1, 1, 1);
   changeEntry(Q, 1, 3, 1);
   changeEntry(Z, 1, 1, 1);
   changeEntry(Z, 1, 3, 1);
   changeEntry(Q, 1, 3, 0);


   printf("%d\n", NNZ(A));
   printMatrix(stdout, Z);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, Q);
   printf("\n");

   printf("Transpose Q:\n");
   F = transpose(Q);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   // testing changeEntry and equals to make sure it updates the matrix correctly
   bool eq = equals(Q, Z);
   printf("SHOULD BE FALSE: %d\n", eq);
   printf("\n");

   // test product on a specific matrix with some empty values
   printf("Product \n");
   J = product(Q, Z);
   printf("%d\n", NNZ(J));
   printMatrix(stdout, J);
   printf("\n");

   printf("Product \n");
   X = product(Q, Z);
   printf("%d\n", NNZ(X));
   printMatrix(stdout, X);
   printf("\n");

   eq = equals(J, X);
   printf("SHOULD BE TRUE: %d\n", eq);
   printf("\n");

   makeZero(X);

   // Should print 0 and nothing
   printf("%d\n", NNZ(X));
   printMatrix(stdout, X);



   // testing freeMatrix
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&Q);
   freeMatrix(&Z);
   freeMatrix(&J);
   freeMatrix(&X);

   return EXIT_SUCCESS;
}