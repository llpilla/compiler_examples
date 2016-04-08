%{
#include <string>
#include "ast.h"
#include "parser.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digs [0-9]+
chars [a-z]+

%%

[ \t]               ; //ignores spaces
{digs}              {yylval.integer = std::atoi(yytext); return T_INT;}
"+"                 {return T_PLUS;}
"*"                 {return T_TIMES;}
","                 {return T_COMMA;}
"="                 {return T_ASSIGN;}
\n                  {return T_NL;}
"def"               {return T_DEF;}
{chars}             {yylval.name = strdup(yytext); return T_ID;}
.                   {yyerror("Unknown token! %c\n", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "Line %d: error: ", yylineno);
    std::vfprintf(stderr, s, ap);
}
