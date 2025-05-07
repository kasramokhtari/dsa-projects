/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{4} 
* Matrix.c
* Function definitions for Matrix ADT 
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj{
    List* rows;
    int size;
    int nnz;
} MatrixObj;

// precondition check functions
static void matrixCheck(Matrix M, const char* functionName){
    if(M == NULL){
        fprintf(stderr, "Matrix Error: calling %s on NULL Graph reference\n", functionName);
        exit(EXIT_FAILURE);
    }
}



// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));

    M->rows = malloc(sizeof(List)*(n+1));
    for(int i = 1; i <= n; i++){
        M->rows[i] = newList();
    }

    M->size = n;
    M->nnz = 0;

    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        for(int i = 1; i <= (*pM)->size; i++){
            List row = (*pM)->rows[i];

            for(moveFront(row); index(row) != -1; moveNext(row)){
                Entry E = (Entry)get(row);
                free(E);
            }

            freeList(&((*pM)->rows[i]));
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}


// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    matrixCheck(M, "size()");
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    matrixCheck(M, "NNZ()");
    return M->nnz;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    matrixCheck(A, "equals()");
    matrixCheck(B, "equals()");

    if(A->size != B->size){
        return 0;
    }

    for(int i = 1; i <= A->size; i++){
        List L = A->rows[i];
        List N = B->rows[i];
        
        if(length(L) != length(N)){
            return 0;
        }

        for(moveFront(L), moveFront(N); index(L) != -1; moveNext(L), moveNext(N)){
            Entry E = (Entry)get(L);
            Entry D = (Entry)get(N);
            if((E->val != D->val) && (E->col != D->col)){
                return 0;
            }
        }
    }

    return 1;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    matrixCheck(M, "makeZero");
    for(int i = 1; i <= M->size; i++){
        List L = M->rows[i];

        moveFront(L);
        while(index(L) != -1){
            free(get(L));
            delete(L);
            moveFront(L);
        }
    }
    M->nnz = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    matrixCheck(M, "changeEntry()");
    if(i > M->size || i < 1 || j > M->size || j < 1){
        fprintf(stderr, "Indices out of range");
        exit(EXIT_FAILURE);
    }

    List L = M->rows[i];
    int inserted = 0;

    for(moveFront(L); index(L) != -1; moveNext(L)){
        Entry E = (Entry)get(L);
        if(E->col == j){
            if(x != 0){
                E->val = x;
            }
            else{
                free(get(L));
                delete(L);
                M->nnz--;
            }
            return;
        }
        if(j < E->col){
            if(x == 0){
                return;
            }
            Entry N = malloc(sizeof(EntryObj));
            N->col = j;
            N->val = x;
            insertBefore(L, N);
            M->nnz++;
            inserted = 1;
            break;
        }
    }
    if(!inserted && x != 0){
        Entry N = malloc(sizeof(EntryObj));
        N->col = j;
        N->val = x;
        append(L, N);
        M->nnz++;
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    matrixCheck(A, "copy()");

    Matrix N = newMatrix(A->size);
    for(int i = 1; i <= N->size; i++){
        List L = A->rows[i];
        List nL = N->rows[i];

        for(moveFront(L); index(L) != -1; moveNext(L)){
            Entry E = (Entry)get(L);

            Entry newE = malloc(sizeof(EntryObj));
            newE->col = E->col;
            newE->val = E->val;

            append(nL, newE);
        }
    }
    N->nnz = A->nnz;
    return N;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    matrixCheck(A, "transpose()");

    Matrix N = newMatrix(A->size);
    for(int i = 1; i <= A->size; i++){
        List L = A->rows[i];


        for(moveFront(L); index(L) != -1; moveNext(L)){
            Entry E = (Entry)get(L);
            int c = E->col;

            Entry newE = malloc(sizeof(EntryObj));
            newE->col = i;
            newE->val = E->val;

            List nL = N->rows[c];
            append(nL, newE);
        }
    }
    N->nnz = A->nnz;
    return N;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    matrixCheck(A, "scalarMult()");

    Matrix N = newMatrix(A->size);
    for(int i = 1; i <= N->size; i++){
        List L = A->rows[i];
        List nL = N->rows[i];

        for(moveFront(L); index(L) != -1; moveNext(L)){
            Entry E = (Entry)get(L);

            Entry newE = malloc(sizeof(EntryObj));
            newE->col = E->col;
            newE->val = E->val * x;

            append(nL, newE);
        }
    }
    N->nnz = A->nnz;
    return N;
}






