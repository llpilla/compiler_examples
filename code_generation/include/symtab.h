/* Symbol Table definition */
#pragma once

#include <map>
#include <string>
#include "llvm-utils.h" /* For variable instructions and code generation */

namespace SymTab {

class Symbol;

enum Type { integer };
enum Kind { variable };

typedef std::map<std::string, Symbol> SymList; //Set of Symbols
typedef std::map<std::string, llvm::AllocaInst*> MemList; //Memory allocations made for variables

class Symbol {
    public:
        Type type;              /*[Return] type of Symbol: integer, double.*/
        Kind kind;              /*Kind of symbol: variable, function, etc.*/
        Symbol(Type type, Kind kind) : type(type), kind(kind) {  }
        Symbol() {type = integer; kind = variable;}
};

class SymbolTable {
    public:
        SymList entryList;
        MemList allocations;
        SymbolTable() {}
        void addSymbol(std::string id, Symbol symbol) {entryList[id] = symbol;}
        bool checkId(std::string id) {return entryList.find(id) != entryList.end();}
        bool checkMem(std::string id) {return allocations.find(id) != allocations.end();}
        bool createVariable(std::string id);
        llvm::AllocaInst* useVariable(std::string id);
};

}
