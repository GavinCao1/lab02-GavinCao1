CXX=g++
CXX_FLAGS=-std=c++ -Wall

all:  intbst.o testbst.o
     $(CXX_FLAGS) intbst.o testbst.o -o all

intbst.o: intbst.cpp  
  $(CXX) $(CXX_FLAGS) intbst.cpp -c

testbst.o: testbst.cpp 
  $(CXX) $(CXX_FLAGS) testbst.cpp -c
