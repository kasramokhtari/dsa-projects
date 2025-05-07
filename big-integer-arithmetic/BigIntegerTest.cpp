/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{6} 
* BigIntegerTest.cpp
* Test file for the BigInteger ADT
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include <cassert>
#include "BigInteger.h"

using namespace std;

int main(){
    // default constructor test
    BigInteger A;
    assert(A.to_string() == "0");
    assert(A.sign() == 0);

    // long constructor test
    BigInteger B = BigInteger(9374569837489);
    assert(B.to_string() == "9374569837489");
    assert(B.sign() == 1);

    BigInteger C = BigInteger(-937456983748905);
    assert(C.to_string() == "-937456983748905");
    assert(C.sign() == -1);

    // from string constructor test
    BigInteger E("28947529384752893745");
    assert(E.to_string() == "28947529384752893745");

    BigInteger F("-97834752938047582934758273452903485");
    assert(F.to_string() == "-97834752938047582934758273452903485");

    BigInteger G("00000000000076454783995683489576");
    assert(G.to_string() == "76454783995683489576");

    BigInteger H("-000000000000928345729034");
    assert(H.to_string() == "-928345729034");

    try {
        BigInteger I("");
        assert(false); // Should throw
    } catch (std::invalid_argument&) {}

    try {
        BigInteger J("-");
        assert(false); // Should throw
    } catch (std::invalid_argument&) {}


    // copy constructor test
    BigInteger K = BigInteger("3245345693045");
    BigInteger L = K;
    assert(L==K);

    // sign/negate/makeZero test
    BigInteger M = BigInteger("12882");
    assert(M.sign()==1);

    M.negate();
    assert(M.to_string() == "-12882");
    assert(M.sign() == -1);

    M.makeZero();
    assert(M.to_string() == "0");
    assert(M.sign() == 0);

    // compare test
    BigInteger N = BigInteger("34523");
    BigInteger O = BigInteger("-9932434");
    BigInteger P = BigInteger("34523");

    assert(N.compare(O) == 1);
    assert(N.compare(P) == 0);
    assert(O.compare(P) == -1);
    assert(P.compare(P) == 0);

    // add / +operator and sub / -operator and mult / *operator test
    BigInteger W = BigInteger("123");
    BigInteger X = BigInteger("456");
    BigInteger Y = BigInteger("-456");

    assert((W.add(X)).to_string() == "579");  
    assert((W.add(Y)).to_string() == "-333"); 

    BigInteger Q = BigInteger(579);
    BigInteger R = BigInteger(-333);

    assert((W+X) == Q);
    assert((W+Y) == R);

    assert((W.sub(X)).to_string() == "-333");  
    assert((W.sub(Y)).to_string() == "579"); 

    assert((W-X) == R);
    assert((W-Y) == Q);


    BigInteger Aa = BigInteger(0);
    BigInteger Bb = BigInteger(56088);

    assert((W*X) == Bb);
    assert((W*0) == Aa);

    // +=, -=, and *= operator tests
    W += X;
    assert(W == Q);

    BigInteger Cc = BigInteger(912);

    X -= Y;
    assert(X == Cc);

    W *= 0;
    assert(W == Aa);

    // ==, <, <=, >, >= operator tests
    BigInteger Dd = BigInteger(10);
    BigInteger Ee = BigInteger(0);
    BigInteger Ff = BigInteger(-10);
    BigInteger Gg = BigInteger(10);

    assert(Dd == Gg);
    assert(!(Dd == Ee));

    assert(Dd > Ee);
    assert(Ff < Ee);

    assert(Dd >= Ff);
    assert(Ff <= Gg);

    // << operator test
    // prints 0
    cout << W << endl;
    // prints 912
    cout << X << endl;

    return EXIT_SUCCESS;
}