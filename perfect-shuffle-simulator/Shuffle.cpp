/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{5} 
* Shuffle.cpp
* Main file program
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


void shuffle(List &D){
    int length = D.length();
    int mid = length / 2;

    List frontHalf;
    List backHalf;
    List N;

    D.moveFront();
    for(int i = 0; i < mid; i++){
        frontHalf.insertAfter(D.moveNext());
        frontHalf.moveNext();
    }

    for(int i = mid; i < length; i++){
        backHalf.insertAfter(D.moveNext());
        backHalf.moveNext();
    }

    frontHalf.moveFront();
    backHalf.moveFront();
    for(int i = 1; i <= length; i++, N.moveNext()){
        if(i % 2 == 1){
            N.insertAfter(backHalf.moveNext());
        }
        else{
            N.insertAfter(frontHalf.moveNext());
        }
    }
    D = N;
    
}

int main(int argc, char* argv[]){


    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <positive integer>\n";
        exit(1);
    }

    int maxDeck = atoi(argv[1]);

    if(maxDeck <= 0){
        std::cerr << "Error: Argument for max deck size must be a positive integer.\n";
    }

    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;

    for(int i = 1; i <= maxDeck; i++){
        List deck;
        for(int j = 0; j < i; j++){
            deck.insertAfter(j);
            deck.moveNext();
        }

        int count;
        if(i != 1){
            List temp = deck;
            shuffle(deck);
            count = 1;
            while(!(deck == temp)){
                shuffle(deck);
                count++;
            }
        }
        else{
            count = 1;
        }

                                 
        std::cout << " " << i;
        if(i < 10){
            std::cout << "               " << count << std::endl;
        }
        else if(i < 100){
            std::cout << "              " << count << std::endl;
        }
        else{
            std::cout << "             " << count << std::endl;
        }
    }

    return 0;

}