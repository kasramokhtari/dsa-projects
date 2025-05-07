/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{6} 
* BigInteger.cpp
* Function definitions for BigInteger ADT 
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include<string>
#include "BigInteger.h"
#include "List.h"


const int base = 1000000000;
const int power = 9;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    if(x < 0){
        signum = -1;
        x *= -1;
    }
    else if(x > 0){
        signum = 1;
    }
    else{
        signum = 0;
        return;
    }

    while(x != 0){
        long val = x % base;
        digits.insertBefore(val);
        x /= base;
    }
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if(s.length() == 0){
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    if(s.length() == 1 && (s[0] == '-' || s[0] == '+')){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    if(s[0] == '-'){
        signum = -1;
        s = s.substr(1,s.length()-1);
    }
    else if(s[0] == '+'){
        signum = 1;
        s = s.substr(1,s.length()-1);
    }
    else{
        signum = 1;
    }


    for(int i = 0; i < int(s.length()); i++){
        if(!isdigit(s[i])){
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    int i;
    for(i = 0; i < int(s.length()); i++){
        if(s[i] != '0'){
            break;
        }
    }

    if(i == int(s.length())){
        signum = 0;
        return;
    }

    for(int pos = s.length(); pos > i; pos-=power){
        int start = std::max(i, pos-power);
        long num = std::stol(s.substr(start, pos-start));
        digits.insertBefore(num);
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}

// // Optional Destuctor
// // ~BigInteger()
// // ~BigInteger();


// // Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    if(signum > N.signum){
        return 1;
    }
    if(signum < N.signum){
        return -1;
    }

    if(signum == 0 && N.signum == 0){
        return 0;
    }

    if(signum == -1){
        if(digits.length() > N.digits.length()){
            return -1;
        }
        else if(digits.length() < N.digits.length()){
            return 1;
        }
    }
    else if(signum == 1){
        if(digits.length() > N.digits.length()){
            return 1;
        }
        else if(digits.length() < N.digits.length()){
            return -1;
        }
    }

    List listA = digits;
    List listB = N.digits;

    listA.moveBack();
    listB.moveBack();

    while(listA.position() != 0 && listB.position() != 0){
        if(listA.peekPrev() < listB.peekPrev() ){
            return (signum == 1) ? -1 : 1;
        }
        if(listA.peekPrev() > listB.peekPrev() ){
            return (signum == 1) ? 1 : -1;
        }

        listA.movePrev();
        listB.movePrev();
        
    }

    return 0;
}


// // Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(signum != 0){
        signum *= -1;
    }
}


// // BigInteger Arithmetic operations ----------------------------------------

//  ARITHMETIC HELPER FUNCTIONS 

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    for(L.moveFront(); L.position() != L.length(); L.moveNext()){
        L.setAfter(-(L.peekNext()));
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){

    bool normalized = false;

    int sign = 1;

    while(!normalized){
        long carry = 0;

        for(L.moveFront(); L.position() != L.length(); L.moveNext()){
            long val = L.peekNext()+carry;

            if(val >= base){
                carry = val / base;
                L.setAfter(val % base);
            }
            else if(val < 0){
                if(L.peekNext() == L.back()){
                    L.setAfter(val);
                    carry = 0;
                }
                else if(val % base == 0){
                    carry = val / base;
                    L.setAfter(0);
                }
                else{
                  carry = (val / base) - 1;
                  L.setAfter(val + base*(-carry));
                }
            }
            else{
                L.setAfter(val);
                carry = 0;
            }
        }

        if(carry > 0){
            L.insertAfter(carry);
        }

        L.moveBack();
        while(L.position() != 0 && L.peekPrev() == 0){
            L.eraseBefore();
        }
        if(L.length() == 0){
            sign = 0;
            break;
        }

        bool notnum =  false;
        for(L.moveFront(); L.position() != L.length(); L.moveNext()){
            if(L.peekNext() > base || L.peekNext() < 0){
                notnum = true;
                break;
            }
        }
        if(!notnum){
            normalized = true;
        }
        else if(L.back() < 0){
            sign = -1;
            negateList(L);
        }
    }

    return sign;
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){

    if (&A == &B) {  
        B = A;       
    }

    for(B.moveFront(); B.position() != B.length(); B.moveNext()){
        B.setAfter(sgn*(B.peekNext()));
    }

    A.moveFront();
    B.moveFront();

    while(1){
        while(B.position() == B.length() && A.position() != A.length()){
            S.insertBefore(A.peekNext());
            A.moveNext();
        }
        while(B.position() != B.length() && A.position() == A.length()){
            S.insertBefore(B.peekNext());
            B.moveNext();
        }
        if(A.position() == A.length() && B.position() == B.length()){
            break;
        }

        S.insertBefore(A.peekNext() + B.peekNext());
        A.moveNext();
        B.moveNext();
    }
}


// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
    for(L.moveFront(); L.position() != L.length(); L.moveNext()){
        L.setAfter(m*(L.peekNext()));
    }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveFront();
    for(int i = 0; i < p; i++){
        L.insertAfter(0);
    }
}


// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    List result;  
    int resSign;  

    if (signum == 0) {
        return N;  
    }
    if (N.signum == 0) {
        return *this;  
    }

    if(signum == N.signum){
        sumList(result, digits, N.digits, 1);
        normalizeList(result);
        resSign = signum;
    }
    else{
        if(signum == -1){
            sumList(result, N.digits, digits, -1);
        }
        else{
            sumList(result, digits, N.digits, -1);
        }
        resSign = normalizeList(result);
    }

    BigInteger F;
    F.digits = result;
    F.signum = resSign;

    return F;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    List result;  
    int resSign;  

    if (signum == 0) {
        BigInteger temp = N;
        negateList(temp.digits);
        temp.signum = normalizeList(temp.digits);
        return temp;  
    }
    if (N.signum == 0) {
        return *this;  
    }

    if(signum == 1 && N.signum == -1){
        sumList(result, digits, N.digits, 1);
        resSign = normalizeList(result);
    }
    else if(signum == -1 && N.signum == -1){
        sumList(result, N.digits, digits, -1);
        resSign = normalizeList(result);
    }
    else if(signum == 1 && N.signum == 1){
        sumList(result, digits, N.digits, -1);
        resSign = normalizeList(result);
    }
    else{
        sumList(result, digits, N.digits, 1);
        normalizeList(result);
        resSign = -1;
    }

    BigInteger F;
    F.digits = result;
    F.signum = resSign;

    return F;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger R;

    if(signum == 0 || N.signum == 0){
        return R;
    }

    List prod;
    List listN = N.digits;

    if(signum != N.signum){
        R.signum = -1;
    }
    else{
        R.signum = 1;
    }

    int numShift = 0;

    for(listN.moveFront(); listN.position() != listN.length(); listN.moveNext()){
        List res = digits;
        scalarMultList(res, listN.peekNext());
        shiftList(res, numShift);
        List temp;
        sumList(temp, prod, res, 1);
        normalizeList(temp);
        prod = temp;
        numShift++;
    }

    R.digits = prod;

    return R;
}


// // Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){

    std::string s = "";

    if(signum == 0){
        return "0";
    }
    else if(signum == -1){
        s += "-";
    }

    for(digits.moveBack(); digits.position() != 0; digits.movePrev()){
        if(digits.peekPrev() == 0){
            for(int i = 0; i < power; i++){
                s += "0";
            }
        }
        else{
            if(digits.peekPrev() == digits.back()){
                s += std::to_string(digits.peekPrev());
                continue;
            }
            long num = digits.peekPrev();
            while(num < (base/10)){
                s += "0";
                num *= 10;
            }
            s += std::to_string(digits.peekPrev());

        }
    }

    return s;
}


// // Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){

    List listA = A.digits;
    List listB = B.digits;

    if(A.signum != B.signum){
        return false;
    }

    if(listA.length() != listB.length()){
        return false;
    }

    listA.moveBack();
    listB.moveBack();

    while(listA.position() != 0 && listB.position() != 0){
        if(listA.peekPrev() != listB.peekPrev()){
            return false;
        }
        listA.movePrev();
        listB.movePrev();
    }

    return true;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == -1 || A.compare(B) == 0);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    return (A.compare(B) == 1 || A.compare(B) == 0);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}
