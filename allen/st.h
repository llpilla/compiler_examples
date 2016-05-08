/*Symbol Table definition*/
#pragma once

#include <map>
#include "ast.h"
#include "support.h"

extern void yyerror(const char* s, ...);

namespace ST {

class Symbol;

enum Kind { variable };

typedef std::map<std::string,Symbol> SymbolList; //Set of Symbols

class Symbol {
    public:
        Types::Type type;     /*[Return] type of Symbol: integer, double.*/
        Kind kind;            /*Kind of symbol: variable, function, etc.*/
        bool initialized;     /*Defines if symbol has been initialized or not.*/
        Symbol(Types::Type type, Kind kind, bool initialized) :
            type(type), kind(kind), initialized(initialized) {  }
        Symbol() {type = Types::unknown; kind = variable; initialized = false;}
};

class SymbolTable {
    public:
        SymbolList entryList;
        SymbolTable() {}
        /*checkId returns true if the variable has been defined and false if it does not exist*/
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        void addSymbol(std::string id, Symbol newsymbol) {entryList[id] = newsymbol;}
        AST::Node* newVariable(std::string id, Types::Type type);
        AST::Node* assignVariable(std::string id);
        AST::Node* useVariable(std::string id);
};

}
