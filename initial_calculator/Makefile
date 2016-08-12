# My Little Makefile
FLEX=flex
BISON=bison
CC=clang++
PARAM=-std=c++11 -fcxx-exceptions -Wno-deprecated-register -Wall
OUTPUT=myparse

$(OUTPUT): parser.h scanner.cpp main.cpp
	${CC} -o ${OUTPUT} *.cpp ${PARAM}

scanner.cpp: scanner.l parser.h
	${FLEX} -o scanner.cpp scanner.l 

parser.h: parser.y
	${BISON} --defines=parser.h --output=parser.cpp parser.y

clean:
	rm parser.cpp parser.h scanner.cpp ${OUTPUT}

