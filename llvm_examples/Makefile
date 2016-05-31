# My Little Makefile
FLEX=flex
BISON=bison
CC=clang++
PARAM=-std=c++11 -fcxx-exceptions -Wno-deprecated-register -O3
LLVM=`llvm-config --cppflags --ldflags --libs core jit native`
OUTPUT=myparse

all: main

main: single_main.cpp
	${CC} -o mymain single_main.cpp ${PARAM} ${LLVM}

clean:
	rm mymain



