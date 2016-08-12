#include <iostream>

extern int yyparse();
//extern int yydebug;

int main(int argc, char **argv)
{
    //yydebug = 1;              //remove comment to have verbose debug messages
    yyparse();                  //parses whole input
    return 0;
}
