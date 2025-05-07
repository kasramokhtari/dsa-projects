Kasra Mokhtari 
kamokhta
2024 Fall CSE101 PA{2} 
README.md
Description of the files used in PA2, including the Graph ADT files, List ADT files, and FindPath.c program.

List.h - The List.h file is used in this project as a file to put the declarations of the variables, functions, and types of the List ADT. 
It is also used as a way to specify all the functions and structs from the List.c file that the user can use.

List.c - This is the file where the code implementation of these functions and types are made.

Graph.h - This is the file where the declarations of the varibales, functions, and types of the Graph ADT. It also specifies the functions that 
is available to the client when they use the Graph ADT.

Graph.c - This is the file where the code implementaiton of these functions and types are made to make the Graph ADT work as intended.

GraphTest.c - This is a file used to test the functions that are involved in the Graph ADT. It checked each function for different types of cases of use to ensure that it works as intended by the instructions.

FindPath.c - This was the file that used the Graph ADT to take in an input and output file and use and find the distance and shortest path between the two vertices
that the file inputted.

Makefile - This file is used to make the FindPath.c and GraphTest executable to run the the program to make sure it works as intended. It also has functionalities
like clean to clean the executable files and checkFind to check for memory leaks in the FindPath.c file. 

README.md - This is the file this text is currently in, used to explain the functionality of each program in this project.