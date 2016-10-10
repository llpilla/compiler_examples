#include "llvm/IR/DerivedTypes.h"   //for types
#include "llvm/IR/IRBuilder.h"      //for Builder
#include "llvm/IR/LLVMContext.h"    //for Context
#include "llvm/IR/Module.h"         //for Module
#include "llvm/IR/Verifier.h"       //for Verify function
#include "llvm/ExecutionEngine/ExecutionEngine.h" //for JIT
#include "llvm/ExecutionEngine/MCJIT.h"           //for JIT

#include <iostream>
#include <vector>

int main() {
    llvm::LLVMContext &Context = llvm::getGlobalContext();
    llvm::Module *OurModule;
    llvm::IRBuilder<> Builder(Context);

    OurModule = new llvm::Module("Our first intermediary code", Context);

    /***** Main: a function that gets no parameters and returns an integer *****/
    /* http://llvm.org/docs/doxygen/html/classllvm_1_1FunctionType.html
     * static FunctionType * get (Type *Result, bool isVarArg)
     * FunctionType::get - Create a FunctionType taking no parameters. */
    llvm::Type* intType = llvm::Type::getInt64Ty(Context);
    llvm::FunctionType* typeOfMain = llvm::FunctionType::get(intType,false);

    /* http://llvm.org/docs/doxygen/html/classllvm_1_1Function.html
     * static Function * Create (FunctionType *Ty, LinkageTypes Linkage, const Twine &N="", Module *M=nullptr) */
    llvm::Function* ourMain = llvm::Function::Create(typeOfMain,llvm::Function::ExternalLinkage, "main", OurModule);

    /* http://llvm.org/docs/doxygen/html/classllvm_1_1BasicBlock.html
     * static BasicBlock * Create (LLVMContext &Context, const Twine &Name="", Function *Parent=nullptr, BasicBlock *InsertBefore=nullptr)
     * Creates a new BasicBlock.
     */
    llvm::BasicBlock *mainBB = llvm::BasicBlock::Create(Context, "entry", ourMain);

    /* http://llvm.org/docs/doxygen/html/classllvm_1_1IRBuilderBase.html
     * void SetInsertPoint (BasicBlock *TheBB)
     * This specifies that created instructions should be appended to the end of the specified block.
     */
    Builder.SetInsertPoint(mainBB);

    /*** Constants are all unified ***/
    /* http://llvm.org/docs/doxygen/html/classllvm_1_1ConstantInt.html
     * static ConstantInt *	get (LLVMContext &Context, const APInt &V)
     * Return a ConstantInt with the specified value and an implied Type.
     * APInt = Arbitrary Precision Integer */
    llvm::ConstantInt* Ten = llvm::ConstantInt::get(Context, llvm::APInt(64,10));
    auto One = llvm::ConstantInt::get(Context, llvm::APInt(64, 1));
    auto Zero = llvm::ConstantInt::get(Context, llvm::APInt(64, 0));

    /* static ConstantInt *	get (IntegerType *Ty, uint64_t V, bool isSigned=false)
     * Return a ConstantInt with the specified integer value for the specified type. */
    llvm::Constant* NegativeOne = llvm::ConstantInt::get( intType, -1, true);

    /*** Lets work with another function named average!! ***/
    /* Average takes two integers as input and returns one */
    std::vector<llvm::Type*> AverageParameters(2, intType);
    llvm::FunctionType* typeOfAverage = llvm::FunctionType::get(intType, AverageParameters, false);

    /* We name it 'average' */
    llvm::Function* ourAverage = llvm::Function::Create(typeOfAverage,llvm::Function::ExternalLinkage, "average", OurModule);

    /* Now we name its parameters 'a' and 'b' */
    llvm::Function::arg_iterator params = ourAverage->arg_begin();
    params->setName("a");
    ++params;
    params->setName("b");

    /* Our function will have its own basic block to add code */
    llvm::BasicBlock *averageBB = llvm::BasicBlock::Create(Context, "avg", ourAverage);
    Builder.SetInsertPoint(averageBB);

    /* Now for the code: return (a >> 1) + (b >> 1) + (a && b && 1) */
    auto args = ourAverage->arg_begin();
    auto a = &*args; //Get a Value* (with &) from the iterator (with *)
    ++args;          //Goes to the next argument
    auto b = &*args;
    auto ashift = Builder.CreateAShr(a, One, "ashift");
    auto bshift = Builder.CreateAShr(b, One, "bshift");
    auto tmp = Builder.CreateAnd(a, b, "andtmp");
    tmp = Builder.CreateAnd(tmp, One, "andtmp");
    tmp = Builder.CreateAdd(bshift, tmp, "sumtmp");
    tmp = Builder.CreateAdd(ashift, tmp, "sumtmp");
    Builder.CreateRet(tmp);

    llvm::verifyFunction(*ourAverage); //Checks if everything is okay with our function

    /*** Now we return to our main to call the average function ***/
    Builder.SetInsertPoint(mainBB);

    /* Lets call average with 41 and 21 */
    std::vector<llvm::Value*> arguments;
    arguments.push_back(llvm::ConstantInt::get(Context, llvm::APInt(64, 41)));
    arguments.push_back(llvm::ConstantInt::get(Context, llvm::APInt(64, 21)));
    auto avgReturn = Builder.CreateCall(ourAverage, arguments, "callavg");

    /* And we return the average at the end*/
    Builder.CreateRet(avgReturn);

    llvm::verifyFunction(*ourMain); //Checks if everything is okay with our function

    /*** Lets print the intermediary representation generated ***/
    OurModule->dump();
    //ourMain->dump();

    /*** Now lets compute it with a just in time (JIT) compiler ***/
    //llvm::ExecutionEngine* OurExecutionEngine;
    //std::string Error;
    //LLVMInitializeNativeTarget(); //target = generates code for my processor
    //OurExecutionEngine = llvm::EngineBuilder(OurModule).setErrorStr(&Error).create();
    //if (!OurExecutionEngine) {
    //    fprintf(stderr, "Could not create OurExecutionEngine: %s\n", Error.c_str());
    //    exit(1);
    //}

    //// JIT our main. It returns a function pointer.
    //void *mainPointer = OurExecutionEngine->getPointerToFunction(ourMain);
    //// Translate the pointer and run our main to get its results
    //int (*result)() = (int (*)())(intptr_t)mainPointer;
    //std::cout << "Result of our main = " << result() << std::endl;
}
