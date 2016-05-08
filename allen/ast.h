/*Abstract Syntax Tree definition*/
#pragma once

#include <iostream>
#include <vector>
#include "support.h"

extern void yyerror(const char *s, ...);

namespace AST {

//Binary operations
enum Operation { plus, times, assign };

class Node;

typedef std::vector<Node*> NodeList; //List of ASTs

class Node {
    public:
        Types::Type type = Types::unknown;
        virtual ~Node() {  }
        virtual void printTree() {  }
        Node() {  }
        Node(Types::Type type) : type(type) {  }
        Node* coerce(Node* otherNode);
};

class BinOp : public Node {
    public:
        Ops::Operation op;
        Node *left;
        Node *right;
        BinOp(Node *left, Ops::Operation op, Node *right) :
            left(left), right(right), op(op) { type = Types::binType(left->type, right->type, op); }
        void printTree();
};

class UnOp : public Node {
    public:
        Ops::Operation op;
        Node *next;
        UnOp(Node *next, Ops::Operation op) :
            next(next), op(op) { type = Types::unType(next->type,op); }
        void printTree();
};

class Block : public Node {
    public:
        NodeList lines;
        Block() { }
        void printTree();
};

class VarDeclaration : public Node {
    public:
        NodeList variables;
        VarDeclaration(Types::Type type) : Node(type) {  }
        void printTree();
};

class Variable : public Node {
    public:
        std::string id;
        Variable(std::string id, Types::Type type) : id(id),  Node(type) {  }
        void printTree();
};

class Value : public Node {
    public:
        std::string value;
        Value(std::string value, Types::Type type) : value(value), Node(type) {  }
        void printTree();
};

class Coercion : public Node {
    public:
        Node *next;
        Coercion(Node *next) : next(next), Node(Types::real) {  }
        void printTree();
};

}

