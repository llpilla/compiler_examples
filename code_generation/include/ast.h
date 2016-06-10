/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>
#include "llvm-utils.h" /*LLVM-related code*/

extern void yyerror(const char *s, ...);

namespace AST {

//Binary operations
enum Operation { plus, times, assign };

class Node;

typedef std::vector<Node*> NodeList; //List of ASTs

class Node {
    public:
        virtual ~Node() {}
        virtual void printTree(){}
        virtual void codeGen() = 0;
        llvm::Value* code;
};

class Integer : public Node {
    public:
        int value;
        Integer(int value) : value(value) { }
        void printTree();
        void codeGen();
};

class BinOp : public Node {
    public:
        Operation op;
        Node *left;
        Node *right;
        BinOp(Node *left, Operation op, Node *right) :
            left(left), right(right), op(op) { codeGen(); }
        void printTree();
        void codeGen();
};

class Variable : public Node {
    public:
        std::string id;
        Variable(std::string id) : id(id) { }
        void printTree();
        void codeGen();
};

class Block : public Node {
    public:
        NodeList lines;
        Block() { }
        void printTree();
        void codeGen();
};

}

