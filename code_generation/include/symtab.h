/* Symbol Table definition */
#pragma once

#include <map>
#include <string>
#include "llvm-utils.h" /* For variable instructions and code generation */

namespace SymTab {

class Symbol;

enum Type { integer };
enum Kind { variable };

typedef std::map<std::string,Symbol> SymList; //Set of Symbols

class Symbol {
    public:
        Type type;              /*[Return] type of Symbol: integer, double.*/
        Kind kind;              /*Kind of symbol: variable, function, etc.*/
        llvm::AllocaInst* inst; /*Allocation instruction for code generation.*/
        Symbol(Type type, Kind kind, llvm::AllocaInst* inst) : type(type), kind(kind), inst(inst) {  }
        Symbol() {type = integer; kind = variable; inst = NULL;}
};

class SymbolTable {
    public:
        SymList entryList;
        SymbolTable() {}
        void addSymbol(std::string id, Symbol symbol) {entryList[id] = symbol;}
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        bool createVariable(std::string id);
        llvm::AllocaInst* useVariable(std::string id);
};

}
