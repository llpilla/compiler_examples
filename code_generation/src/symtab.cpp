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

        /* Creates the memory allocation for the variable */
        llvm::AllocaInst* inst = IR::Builder.CreateAlloca(IR::intType, 0, id.c_str());
        allocations[id] = inst;
        return true;
    }
}

llvm::AllocaInst* SymbolTable::useVariable (std::string id){
    if (! checkId(id) ) { //Variable never used
        std::cout << "Variable not declared: " << id.c_str() << std::endl;
        return NULL;
    } else {
        return allocations[id];
    }
}
