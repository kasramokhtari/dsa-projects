/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{5} 
* List.cpp
* Function definitions for List ADT 
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include <climits>
#include <vector>

#include"List.h"

List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List(){
    frontDummy = new Node(INT_MIN);
    backDummy = new Node(INT_MAX);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new Node(INT_MIN);
    backDummy = new Node(INT_MAX);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node *N = nullptr;
    for(N = L.frontDummy->next; N != L.backDummy; N = N->next){
        insertAfter(N->data);
        moveNext();
    }

    pos_cursor = 0;
    num_elements = L.num_elements;

    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

 // Destructor
List::~List(){
    Node* N = frontDummy;
    while(N != nullptr){
        Node* temp = N;
        N = N->next;
        delete temp;
    }
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(num_elements == 0){
        throw std::length_error("List: front(): empty list");
    }
    return (frontDummy->next)->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(length() == 0){
        throw std::length_error("List: back(): empty list");
    }
    return (backDummy->prev)->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    if(pos_cursor > length() || pos_cursor < 0){
        throw std::range_error("List: position(): cursor is outside range");
    }
    return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(position() == length()){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(position() == 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(afterCursor != backDummy){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(position() >= length()){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    ListElement elem = afterCursor->data;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    pos_cursor++;

    return elem;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(position() <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    ListElement elem = beforeCursor->data;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;

    return elem;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);

    beforeCursor->next = N;
    N->prev = beforeCursor;

    N->next = afterCursor;
    afterCursor->prev = N;

    afterCursor = N;

    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);

    beforeCursor->next = N;
    N->prev = beforeCursor;

    afterCursor->prev = N;
    N->next = afterCursor;

    beforeCursor = N;

    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(position() >= length()){
        throw std::range_error("List: setAfter(): cursor at back");
    }

    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(position() <= 0){
        throw std::range_error("List: setBefore(): cursor at front");
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(position() >= length()){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    beforeCursor->next = afterCursor->next;
    (afterCursor->next)->prev = beforeCursor;

    delete afterCursor;

    afterCursor = beforeCursor->next;
    num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(position() <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    afterCursor->prev = beforeCursor->prev;
    (beforeCursor->prev)->next = afterCursor;

    delete beforeCursor;

    beforeCursor = afterCursor->prev;
    pos_cursor--;
    num_elements--;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(afterCursor != backDummy){
        moveNext();
        if(beforeCursor->data == x){
            return pos_cursor;
        }
    }

    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(beforeCursor != frontDummy){
        movePrev();
        if(afterCursor->data == x){
            return pos_cursor;
        }
    }

    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
    std::vector<int> elemsFound;

    int val;

    Node* N = afterCursor;
    while(N != nullptr){
        if(findPrev(N->data) == -1){
            val = N->data;
            break;
        }
        N = N->next;
    }

    moveFront();
    while(afterCursor != backDummy){

        ListElement currentElem = peekNext();

        bool found = false;
        for(int elem: elemsFound){
            if(elem == currentElem){
                found = true;
                break;
            }
        }

        if(found){
            eraseAfter();
        }
        else{
            elemsFound.push_back(peekNext());
            moveNext();
        }
    }

    Node* n = frontDummy->next;
    moveFront();
    while(n->data != val){
        moveNext();
        n = n->next;
    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List newList = *this;

    Node *N = nullptr;
    newList.moveBack();
    for(N = L.frontDummy->next; N != L.backDummy; N = N->next){
        newList.insertAfter(N->data);
        newList.moveNext();
    }

    newList.moveFront();
    return newList;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;

    std::string s = "(";

    for(N = frontDummy->next; N != backDummy; N = N->next){
        s += std::to_string(N->data);

        if(N->next != backDummy){
            s += ", ";
        }
    }

    s += ")";
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    if(length() != R.length()){
        return false;
    }

    Node* N = R.frontDummy->next;
    Node* C = frontDummy->next;

    while(N != R.backDummy && C != backDummy){
        if(N->data != C->data){
            return false;
        }

        N = N->next;
        C = C->next;
    }

    return true;
}


// // Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if(this == &L){
        return *this;
    }

    List temp = L;

    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);

    return *this;
}