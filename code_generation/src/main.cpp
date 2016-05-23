#include <iostream>
#include "ast.h"

extern AST::Block* programRoot; //set on Bison file
extern int yyparse();
extern int yydebug;

int main(int argc, char **argv)
{
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole data
    std::cout << "##Printing the lines" << std::endl;
    programRoot->printTree();   //prints the ASTs
    std::cout << "##Code generation" << std::endl;
    programRoot->Codegen();
    return 0;
}
