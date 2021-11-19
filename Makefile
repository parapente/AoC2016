CXX=clang++
LIBCXX=-lstdc++
OPT=-g -pedantic -Wall -Wfatal-errors
STD=-std=c++17
PROGS=01a.c++ 01b.c++ 02a.c++ 02b.c++ 03a.c++ 03b.c++ \
	  04a.c++ 04b.c++ 05a.c++ 05b.c++ 06a.c++ 06b.c++ \
	  07a.c++ 07b.c++ 08.c++

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

03b.c++: 03b.cc
	$(CXX) 03b.cc $(LIBCXX) $(OPT) $(STD) -o 03b.c++

04a.c++: 04a.cc
	$(CXX) 04a.cc $(LIBCXX) $(OPT) $(STD) -o 04a.c++

04b.c++: 04b.cc
	$(CXX) 04b.cc $(LIBCXX) $(OPT) $(STD) -o 04b.c++

05a.c++: 05a.cc
	$(CXX) 05a.cc $(LIBCXX) $(OPT) $(STD) -lcrypto -o 05a.c++

05b.c++: 05b.cc
	$(CXX) 05b.cc $(LIBCXX) $(OPT) $(STD) -lcrypto -o 05b.c++

06a.c++: 06a.cc
	$(CXX) 06a.cc $(LIBCXX) $(OPT) $(STD) -o 06a.c++

06b.c++: 06b.cc
	$(CXX) 06b.cc $(LIBCXX) $(OPT) $(STD) -o 06b.c++

07a.c++: 07a.cc
	$(CXX) 07a.cc $(LIBCXX) $(OPT) $(STD) -o 07a.c++

07b.c++: 07b.cc
	$(CXX) 07b.cc $(LIBCXX) $(OPT) $(STD) -o 07b.c++

08.c++: 08.cc
	$(CXX) 08.cc $(LIBCXX) $(OPT) $(STD) -o 08.c++

clean:
	rm -f *.c++

