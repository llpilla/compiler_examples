#include "ast.h"
#include "symtab.h"
#include "llvm-utils.h"

extern SymTab::SymbolTable symbolTable;

using namespace AST;

/* Code generation methods */

/* Constant: LLVM keeps constants 'uniqued' together */
llvm::Value* Integer::Codegen(){
    return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(64,value));
}

/* Binary operation: we add to the basic block an instruction using
 * the code generated for the left and right hand sides */
llvm::Value* BinOp::Codegen(){
    if (op == assign){
        /*Assignments are a different beast.
         * They require storing a value on a variable on the left side*/
        Variable* lvar = dynamic_cast<Variable *>(left);
        llvm::AllocaInst* inst = symbolTable.useVariable(lvar->id); /*gets left side*/
        llvm::Value* rvalue = right->Codegen(); /*gets right side*/
        return Builder.CreateStore(rvalue,inst); /*stores the value*/
    }

    /*Usual binary operations: get both sides and generate an instruction*/
    llvm::Value* lvalue = left->Codegen();
    llvm::Value* rvalue = right->Codegen();
    switch(op){
        case plus: return Builder.CreateAdd(lvalue, rvalue, "addtmp");
        case times: return Builder.CreateMul(lvalue, rvalue, "multmp");
        default: return Builder.CreateAdd(lvalue, rvalue, "addtmp");
    }
}

/* Variable: */
llvm::Value* Variable::Codegen(){
    /*First we get the allocation from the variable declaration*/
    std::cout << "Checking " << id << std::endl;
    llvm::Value* value = symbolTable.useVariable(id);
    std::cout << "Checking " << id << std::endl;
    /*Then we load from there*/
    if (value == 0) std::cout << "Panic";
    return Builder.CreateLoad(value, id.c_str());
}

/* Block: we generate the code for all lines of high level code */
llvm::Value* Block::Codegen(){

    llvm::Value* value;
    for (Node* line: lines) {
        std::cout << "Generating block" << std::endl;
        value = line->Codegen();
        value->dump();
    }
    return value;
}
