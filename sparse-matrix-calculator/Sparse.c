/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{4} 
* Sparse.c
* Main file program
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

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

    int size;
    int nnzA;
    int nnzB;


    fgets(buffer, sizeof(buffer), in);

    sscanf(buffer, "%d %d %d", &size, &nnzA, &nnzB);

    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);

    fgets(buffer, sizeof(buffer), in);
    for(int i = 1; i <= nnzA; i++){
        int row, col;
        double val;
        fgets(buffer, sizeof(buffer), in);
        sscanf(buffer, "%d %d %lf", &row, &col, &val);


        changeEntry(A, row, col, val);
    }

    fgets(buffer, sizeof(buffer), in);
    for(int i = 1; i <= nnzB; i++){
        int row, col;
        double val;
        fgets(buffer, sizeof(buffer), in);
        sscanf(buffer, "%d %d %lf", &row, &col, &val);

        printf("%s", buffer);
        printf("%d %d %lf\n\n", row, col, val);

        changeEntry(B, row, col, val);
    }


    fprintf(out, "A has %d non-zero entries:\n", nnzA);
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", nnzB);
    printMatrix(out, B);
    fprintf(out, "\n");


    fprintf(out, "(1.5)*A = \n");
    Matrix D = scalarMult(1.5, A);
    printMatrix(out, D);
    fprintf(out, "\n");


    fprintf(out, "A+B = \n");
    Matrix S = sum(A,B);
    printMatrix(out, S);
    fprintf(out, "\n");


    fprintf(out, "A+A = \n");
    Matrix M = sum(A,A);
    printMatrix(out, M);
    fprintf(out, "\n");


    fprintf(out, "B-A = \n");
    Matrix C = diff(B,A);
    printMatrix(out, C);
    fprintf(out, "\n");

    fprintf(out, "A-A = \n");
    Matrix E = diff(A,A);
    printMatrix(out, E);
    fprintf(out, "\n");

    fprintf(out, "Transpose(A) = \n");
    Matrix T = transpose(A);
    printMatrix(out, T);
    fprintf(out, "\n");

    fprintf(out, "A*B = \n");
    Matrix P = product(A,B);
    printMatrix(out, P);
    fprintf(out, "\n");

    fprintf(out, "B*B = \n");
    Matrix F = product(B,B);
    printMatrix(out, F);


    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&D);
    freeMatrix(&S);
    freeMatrix(&M);
    freeMatrix(&C);
    freeMatrix(&E);
    freeMatrix(&T);
    freeMatrix(&P);
    freeMatrix(&F);

    fclose(in);
    fclose(out);

    return(0);
}
