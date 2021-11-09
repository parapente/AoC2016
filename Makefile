CXX=clang++
LIBCXX=-lstdc++
OPT=-g -pedantic -Wall -Wfatal-errors
STD=-std=c++14
PROGS=01a.c++ 01b.c++

all: $(PROGS)

01a.c++: 01a.cc
	$(CXX) 01a.cc $(LIBCXX) $(OPT) $(STD) -o 01a.c++

01b.c++: 01b.cc
	$(CXX) 01b.cc $(LIBCXX) $(OPT) $(STD) -o 01b.c++

clean:
	rm -f *.c++

