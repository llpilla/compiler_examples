#include "st.h"

using namespace ST;

extern SymbolTable symtab;

AST::Node* SymbolTable::newVariable(std::string id, Types::Type type){
    if ( checkId(id) ) yyerror("semantico: redefinicao da variavel %s.", id.c_str());
    else {
       Symbol entry(type, variable, false);
       addSymbol(id,entry); //Adds variable to symbol table
    }
    return new AST::Variable(id, type); //Creates variable node anyway
}

AST::Node* SymbolTable::assignVariable(std::string id){
    Types::Type varType;
    if ( ! checkId(id) ) {
        yyerror("semantico: variavel %s sem declaracao.", id.c_str());
        varType = Types::unknown;
    } else {
        varType = entryList[id].type;
        entryList[id].initialized = true;
    }
    return new AST::Variable(id, varType); //Creates variable node anyway
}

AST::Node* SymbolTable::useVariable(std::string id){
    Types::Type varType;
    if ( ! checkId(id) ) {
        yyerror("semantico: variavel %s sem declaracao.", id.c_str());
        varType = Types::unknown;
    } else {
        varType = entryList[id].type;
        if ( ! entryList[id].initialized ) yyerror("semantico: variavel %s nao inicializada.", id.c_str());
    }
    return new AST::Variable(id, varType); //Creates variable node anyway
}

