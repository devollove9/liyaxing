#
#hw4
#
hw4: heap-shell.o
	g++  heap-shell.o -o hw4

heap-shell.o: heap-shell.cpp
	g++ -Wall -c heap-shell.cpp 

clean:
