%{
#include "ast.h"
#include "st.h"

ST::SymbolTable symtab;  /* main symbol table */
AST::Block *programRoot; /* the root node of our program AST:: */

extern int yylex();
extern void yyerror(const char* s, ...);
%}

/*Suddenly, the union decided not to find things included before...*/
%code requires{
#include "support.h"
}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    AST::Node *node;        //Node of the syntax tree
    AST::Block *block;      //List of nodes of syntax trees
    AST::VarDeclaration *vars; //List of variables in a declaration
    const char *name;       //Names of variables and values
    Ops::Operation comp;    //Comparison operations ( =, ~=, <, <=, >, >= )
}

/* token defines our terminal symbols (tokens).
 */
%token OP_PLUS OP_TIMES OP_DIV OP_MINUS OP_AND OP_OR OP_NOT
%token ASSIGN END DOTS COMMA
%token T_REAL T_INT T_BOOL
%token PAR_OP PAR_CL
%token <comp> COMP
%token <name> T_ID INT_VAL REAL_VAL BOOL_VAL

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <node> block decl assign target expr term
%type <block> blocks program
%type <vars> listvars

/* Operator precedence for mathematical operators
 * The later it is listed, the higher the precedence
 */
%left OP_AND OP_OR
%left OP_NOT
%nonassoc COMP
%left OP_PLUS OP_MINUS
%left OP_TIMES OP_DIV
%nonassoc OP_MIN_UN
%nonassoc error

/* Starting rule 
 */
%start program

%%

/* A program is composed of blocks */
program : blocks { programRoot = $1; }
        ;

blocks  : block { $$ = new AST::Block(); if($1 != NULL) $$->lines.push_back($1); }
        | blocks block { if($2 != NULL) $1->lines.push_back($2); }
        ;

/* Each block can be an assignment or a variable declaration */
block   : decl END      {$$ = $1;}
        | assign END    
        | error END     {yyerrok; $$ = NULL;}
        ;

/********* Declaration **********/
/* A declaration has a type and a list of variables */
decl    : type DOTS listvars {$$ = $3;}
        ;

/* There are three types */
type    : T_REAL { Types::lastType = Types::real; }
        | T_INT  { Types::lastType = Types::integer; }
        | T_BOOL { Types::lastType = Types::boolean; }
        ;

/* A list of variables is composed of one or more names */
listvars : T_ID { $$ = new AST::VarDeclaration(Types::lastType);
                  $$->variables.push_back(symtab.newVariable($1, Types::lastType));  }
         | listvars COMMA T_ID { $$ = $1;
                                 $$->variables.push_back(symtab.newVariable($3, Types::lastType)); }
         ;

/********* Assignement **********/
/* Assignments have a target that receives the value of an expression */
assign  : target ASSIGN expr { $$ = new AST::BinOp($1, Ops::assign, $3->coerce($1)); }
        ;

/*Targets of assignements can only be simple variables right now*/
target  : T_ID      { $$ = symtab.assignVariable($1); }
        ;

/*Expressions can be composed of one or more expressions, operations, variables, values, etc. */
expr    : term              /*just copies the Node*/
        | expr COMP expr { $$ = new AST::BinOp($1->coerce($3), $2, $3->coerce($1)); }
        | expr OP_PLUS expr { $$ = new AST::BinOp($1->coerce($3), Ops::plus, $3->coerce($1)); }
        | expr OP_TIMES expr { $$ = new AST::BinOp($1->coerce($3), Ops::times, $3->coerce($1)); }
        | expr OP_DIV expr { $$ = new AST::BinOp($1->coerce($3), Ops::div, $3->coerce($1)); }
        | expr OP_MINUS expr { $$ = new AST::BinOp($1->coerce($3), Ops::minus, $3->coerce($1)); }
        | expr OP_AND expr { $$ = new AST::BinOp($1, Ops::andOp, $3); }
        | expr OP_OR expr { $$ = new AST::BinOp($1, Ops::orOp, $3); }
        | OP_NOT expr { $$ = new AST::UnOp($2, Ops::notOp); }
        | OP_MINUS expr %prec OP_MIN_UN { $$ = new AST::UnOp($2, Ops::uMinus); }
        | PAR_OP expr PAR_CL { $$ = new AST::UnOp($2, Ops::par); }
        ;

/*Lets call a term a simple variable or value*/
term    : T_ID      { $$ = symtab.useVariable($1); }
        | INT_VAL   { $$ = new AST::Value($1, Types::integer); }
        | REAL_VAL  { $$ = new AST::Value($1, Types::real); }
        | BOOL_VAL  { $$ = new AST::Value($1, Types::boolean); }
        ;

%%


