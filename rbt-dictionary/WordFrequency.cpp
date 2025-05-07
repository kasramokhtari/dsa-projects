/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{8} 
* WordFrequency.cpp
* One of the two top-level client programs 
***/ 

#include<fstream>
#include <cstdio>
#include <cctype> 
#include <algorithm>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*%()-_=+0123456789";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 

   Dictionary D;

   std::string word;
   while( getline(in, line) )  {
      len = line.length();

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){ 
         std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ 
            return std::tolower(c); 
         });
         if(D.contains(token)){
            D.getValue(token)++;
         }
         else{
            D.setValue(token, 1);
         }
         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }

   out << D.to_string();

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
