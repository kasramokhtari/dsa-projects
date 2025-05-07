/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{8} 
* DictionaryTest.cpp
* Test file for RBT Dictionary ADT
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include<cassert>
#include"Dictionary.h"

using namespace std;

int main(){

   Dictionary D;

   // size() and contains() test on empty state
   assert(D.size() == 0);
   assert(!D.contains("random"));

   // prints nothing (<< operator and .to_string() test)
   std::cout << D << std::endl;
   // also prints nothing
   std::cout << D.to_string() << std::endl;


   // setValue() test
   D.setValue("car", 5);
   D.setValue("dog", 10);
   D.setValue("tree", 20);
   D.setValue("zoo", 37);
   D.setValue("green", 900);

   // size() and contains test
   assert(D.size() == 5);
   assert(D.contains("dog"));
   assert(D.contains("zoo"));
   
   // getValue() test
   assert(D.getValue("car") == 5);
   assert(D.getValue("tree") == 20);
   assert(D.getValue("green") == 900);

   // setValue() test on existing key
   D.setValue("dog", 888);
   assert(D.getValue("dog") == 888);

   std::cout << D << std::endl;
   // remove() test
   D.remove("dog");
   assert(!D.contains("dog"));
   assert(D.size() == 4);

   // prints the tree in alphabetical order (tests inOrderString)
   std::cout << D << std::endl;

   // begin(), next(), end(), currentKey(), currentVal() test
   
   D.begin(); // begin() uses, thus tests, findMin
   assert(D.currentKey() == "car");
   assert(D.currentVal() == 5);

   D.next(); // next() uses, thus tests, findNext()
   D.next();

   assert(D.currentKey() == "tree");
   assert(D.currentVal() == 20);

   D.end(); // end() uses, thus tests, findMax
   assert(D.currentKey() == "zoo");
   assert(D.currentVal() == 37);

   D.prev(); // prev() uses, thus tests, findPrev
   D.prev();
   assert(D.currentKey() == "green");
   assert(D.currentVal() == 900);

   assert(D.hasCurrent());

   // prints the tree in pre-order tree walk (pre_string and preOrderString test)
   std::cout << D.pre_string() << std::endl;

   Dictionary A;

   A.setValue("wow", 1);
   A.setValue("hello", 1);
   A.setValue("cool", 1);
   A.setValue("sent", 1);

   // copy constructor and comparison operator check (also equals() and preOrderCopy() check)
   Dictionary B = D;
   Dictionary C = B;

   // checking that when copying, the copy constructor creates identical trees
   assert(C.pre_string() == B.pre_string());

   assert(!(A == B));
   assert(!(A == D));
   assert(D == B);

   assert(D.equals(B));
   assert(!(A.equals(B)));

   // clear() test
   D.clear();
   assert(D.size() == 0);
   assert(!D.contains("dog"));

   return( EXIT_SUCCESS );
}