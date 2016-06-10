#include "ast.h"

using namespace AST;


/* Print methods */
void Integer::printTree(){
    std::cout << value;
    return;
}

void BinOp::printTree(){
    left->printTree();
    switch(op){
        case plus: std::cout << " + "; break;
        case times: std::cout << " * "; break;
        default:
        case assign: std::cout << " = "; break;
    }
    right->printTree();
    return;
}

void Variable::printTree(){
    std::cout << id;
}

void Block::printTree(){
    for (Node* line: lines) {
        line->printTree();
        std::cout << std::endl;
    }
}

