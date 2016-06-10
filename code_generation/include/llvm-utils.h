#pragma once

/*LLVM-related code*/
#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

/* LLVM support objects */
using namespace llvm;

namespace IR {

    static Module *OurModule; //LLVM Module
    static LLVMContext &Context = llvm::getGlobalContext(); //LLVM Context
    static IRBuilder<> Builder(Context); //LLVM IR Builder
    static Type* intType = Type::getInt64Ty(Context); //Type of integers = 64 bit integers
    static BasicBlock* mainBB; //LLVM Basic Block where all code ends up being written
    static Function* ourMain; //Functions that represents all the code that we set
    static Constant* Zero = ConstantInt::get(Context, APInt(64, 0)); //Constant zero in IR

    void codeGenSetup(); //Sets up the whole LLVM environment for code generation
    void codeGenEnd(Value* endvalue); //Finishes the IR generation and prints the code

}

