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
%type <node> expr line endline /*varlist*/
%type <block> lines program
%type <novalue> startcode

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 */
%left T_PLUS
%left T_TIMES

/* Starting rule 
 */
%start program

%%

program : startcode lines endline { $2->lines.push_back($3); programRoot = $2; }
        ;

startcode : { IR::codeGenSetup(); }
          ;

endline : ID NL { $$ = new AST::Variable($1); IR::codeGenEnd(symbolTable.useVariable($1)); }

lines   : line { $$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | lines line { if($2 != NULL) $1->lines.push_back($2); $$ = $1; }
        ;

line    : NL { $$ = NULL; } /*nothing here to be used */
        | expr NL /*$$ = $1 when nothing is said*/
        | TYPE_INT ID { $$ = new AST::Variable($2); symbolTable.createVariable($2); }
        | ID ASSIGN expr { $$ = new AST::BinOp(new AST::Variable($1),AST::assign,$3); }
        ;

expr    : INT { $$ = new AST::Integer($1); }
        | ID { $$ = new AST::Variable($1); } 
        | expr PLUS expr { $$ = new AST::BinOp($1,AST::plus,$3); }
        | expr TIMES expr { $$ = new AST::BinOp($1,AST::times,$3); }
        ;

%%


