#include "ast.h"

using namespace AST;

//extern ST::SymbolTable symtab;

/* Coerces a node if needed */
Node* Node::coerce(Node* otherNode){
    if (Types::coercionNeeded(this->type, otherNode->type))
        return new AST::Coercion(this);
    else return this;
}

/* Print methods */
void BinOp::printTree(){
    switch(op){
        case Ops::assign:
            /*Atribuicao de valor para variavel TIPO FEMININO nome:*/
            std::cout << "Atribuicao de valor para ";
            left->printTree();
            std::cout << ": ";
            right->printTree();
            break;
        default:
            std::cout << "(";
            left->printTree();
            std::cout << " (" << Ops::opName[op] << " ";
            if ( Ops::masculineOp[op] ) std::cout << Types::masTypes[this->type];
            else std::cout << Types::femTypes[this->type];
            std::cout << ") ";
            right->printTree();
            std::cout << ")";
            break;
    }
}

void UnOp::printTree(){
    std::cout << "(";
    switch(op){
        case Ops::par:
            std::cout << "(abre parenteses) ";
            next->printTree();
            std::cout << " (fecha parenteses)";
            break;
        default:
            std::cout << "(" << Ops::opName[op] << " ";
            if ( Ops::masculineOp[op] ) std::cout << Types::masTypes[this->type];
            else std::cout << Types::femTypes[this->type];
            std::cout << ") ";
            next->printTree();
            break;
    }
    std::cout << ")";
}

void Block::printTree(){
    for (Node* line: lines) {
        line->printTree();
        std::cout << std::endl;
    }
}

void Variable::printTree(){
    /*variavel TIPO FEMININO nome*/
    std::cout << "variavel " << Types::femTypes[type] << " " << id;
}

void VarDeclaration::printTree(){
/* Declaracao de variavel TIPO FEMININO: nome{, nome}* */
    std::cout << "Declaracao de variavel " << Types::femTypes[type] <<": ";
    for (auto var = variables.begin(); var != variables.end(); var++) {
        std::cout << dynamic_cast<Variable *>(*var)->id;
        if(next(var) != variables.end()) std::cout << ", ";
    }
}

void Value::printTree(){
    /*valor TIPO MASCULINO {num|TRUE|FALSE|real}*/
    std::cout << "valor " << Types::masTypes[type] << " " << value;
}

void Coercion::printTree(){
    /*para real*/
    next->printTree();
    std::cout << " para real";
}
