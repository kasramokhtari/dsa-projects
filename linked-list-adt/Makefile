# Kasra Mokhtari 
# kamokhta
# 2024 Fall CSE101 PA{1} 
# Makefile
# Makefile to create executables 


#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make clean             removes all binaries
# make ListText		     makes ListTest
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

# ListClient: ListClient.o List.o
# 	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

# ListClient.o : ListClient.c List.h
# 	gcc -std=c17 -Wall -c ListClient.c

 ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

 ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListTest Lex.o ListTest.o List.o

# checkClient : 
# 	valgrind --leak-check=full ListClient

# checkTest:
# 	valgrind --leak-check=full ./ListTest

# checkLex :
# 	valgrind --leak-check=full ./Lex in3 blah3
