# My Little Makefile
FLEX=flex
BISON=bison
CC=clang++
PARAM=-std=c++11 -fcxx-exceptions -O3
LLVM=`llvm-config --cxxflags --ldflags --system-libs --libs core native mcjit`
OUTPUT=myparse

all: main average

main: single_main.cpp
	${CC} -o mymain single_main.cpp ${PARAM} ${LLVM}

average: two_functions.cpp
	${CC} -o myaverage two_functions.cpp ${PARAM} ${LLVM}

clean:
	rm mymain myaverage



