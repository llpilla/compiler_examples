%{
#include "ast.h"
#include "symtab.h"
AST::Block *programRoot; /* the root node of our program AST:: */
SymTab::SymbolTable symbolTable; /* symbol table */
extern int yylex();
extern void yyerror(const char* s, ...);
%}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int integer;
    AST::Node *node;
    AST::Block *block;
    const char *name;
    void* novalue;
}

/* token defines our terminal symbols (tokens).
 */
%token <integer> INT
%token PLUS TIMES TYPE_INT ASSIGN NL
%token <name> ID

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <node> expr line /*varlist*/
%type <block> lines program
%type <novalue> startcode

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */
%left PLUS
%left TIMES

/* Starting rule 
 */
%start program

%%

/* program: The program returns the value of the last generated code */
program : startcode lines { programRoot = $2; 
                            IR::codeGenEnd($2->lines.back()->code); /*We are not taking care of empty codes*/}
        ;

/* startcode: Only sets up the code generation environment */
startcode : { IR::codeGenSetup(); }
          ;

/* lines: Lines of code separated by new lines */
lines   : line { $$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | lines line { if($2 != NULL) $1->lines.push_back($2); $$ = $1; }
        ;

/* line: A line of code can declare a variable, give the result of an expression, or give a new value to a variable */
line    : NL { $$ = NULL; } /*nothing here to be used */
        | expr NL /*$$ = $1 when nothing is said*/
        | TYPE_INT ID { $$ = new AST::Variable($2); /*Creates the AST node*/
                        symbolTable.createVariable($2); /*Makes it exist in the symbol table*/ }
        | ID ASSIGN expr { $$ = new AST::BinOp(new AST::Variable($1),AST::assign,$3); /*The assignment updates the symbol table with the new value of a variable*/ }
        ;

/* expr: An expression can be an integer value, a variable, a sum or a multiplication */
expr    : INT { $$ = new AST::Integer($1); /*Only creates the AST node. Does not touch the symbol table.*/ }
        | ID { $$ = new AST::Variable($1); } 
        | expr PLUS expr { $$ = new AST::BinOp($1,AST::plus,$3); }
        | expr TIMES expr { $$ = new AST::BinOp($1,AST::times,$3); }
        ;

%%


