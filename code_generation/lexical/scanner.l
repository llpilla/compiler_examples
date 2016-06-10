%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digs [0-9]+
chars [a-zA-Z_]+

%%

[ \t]               ; //ignores spaces
{digs}              {yylval.integer = std::atoi(yytext); return INT;}
"+"                 {return PLUS;}
"*"                 {return TIMES;}
int                 {return TYPE_INT;}
=                   {return ASSIGN;}
\n                  {return NL;}
{chars}             {yylval.name = strdup(yytext); return ID;}
.                   {yyerror("Unknown token! %c\n", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
