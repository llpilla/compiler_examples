# My Little Makefile
OBJ=./src/obj
SRC=./src
INC=./include
LEX=./lexical
SYN=./syntax

FLEX=flex
BISON=bison
CC=clang++
PARAM=-std=c++11 -fcxx-exceptions -Wno-deprecated-register 
LLVMLIB=`llvm-config --ldflags --libs core`
LLVMPARAM=`llvm-config --cppflags`
OUTPUT=mycompiler

compiler: $(OBJ)/printer.o $(OBJ)/codegen.o $(OBJ)/parser.o $(OBJ)/scanner.o $(OBJ)/main.o
	${CC} -o $(OUTPUT) $(OBJ)/*.o -I$(INC) ${PARAM} ${LLVMLIB}

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/ast.h
	${CC} -c -o $(OBJ)/main.o $(SRC)/main.cpp -I$(INC) ${PARAM} ${LLVMPARAM}

$(OBJ)/printer.o: $(SRC)/printer.cpp $(INC)/ast.h
	${CC} -c -o $(OBJ)/printer.o $(SRC)/printer.cpp -I$(INC) ${PARAM} ${LLVMPARAM}

$(OBJ)/codegen.o: $(SRC)/codegen.cpp $(INC)/ast.h
	${CC} -c -o $(OBJ)/codegen.o $(SRC)/codegen.cpp -I$(INC) ${PARAM} ${LLVMPARAM}

$(OBJ)/parser.o: $(SYN)/parser.y $(INC)/ast.h
	${BISON} --defines=$(INC)/parser.h --output=$(SRC)/parser.cpp $(SYN)/parser.y
	${CC} -c -o $(OBJ)/parser.o $(SRC)/parser.cpp -I$(INC) ${PARAM} ${LLVMPARAM}

$(OBJ)/scanner.o: $(LEX)/scanner.l $(SYN)/parser.y $(INC)/ast.h
	${FLEX} -o $(SRC)/scanner.cpp $(LEX)/scanner.l
	${CC} -c -o $(OBJ)/scanner.o $(SRC)/scanner.cpp -I$(INC) ${PARAM} ${LLVMPARAM}

clean:
	rm $(OBJ)/* $(SRC)/scanner.cpp $(SRC)/parser.cpp $(INC)/parser.h $(OUTPUT)



