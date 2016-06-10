#include "ast.h"
#include "symtab.h"
#include "llvm-utils.h"

extern SymTab::SymbolTable symbolTable;

using namespace AST;
using namespace llvm;

/* Code generation methods */

/* Constant: LLVM keeps constants 'uniqued' together */
void Integer::codeGen(){
    if(code == NULL) //Generates code if we have none. We only do it when we have an expression or assignment
        code = ConstantInt::get(IR::Context, APInt(64,value));
    //code->dump(); //if curious about the generated IR
}

/* Binary operation: we add to the basic block an instruction using
 * the code generated for the left and right hand sides */
void BinOp::codeGen(){
    if (code == NULL) { //generates code if we have none
        if (op == assign){
            /*Assignments use the name of the variable and update the symbol table.*/
            Variable* lvar = dynamic_cast<Variable *>(left);
            right->codeGen(); /*gets right side*/
            code = IR::Builder.CreateAdd(right->code, IR::Zero, lvar->id.c_str()); /*'copies' the value to the variable*/
            symbolTable.updateVariable(lvar->id, code); /*Gives the new code and value to the variable in the symbol table.*/
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
                    code = NULL; //Not the greatest error capture, but okay for the example
                    break;
            }
        }
    }
    //code->dump(); //if curious about the generated IR
}

/* Variable: variables have their latest values in the symbol table, so we can get them from there */
void Variable::codeGen(){
    if (code == NULL){ //generates code if we have none
        code = symbolTable.useVariable(id);
    }
    //code->dump(); //if curious about the generated IR
}


/* Block: blocks are only used at the highest of levels in our code, so we have no code to generate */
void Block::codeGen(){
    //for (Node* line: lines) {
    //    if (line->code != NULL) line->code->dump();
    //}
}
