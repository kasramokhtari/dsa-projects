/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{2} 
* List.c
* Function defintions for List ADT 
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    ListElement data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    int length;
    Node cursor;
    int cursorIndex;
} ListObj;

// newNode()
// Returns reference to a new Node Object, initializing the data value of the node to the provided arguement
Node newNode(ListElement data){
    Node n = malloc(sizeof(NodeObj));
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    return(n);
}


// freeNode()
// Frees the node pointed to by Node *pN
void freeNode(Node* pN){
    if(pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Creates a new empty list
List newList(){
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->length = 0;
    L->cursor = NULL;
    L->cursorIndex = -1;
    return L;
}

//freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        while(!isEmpty(*pL)){
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


// isEmpty()
// Returns true if L is empty, false if otherwise
bool isEmpty(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling isEmpty() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length == 0);
}

//_________________ACCESS_________________________________________________________________________________________________________


// length()
// Returns the number of elements in the list provided
int length(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    } 
    return L->length;
}

// index()
// Returns the index of the cursor if defined 
int index(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursor == NULL){
        return -1;
    }
    return L->cursorIndex;
}

// front()
 // Returns front element of L. Pre: length()>0
int front(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    } 
    if(length(L) < 1){
        fprintf(stderr, "%s", "List Error: calling front() on an empty list\n");
        exit(EXIT_FAILURE); 
    }
    return L->front->data;
}

// back()
 // Returns back element of L. Pre: length()>0
int back(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) < 1){
        fprintf(stderr, "%s", "List Error: calling back() on an empty list\n");
        exit(EXIT_FAILURE); 
    }
    return L->back->data;
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) < 1){
        fprintf(stderr, "%s", "List Error: calling get() on an empty list\n");
        exit(EXIT_FAILURE); 
    }
    if(index(L) < 0){
        fprintf(stderr, "%s", "Cursor is undefined\n");
        exit(EXIT_FAILURE); 
    }

    return L->cursor->data;

}



// equals()
// Returns true iff Lists A and B contain the same
 // sequence of elements, returns false otherwise.
 bool equals(List A, List B){
    if(A == NULL || B == NULL){
        fprintf(stderr, "%s", "List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(A) != length(B)){
        return false;
    }
    
    Node aCurrent = A->front;
    Node bCurrent = B->front;

    while(aCurrent != NULL){
        if(aCurrent->data != bCurrent->data){
            return false;
        }
        aCurrent = aCurrent->next;
        bCurrent = bCurrent->next;
    }

    return true;
 }


////____________________________Manipulation procedures______________________________________________________________________________________________

// clear()
// Resets L to empty state
void clear(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    while(!isEmpty(L)){
        deleteFront(L);
    }

    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}

// set()
// Overwrites the cursor element’s data with x.
void set(List L, int x){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(L->cursorIndex < 0){
        fprintf(stderr, "%s", "Cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    L->cursor->data = x;
}

// apend()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x){
    Node n = newNode(x);

    if(isEmpty(L)){
        L->front = n;
        L->back = n;
        L->length++;
        return;
    }

    L->back->next = n;
    n->prev = L->back;
    L->back = n;

    L->length++;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x){
    Node n = newNode(x);

    if(isEmpty(L)){
        L->front = n;
        L->back = n;
    }
    else{
        L->front->prev = n;
        n->next = L->front;
        L->front = n;
    }

    L->length++;

    if(L->cursorIndex != -1){
        L->cursorIndex++;
    }
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(isEmpty(L)){
        return;
    }

    L->cursor = L->front;
    L->cursorIndex = 0;
}

//moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(isEmpty(L)){
        return;
    }

    L->cursor = L->back;
    L->cursorIndex = L->length-1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        return;
    }
    if(L->cursorIndex == 0){
        L->cursorIndex = -1;
        L->cursor = NULL;
        return;
    }

    L->cursor = L->cursor->prev;
    L->cursorIndex--;
}

// moveNext()
// If cursor is defined and not at back, move cursor one 
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursorIndex < 0){
        return;
    }
    if(L->cursor->next == NULL){
        L->cursorIndex = -1;
        L->cursor = NULL;
        return;
    }

    L->cursor = L->cursor->next;
    L->cursorIndex++;
}

// insertBefore()
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(length(L) == 0 || index(L) < 0){
        fprintf(stderr, "%s", "Cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    Node n = newNode(x);
    
    n->prev = L->cursor->prev;
    n->next = L->cursor;

    if(L->cursor == L->front){
        L->front = n;
    }
    else {
        L->cursor->prev->next = n;
    }

    L->cursor->prev = n;

    L->cursorIndex++;
    L->length++;
}

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0 || index(L) < 0){
        fprintf(stderr, "%s", "Cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    Node n = newNode(x);

    n->next = L->cursor->next;
    n->prev = L->cursor;

    if(L->cursor == L->back){
        L->back = n;
    }
    else {
        L->cursor->next->prev = n;
    }

    L->cursor->next = n;

    L->length++;
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0){
        fprintf(stderr, "%s", "Calling deleteFront() on an empty list\n");
        exit(EXIT_FAILURE);
    }
    
    Node n = L->front;

    if(L->cursor == L->front){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }

    if(length(L) == 1){
        L->front = NULL;
        L->back = NULL;
    }
    else {
        L->front = L->front->next;
        L->front->prev = NULL;
        if(L->cursorIndex > 0){
            L->cursorIndex--;
        }
    }

    freeNode(&n);

    L->length--;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0){
        fprintf(stderr, "%s", "Calling deleteBack() on an empty list\n");
        exit(EXIT_FAILURE);
    }
    
    Node n = L->back;

    if(L->cursor == L->back){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }

    if(length(L) == 1){
        L->front = NULL;
        L->back = NULL;
    }
    else {
        L->back = L->back->prev;
        L->back->next = NULL;
    }

    freeNode(&n);

    L->length--;
}



// delete()
// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) == 0 || index(L) < 0){
        fprintf(stderr, "%s", "Cursor is undefined\n");
        exit(EXIT_FAILURE);
    }

    Node n = L->cursor;

    if(L->cursor == L->front){
        deleteFront(L);
    }
    else if(L->cursor == L->back){
        deleteBack(L);
    }
    else {
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&n);
        L->length--;
    }

    L->cursor = NULL;
    L->cursorIndex = -1;

}

// printList()
 // Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if(length(L) == 0){
        return;
    }
    
    Node current = L->front;

    while(current != NULL){
        fprintf(out, "%d", current->data);
        current = current->next;

        if(current != NULL){
            fprintf(out, " ");
        }
    }
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L){
    if(L == NULL){
        fprintf(stderr, "%s", "List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List newL = newList();

    if(isEmpty(L)){
        return newL;
    }


    Node oldCurrent = L->front;
    newL->front = newNode(L->front->data);
    newL->length = 1;

    Node newCurrent = newL->front;
    
    while(oldCurrent->next != NULL){
        oldCurrent = oldCurrent->next;
        newCurrent->next = newNode(oldCurrent->data);
        newCurrent->next->prev = newCurrent;
        newCurrent = newCurrent->next;
        newL->length++;
    }

    newL->back = newCurrent;

    newL->cursor = NULL;
    newL->cursorIndex = -1;

    return newL;
}
