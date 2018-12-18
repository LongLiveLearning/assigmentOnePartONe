# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main TextMain


main:	main.cpp Text.o  
	$(CXX) $(CXXFLAGS) main.cpp Text.o -o main

Text.o: Text.cpp Text.h
	$(CXX) $(CXXFLAGS) -c Text.cpp -o Text.o

TextMain:	TextMain.cpp Text.o TextTester.o 
	$(CXX) $(CXXFLAGS) TextMain.cpp Text.o TextTester.o -o TextMain

TextTester.o: TextTester.cpp TextTester.h
	$(CXX) $(CXXFLAGS) -c TextTester.cpp -o TextTester.o

deepclean: 
	rm -f *~ *.o main TextMain *.exe *.stackdump 

clean:
	-rm -f *~ *.o *.stackdump 