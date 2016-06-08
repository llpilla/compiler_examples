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

    static Module *OurModule;
    static LLVMContext &Context = llvm::getGlobalContext();
    static IRBuilder<> Builder(Context);
    static Type* intType = Type::getInt64Ty(Context);
    static BasicBlock* mainBB;
    static Function* ourMain;

    void codeGenSetup();
    void codeGenEnd(AllocaInst* endvalue);

}

