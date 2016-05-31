#include <iostream>
#include "ast.h"
#include "llvm-utils.h"

extern AST::Block* programRoot; //set on Bison file
extern llvm::Module *TheModule;
extern int yyparse();
extern int yydebug;

int main(int argc, char **argv)
{
    /*Start by defining the global module for our code*/
    llvm::InitializeNativeTarget();
    TheModule = new llvm::Module("My first code generating compiler", llvm::getGlobalContext());
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole data
    std::cout << "##Printing the lines" << std::endl;
    programRoot->printTree();   //prints the ASTs
    std::cout << "##Code generation" << std::endl;
    programRoot->Codegen();
    return 0;
}
