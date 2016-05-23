/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>

/*LLVM-related code*/
#include "llvm/Analysis/Verifier.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

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
        virtual llvm::Value *Codegen() = 0;
};

class Integer : public Node {
    public:
        int value;
        Integer(int value) : value(value) {  }
        void printTree();
        llvm::Value *Codegen();
};

class BinOp : public Node {
    public:
        Operation op;
        Node *left;
        Node *right;
        BinOp(Node *left, Operation op, Node *right) :
            left(left), right(right), op(op) { }
        void printTree();
        llvm::Value *Codegen();
};

class Block : public Node {
    public:
        NodeList lines;
        Block() { }
        void printTree();
        llvm::Value *Codegen();
};

}

