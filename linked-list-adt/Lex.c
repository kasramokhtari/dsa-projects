/***
* Kasra Mokhtari 
* kamokhta
* 2024 Fall CSE101 PA{1} 
* Lex.c
* Main Program file
***/ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

int main(int argc, char* argv[]){

    FILE *in, *out;

    if( argc != 3 ){
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
      if( in==NULL ){
      fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
      fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }

    char buffer[1024];
    int line_count = 0;
    char** lines;

    while(fgets(buffer, sizeof(buffer), in)){
        line_count++;
    }

    // reseting the file pointer
    rewind(in);

    lines = malloc(line_count * sizeof(char *));
    
    int i = 0;

    while(fgets(buffer, sizeof(buffer), in)){

        // after getting the first line, we are making it null terminated, like making it into a string
        buffer[strcspn(buffer, "\n")] = '\0';

        // we get the size of the line using strlen since it is now null terminated
        int length = strlen(buffer) + 1;

        // we allocate memory for the string and store its pointer at the current position
        lines[i] = malloc(length * sizeof(char));

        // we take the newly allocated memory in this position and put the string in it.
        strcpy(lines[i], buffer);

        // moving to the next index
        i++;
    }
    

    List L = newList();

    if(lines != NULL){
        append(L, 0);
    }


    for(int i = 1; i < line_count; i++){
        bool inserted = false;
        moveFront(L);

        while(index(L) != -1){
            if(strcmp(lines[i], lines[get(L)]) <= 0){
                insertBefore(L, i);
                inserted = true;
                break;
            }
            moveNext(L);
        }
        if(!inserted){
            moveBack(L);
            insertAfter(L, i);
        }
    }


    moveFront(L);
    for(int i = 0; i < length(L); i++){
        fprintf(out, "%s", lines[get(L)]);
        moveNext(L);
        if(i != length(L)-1){
            fprintf(out, "\n");
        }
    }
    
    freeList(&L);
    for(int i = 0; i < line_count; i++){
        free(lines[i]);
    }
    free(lines);
    

    fclose(in);
    fclose(out);
    return(0);
}