main:main.o DLlist.o core.o assistantfun.o DLlist.h core.h assistantfun.h
	g++ main.o DLlist.o core.o assistantfun.o -g -o main
DLlist.o:DLlist.cpp
	g++ DLlist.cpp -g -c -o DLlist.o
main.o:main.cpp
	g++ main.cpp -g -c -o main.o
core.o:core.cpp
	g++ core.cpp -g -c -o core.o
assistantfun.o:assistantfun.cpp
	g++ assistantfun.cpp -g -c -o assistantfun.o

