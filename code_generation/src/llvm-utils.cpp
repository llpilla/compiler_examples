#include "llvm-utils.h"

using namespace llvm;
using namespace IR;

void IR::codeGenSetup(){
    //Starts module
    OurModule = new Module("Our first intermediary code compiler", Context);
    //Set up 'main'
    //FunctionType* typeOfMain = FunctionType::get(Type::getVoidTy(Context),false);
    FunctionType* typeOfMain = FunctionType::get(intType,false);
    ourMain = Function::Create(typeOfMain,Function::ExternalLinkage, "compiler", OurModule);
    //Set up the initial basic block
    mainBB = BasicBlock::Create(Context, "start", ourMain);
    Builder.SetInsertPoint(mainBB);

}
//void codeGenEnd(Value* value){
void IR::codeGenEnd(AllocaInst* endvalue){
    auto value = Builder.CreateLoad(endvalue, "retval");
    Builder.CreateRet(value);
    //Builder.CreateRetVoid();
    verifyFunction(*ourMain);
    OurModule->dump();
}

