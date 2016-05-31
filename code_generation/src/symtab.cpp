#include "symtab.h"
#include <iostream>

using namespace SymTab;

bool SymbolTable::createVariable (std::string id){
    if ( checkId(id) ) return false;
    else {
        /* Creates memory allocation */
        llvm::AllocaInst* inst = Builder.CreateAlloca(
                llvm::Type::getInt64Ty(llvm::getGlobalContext()),
                0,
                id.c_str());
        if(inst == NULL) std::cout << "Panic" << std::endl;
        /* Creates symbol */
        Symbol var(integer, variable, inst);
        /* Adds symbol to symbol table */
        addSymbol(id, var);
        return true;
    }
}

llvm::AllocaInst* SymbolTable::useVariable (std::string id){
    if ( checkId(id) ) return NULL;
    else return entryList[id].inst;
}
