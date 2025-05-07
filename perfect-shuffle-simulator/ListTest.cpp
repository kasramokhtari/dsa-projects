/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{5} 
* ListTest.cpp
* Test file for the List ADT
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include <cassert>
#include"List.h"

using namespace std;

int main(){

  List A, B, C, D;

  // insertAfter/insertBefore test
  for(int i=1; i<=10; i++){
    A.insertAfter(i);
    B.insertAfter(i*2);
    C.insertBefore(i+1);
    D.insertBefore(i*4);
  }

  cout << endl;

  // to string and << operator test
  cout << "A = " << A << endl;
  cout << "B = " << B << endl;
  cout << "C = " << C << endl;
  cout << "D = " << D << endl;
  cout << endl;


  // length test
  assert(A.length() == 10);
  assert(C.length() == 10);

  // front and back test
  assert(A.front() == 10);
  assert(A.back() == 1);
  assert(D.front() == 4);
  assert(D.back() == 40);


  // moveBack, moveFront, and position Test
  A.moveBack();
  B.moveFront();
  C.moveFront();
  D.moveFront();

  assert(A.position() == A.length());
  assert(B.position() == 0);
  assert(C.position() == 0);
  assert(D.position() == 0);


  // movePrev, moveNext, peekPrev, peekNext Test
  for(int i = 0; i < 4; i++){
    A.movePrev();
    B.moveNext();
  }

  D.moveBack();
  for(int i = 0; i < 7; i++){
    C.moveNext();
    D.movePrev();
  }

  assert(A.peekPrev() == 5);
  assert(A.peekNext() == 4);

  assert(B.peekPrev() == 14);
  assert(B.peekNext() == 12);

  assert(C.peekPrev() == 8);
  assert(C.peekNext() == 9);

  assert(D.peekPrev() == 12);
  assert(D.peekNext() == 16);

  // Copy constructor, = operator (and equals function, and == operator test
  List E = D;
  assert((E == D) == true);
  assert((E == A) == false);

  E = B;
  assert((E == B) == true);
  assert((E.equals(B)) == true);

  // concat test
  List F = A.concat(C);
  assert(F.length() == 20);
  assert(F.front() == 10);
  assert(F.back() == 11);

  // F = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11)
  cout << "F = " << F << endl;

  //cleanup test
  F.cleanup();

  // F = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11)
  cout << "F = " << F << endl << endl;
  assert(F.length() == 11);
  assert(F.front() == 10);
  assert(F.back() == 11);

  // findPrev and findNext Test
  F.moveBack();
  assert(F.findPrev(1) == 9);
  assert(F.findPrev(20) == -1);

  F.moveFront();
  assert(F.findNext(5) == 6);
  assert(F.findNext(20) == -1);


  cout << "A = " << A << endl;
  cout << "B = " << B << endl;
  cout << "C = " << C << endl;
  cout << "D = " << D << endl << endl;


  // eraseBefore and eraseAfter tests
  A.moveFront();
  A.moveNext();

  A.eraseBefore();
  A.eraseAfter();

  B.moveBack();
  B.movePrev();
  B.movePrev();

  B.eraseBefore();
  B.eraseAfter();

  // A = (8, 7, 6, 5, 4, 3, 2, 1)
  cout << "A = " << A << endl;

  // B = (20, 18, 16, 14, 12, 10, 8, 2)
  cout << "B = " << B << endl << endl;

  // setBefore and setAfter
  A.moveFront();
  B.moveBack();

  A.setAfter(100);
  B.setBefore(200);

  assert(A.front() == 100);
  assert(B.back() == 200);

  // clear test
  A.clear();
  B.clear();
  C.clear();
  D.clear();
  E.clear();
  F.clear();

  assert(A == B && B == C && C == D && D == E && E == F);


  return( EXIT_SUCCESS );
}