List rowSum(List A, List B){
    List L = newList();

    List tempA = copyList(A);
    List tempB = copyList(B);

    moveFront(tempA);
    moveFront(tempB);


    while(1){
        while(index(tempB) == -1 && index(tempA) != -1){
            Entry a = (Entry)get(tempA);
            Entry E = malloc(sizeof(EntryObj));

            E->col = a->col;
            E->val = a->val;
            
            append(L, E);
            moveNext(tempA);
        }
        while(index(tempB) != -1 && index(tempA) == -1){
            Entry b = (Entry)get(tempB);
            Entry E = malloc(sizeof(EntryObj));

            E->col = b->col;
            E->val = b->val;
            append(L, E);
            moveNext(tempB);
        }

        if(index(tempA) == -1 && index(tempB) == -1){
            break;
        }

        Entry a = (Entry)(get(tempA));
        Entry b = (Entry)(get(tempB));
        if(a->col == b->col){
            Entry E = malloc(sizeof(EntryObj));
            E->col = a->col;
            E->val = (a->val)+(b->val);
            if(E->val != 0){
                append(L, E);
            }
            else{
                free(E);
            }
            moveNext(tempA);
            moveNext(tempB);
        }
        else if(a->col < b->col){
            Entry E = malloc(sizeof(EntryObj));
            E->col = a->col;
            E->val = a->val;

            append(L, E);
            moveNext(tempA);
        }
        else{
            Entry E = malloc(sizeof(EntryObj));
            E->col = b->col;
            E->val = b->val;

            append(L, E);
            moveNext(tempB);
        }
    }


    freeList(&tempA);
    freeList(&tempB);
    return L;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    matrixCheck(A, "sum()");
    matrixCheck(B, "sum()");
    if(A->size != B->size){
        fprintf(stderr, "Matricies A and B are different sizes");
        exit(EXIT_FAILURE);
    }

    Matrix N = newMatrix(A->size);
    int count = 0;

    for(int i = 1; i <= N->size; i++){
        List a = A->rows[i];
        List b = B->rows[i];

        freeList(&(N->rows[i]));

        N->rows[i] = rowSum(a,b);

        for(moveFront(N->rows[i]); index(N->rows[i]) != -1; moveNext(N->rows[i])){
            count++;
        }
    }
    

    N->nnz = count;
    return N;
}



List rowDiff(List A, List B){
    List L = newList();

    List tempA = copyList(A);
    List tempB = copyList(B);

    moveFront(tempA);
    moveFront(tempB);

    while(1){
        while(index(tempB) == -1 && index(tempA) != -1){
            Entry a = (Entry)get(tempA);
            Entry E = malloc(sizeof(EntryObj));

            E->col = a->col;
            E->val = a->val;
            
            append(L, E);
            moveNext(tempA);
        }
        while(index(tempB) != -1 && index(tempA) == -1){
            Entry b = (Entry)get(tempB);
            Entry E = malloc(sizeof(EntryObj));

            E->col = b->col;
            E->val = -(b->val);
            append(L, E);
            moveNext(tempB);
        }

        if(index(tempA) == -1 && index(tempB) == -1){
            break;
        }

        Entry a = (Entry)(get(tempA));
        Entry b = (Entry)(get(tempB));
        if(a->col == b->col){
            Entry E = malloc(sizeof(EntryObj));
            E->col = a->col;
            E->val = (a->val)-(b->val);

            if(E->val != 0){
                append(L, E);
            }
            else{
                free(E);
            }
            moveNext(tempA);
            moveNext(tempB);
        }
        else if(a->col < b->col){
            Entry E = malloc(sizeof(EntryObj));
            E->col = a->col;
            E->val = a->val;

            append(L, E);
            moveNext(tempA);
        }
        else{
            Entry E = malloc(sizeof(EntryObj));
            E->col = b->col;
            E->val = -(b->val);

            append(L, E);
            moveNext(tempB);
        }
    }

    freeList(&tempA);
    freeList(&tempB);
    return L;
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    matrixCheck(A, "diff()");
    matrixCheck(B, "diff()");
    if(A->size != B->size){
        fprintf(stderr, "Matricies A and B are different sizes");
        exit(EXIT_FAILURE);
    }

    Matrix N = newMatrix(A->size);
    int count = 0;

    for(int i = 1; i <= N->size; i++){
        List a = A->rows[i];
        List b = B->rows[i];

        freeList(&(N->rows[i]));

        N->rows[i] = rowDiff(a,b);

        for(moveFront(N->rows[i]); index(N->rows[i]) != -1; moveNext(N->rows[i])){
            count++;
        }
    }
    
    N->nnz = count;
    return N;
}

double vectorDot(List P, List Q){
    double dot = 0;

    moveFront(P);
    moveFront(Q);
    
    while(index(P) != -1 && index(Q) != -1){
        Entry p = (Entry)get(P);
        Entry q = (Entry)get(Q);

        if(p->col == q->col){
            dot += (p->val) * (q->val);

            moveNext(P);
            moveNext(Q);
        }
        else if(p->col < q->col){
            moveNext(P);
        }
        else{
            moveNext(Q);
        }
    }

    return dot;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    matrixCheck(A, "product()");
    matrixCheck(B, "product()");
    if(A->size != B->size){
        fprintf(stderr, "Matricies A and B are different sizes");
        exit(EXIT_FAILURE);
    }

    Matrix N = newMatrix(A->size);

    Matrix T = transpose(B);

    int count = 0;
    for(int i = 1; i <= A->size; i++){
        List L = T->rows[i];
        if(isEmpty(T->rows[i])){
            continue;
        }

        for(int j = 1; j <= A->size; j++){
            // if A->rows[j] is empty, you can skip this entire iteration
            if(isEmpty(A->rows[j])){
                continue;
            }
            Entry E = malloc(sizeof(EntryObj));
            E->val = vectorDot(A->rows[j], L);
            E->col = i;

            if(E->val == 0){
                free(E);
                continue;
            }
            
            List C = N->rows[j];
            append(C, E);
            count++;
        }
    }

    freeMatrix(&T);
    N->nnz = count;
    return N;
}


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){

    for(int i = 1; i <= M->size; i++){
        List L = M->rows[i];
        if(isEmpty(L)){
            continue;
        }

        fprintf(out, "%d:", i);
        for(moveFront(L); index(L) != -1; moveNext(L)){
            double val = ((Entry)get(L))->val;
            int col = ((Entry)get(L))->col;
            fprintf(out, " (%d, %.1lf)", col, val);
        }
        fprintf(out, "\n");
    }
}