CXX=clang++
LIBCXX=-lstdc++
OPT=-g -pedantic -Wall -Wfatal-errors
STD=-std=c++17
PROGS=01a.c++ 01b.c++ 02a.c++ 02b.c++ 03a.c++ \
	  04a.c++ 04b.c++

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

04a.c++: 04a.cc
	$(CXX) 04a.cc $(LIBCXX) $(OPT) $(STD) -o 04a.c++

04b.c++: 04b.cc
	$(CXX) 04b.cc $(LIBCXX) $(OPT) $(STD) -o 04b.c++

clean:
	rm -f *.c++

