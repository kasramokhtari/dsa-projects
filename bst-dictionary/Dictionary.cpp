/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{7} 
* Dictionary.cpp
* Function definitions for Dictionary ADT 
***/ 

#include "Dictionary.h"

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s.append(R->key);
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R == N){
        return;
    }

    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);

}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R.
void Dictionary::postOrderDelete(Node* R){
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}



// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil){
        return nil;
    }

    if(k == R->key){
        return R;
    }
    if(k < R->key){
        return search(R->left, k);
    }
    else{
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    if(R == nil){
        return nil;
    }

    Node* T = R;

    while(T->left != nil){
        T = T->left;
    }
    return T;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R == nil){
        return nil;
    }

    Node* T = R;

    while(T->right != nil){
        T = T->right;
    }
    return T;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == nil){
        return nil;
    }
    
    if(N->right != nil){
        return findMin(N->right);
    }

    Node* P = N->parent;
    while(P != nil && N == P->right){
        N = P;
        P = P->parent;
    }
    return P;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == nil){
        return nil;
    }

    if(N->left != nil){
        return findMax(N->left);
    }

    Node* P = N->parent;
    while(P != nil && N == P->left){
        N = P;
        P = P->parent;
    }
    return P;
}

// Class Constructors & Destructors ----------------------------------------

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("NIL", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("NIL", -1);
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
    postOrderDelete(root);
    delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    return (search(root, k) != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(search(root, k) == nil){ 
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }

    Node* N = search(root, k);

    return N->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// // Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* F = search(root, k);
    if(F != nil){
        F->val = v;
        return;
    }

    Node* Y = nil;
    Node* X = root;
    Node* Z = new Node(k, v);
    Z->left = nil;
    Z->right = nil;


    while(X != nil){
        Y = X;
        if(Z->key < X->key){
            X = X->left;
        }
        else{
            X = X->right;
        }
    }
    Z->parent = Y;

    if(Y == nil){
        root = Z;
    }
    else if(Z->key < Y->key){
        Y->left = Z;
    }
    else{
        Y->right = Z;
    }

    num_pairs++;
}


// Transplant()
// replace subtree rooted at u with subtree rooted at v
void Dictionary::Transplant(Node* U, Node* V){
    if(U->parent == nil){
        root = V;
    }
    else if(U == U->parent->left){
        U->parent->left = V;
    }
    else{
        U->parent->right = V;
    }
    if(V != nil){
        V->parent = U->parent;
    }
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    if(search(root, k) == nil){
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    Node* Z = search(root, k);

    if(current == Z){
        current = nil;
    }

    if(Z->left == nil){
        Transplant(Z, Z->right);
        delete Z;
    }
    else if(Z->right == nil){
        Transplant(Z, Z->left);
        delete Z;
    }
    else{
        Node* Y = findMin(Z->right);
        if(Y->parent != Z){
            Transplant(Y, Y->right);
            Y->right = Z->right;
            Y->right->parent = Y;
        }
        Transplant(Z, Y);
        Y->left = Z->left;
        Y->left->parent = Y;
        delete Z;
    }

    num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(num_pairs == 0){
        return;
    }
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(num_pairs == 0){
        return;
    }
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}


// // Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    std::string s1 = to_string();
    std::string s2 = D.to_string();

    return s1 == s2;
}


// // Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this == &D){
        return *this;
    }

    Dictionary temp = D;

    std::swap(nil, temp.nil);
    std::swap(current, temp.current);
    std::swap(root, temp.root);
    std::swap(num_pairs, temp.num_pairs);

    return *this;
}