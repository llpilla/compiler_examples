#include "symtab.h"
#include <iostream>

using namespace SymTab;

bool SymbolTable::createVariable (std::string id){
    if ( checkId(id) ) return false;
    else {
        /* Creates symbol */
        Symbol var(integer, variable);
        /* Adds symbol to symbol table */
        addSymbol(id, var);
        /* Zeroes the variable, so we have some IR code to get without worrying about the first time a variable receives a value */
        allocations[id] = IR::Zero;
        return true;
    }
}

llvm::Value* SymbolTable::useVariable (std::string id){
    if (! checkId(id) ) { //Variable never declared
        std::cout << "Variable not declared: " << id.c_str() << std::endl;
        return NULL;
    } else {
        return allocations[id]; //Gets its value
    }
}

void SymbolTable::updateVariable (std::string id, llvm::Value * value){
    if (! checkId(id) ) { //Variable never declared
        std::cout << "Variable not declared: " << id.c_str() << std::endl;
    } else {
        allocations[id] = value; //Updates its value
    }
}
