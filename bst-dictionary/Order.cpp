/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{7} 
* Order.cpp
* Main file program 
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include <cstdio>
#include "Dictionary.h"

int main(int argc, char* argv[]){

    if( argc != 3 ){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if(!inputFile){
        std::cerr << "Unable to open file " << argv[1] << "for reading" << std::endl;
        return 1;
    }

    std::ofstream outputFile(argv[2]);
    if(!outputFile){
        std::cerr << "Unable to open file " << argv[2] << "for writing" << std::endl;
        return 1;
    }

    Dictionary D;

    std::string line;
    int line_num = 1;
    while(std::getline(inputFile, line)){
        D.setValue(line, line_num);
        line_num++;
    }

    outputFile << D.to_string() << std::endl;

    outputFile << D.pre_string();

    inputFile.close();
    outputFile.close();

    return 0;
}