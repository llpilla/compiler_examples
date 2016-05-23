#include "ast.h"

/* LLVM support objects */
static llvm::Module *TheModule;
static llvm::IRBuilder<> Builder(llvm::getGlobalContext());
static std::map<std::string, llvm::Value*> NamedValues;

using namespace AST;

/* Code generation methods */

/* Constant: LLVM keeps constants 'uniqued' together */
llvm::Value* Integer::Codegen(){
    return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(64,value));
}

/* Binary operation: we add to the basic block an instruction using
 * the code generated for the left and right hand sides */
llvm::Value* BinOp::Codegen(){
    llvm::Value* lvalue = left->Codegen();
    llvm::Value* rvalue = right->Codegen();
    switch(op){
        case plus: return Builder.CreateAdd(lvalue, rvalue, "addtmp");
        case times: return Builder.CreateMul(lvalue, rvalue, "multmp");
        default: return Builder.CreateAdd(lvalue, rvalue, "addtmp");
    }
}

/* Block: we generate the code for all lines of high level code */
llvm::Value* Block::Codegen(){
    llvm::Value* value;
    for (Node* line: lines) {
        value = line->Codegen();
    }
    return value;
}
