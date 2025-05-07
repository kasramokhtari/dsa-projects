/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{6} 
* Arithmetic.cpp
* Main file program
***/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include <cstdio>
#include"BigInteger.h"


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

  std::string val1;
  std::string blank;
  std::string val2;

  std::getline(inputFile, val1);
  std::getline(inputFile, blank);
  std::getline(inputFile, val2);

  BigInteger A = BigInteger(val1);
  BigInteger B = BigInteger(val2);

  outputFile << A << "\n\n";
  
  outputFile << B << "\n\n";

  BigInteger C = A+B;
  outputFile << C << "\n\n";
  
  BigInteger D = A-B;
  outputFile << D << "\n\n";
  
  BigInteger E = A-A;
  outputFile << E << "\n\n";

  BigInteger three = BigInteger("3");
  BigInteger two = BigInteger("2");
  BigInteger F = (three*A)-(two*B);
  outputFile << F << "\n\n";

  BigInteger G = A*B;
  outputFile << G << "\n\n";

  BigInteger H = A*A;
  outputFile << H << "\n\n";

  BigInteger I = B*B;
  outputFile << I << "\n\n";

  BigInteger nine = BigInteger("9");
  BigInteger sixteen = BigInteger("16");
  BigInteger J = (H*H*nine) + (I*I*B*sixteen);
  outputFile << J << "\n";

  inputFile.close();
  outputFile.close();

  return 0;
}
