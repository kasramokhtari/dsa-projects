Kasra Mokhtari
kamokhta
2024 Fall CSE101 PA{3}
README.md
Description of the files used in PA3, including the Graph ADT files, List ADT files, and the FindComponents file


List.h - The List.h file is used in this project as a file to put the declarations of the variables, functions, and types of the List ADT.
It is also used as a way to specify all the functions and structs from the List.c file that the user can use.


List.c - This is the file where the code implementation of these functions and types are made.


Graph.h - This is the file where the declarations of the variables, functions, and types of the Graph ADT. It also specifies the functions that
is available to the client when they use the Graph ADT.


Graph.c - This is the file where the code implementation of these functions and types are made to make the Graph ADT work as intended.

Implementation decisions in Graph.c:
   - In my implementation of the Graph ADT for PA3, I opted to copy the Graph ADT from PA2 and use that as an outline for my PA3 ADT.
     I made this decision because the PA2 ADT had many of the same structures, constants, and functions as the PA3 ADT, with a couple of new arrays
     added to the GraphObj struct like the discoverTime and finishTime arrays and some variables removed like source and distance, as well as the new functions
     transpose() and copyGraph().
   - In my implementation of the visit() function in the Graph ADT, I opted to use the second option in deciding how to work with the time variable
     in the visit function. As mentioned in the instructions for the second option, I let time be a local int variable in DFS, and had the visit function
     take an int pointer, which is where the address of the time variable would be passed.


GraphTest.c - This is a file used to test the functions that are involved in the Graph ADT. It checked each function for different types of cases of use to ensure that it works as intended by the instructions.


FindComponents.c - This was the file that used the Graph ADT to take in an input and output file and use and find the strongly connected components of the graph that was inputted.


Makefile - This file is used to make the FindComponents.o and GraphTest.o executables to run the program to make sure it works as intended. It also has functionalities
like clean to remove the executable files and checkFind/checkTest to check for memory leaks in the FindComponents.c and GraphTest.c files.


README.md - This is the file this text is currently in, used to explain the functionality of each program in this project.
