#include "ast.h"
#include "symtab.h"
#include "llvm-utils.h"

extern SymTab::SymbolTable symbolTable;

using namespace AST;
using namespace llvm;

/* Code generation methods */

/* Constant: LLVM keeps constants 'uniqued' together */
void Integer::codeGen(){
    if(code == NULL) //generates code if we have none
        code = ConstantInt::get(IR::Context, APInt(64,value));
    code->dump();
}

/* Binary operation: we add to the basic block an instruction using
 * the code generated for the left and right hand sides */
void BinOp::codeGen(){
    if (code == NULL) { //generates code if we have none
        if (op == assign){
            std::cout << "Generating assignment" << std::endl;
            /*Assignments are a different beast.
             * They require storing a code on a variable on the left side*/
            Variable* lvar = dynamic_cast<Variable *>(left);
            auto tmp = symbolTable.useVariable(lvar->id); /*gets left side*/
            std::cout << "printing temp" << std::endl;
            tmp->dump();
            right->codeGen(); /*gets right side*/
            auto tmpStore = IR::Builder.CreateStore(right->code, tmp); /*stores the code*/
            tmpStore->dump();
            code = right->code;
        }
        else {
            /*Usual binary operations: get both sides and generate an instruction*/
            left->codeGen();
            right->codeGen();
            switch(op){
                case plus:
                    code = IR::Builder.CreateAdd(left->code, right->code, "addtmp");
                    break;
                case times:
                    code = IR::Builder.CreateMul(left->code, right->code, "multmp");
                    break;
                default:
                    code = NULL;
                    break;
            }
        }
    }
    code->dump();
}

/* Variable: */
void Variable::codeGen(){
    if (code == NULL){ //generates code if we have none
        /*First we get the allocation from the variable declaration*/
        auto tmp = symbolTable.useVariable(id);
        /*Then we load from there*/
        code = IR::Builder.CreateLoad(tmp, "tmp");
    }
    code->dump();
}


/* Block: we generate the code for all lines of high level code */
void Block::codeGen(){
    for (Node* line: lines) {
        if (line->code != NULL) line->code->dump();
    }
}
