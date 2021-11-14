CXX=clang++
LIBCXX=-lstdc++
OPT=-g -pedantic -Wall -Wfatal-errors
STD=-std=c++14
PROGS=01a.c++ 01b.c++ 02a.c++ 02b.c++ 03a.c++

all: $(PROGS)

01a.c++: 01a.cc
	$(CXX) 01a.cc $(LIBCXX) $(OPT) $(STD) -o 01a.c++

01b.c++: 01b.cc
	$(CXX) 01b.cc $(LIBCXX) $(OPT) $(STD) -o 01b.c++

02a.c++: 02a.cc
	$(CXX) 02a.cc $(LIBCXX) $(OPT) $(STD) -o 02a.c++

02b.c++: 02b.cc
	$(CXX) 02b.cc $(LIBCXX) $(OPT) $(STD) -o 02b.c++

03a.c++: 03a.cc
	$(CXX) 03a.cc $(LIBCXX) $(OPT) $(STD) -o 03a.c++

clean:
	rm -f *.c++

