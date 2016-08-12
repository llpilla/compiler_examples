%{
#include <iostream>

extern int yylex();
extern void yyerror(const char* s, ...);
%}

%define parse.trace

/* yylval == %union
 * union informs the different ways we can store data
 */
%union {
    int value;
}

/* token defines our terminal symbols (tokens).
 */
%token <value> T_INT
%token T_PLUS T_TIMES T_NL

/* type defines the type of our nonterminal symbols.
 * Types should match the names used in the union.
 * Example: %type<node> expr
 */
%type <value> program lines line expr

/* Operator precedence for mathematical operators
 * The latest it is listed, the highest the precedence
 * left, right, nonassoc
 */

/* Starting rule 
 */
%start program

%%

program: /*use ctrl+d to stop*/
    lines /*$$ = $1 when nothing is said*/
    ;

lines: 
    line /*$$ = $1 when nothing is said*/
    | lines line
    ;

line: 
    T_NL { $$ = 0 /*NULL*/; } /*nothing here to be used */
    | expr T_NL { std::cout << "Res: " << $1 << std::endl; }
    ;

expr: 
    T_INT { $$ = $1; } /*Could write nothing here since we are just copying*/
    | expr T_PLUS expr { $$ = $1 + $3; }
    | expr T_TIMES expr { $$ = $1 * $3; }
    ;

%%


