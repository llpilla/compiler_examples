%{
#include <string>
#include "ast.h"
#include "parser.h"
#include "support.h"
extern int yylineno;
void yyerror(const char* s, ...);
%}

%option noyywrap nodefault yylineno

digs [0-9]+
chars [a-z]+
reals [0-9]+\.[0-9]*|[0-9]*\.[0-9]+

%%

[ \t\n]               ; //ignores spaces
"TRUE"              {yylval.name = strdup(yytext); return BOOL_VAL;}
"FALSE"             {yylval.name = strdup(yytext); return BOOL_VAL;}

{digs}              {yylval.name = strdup(yytext); return INT_VAL;}
{reals}             {yylval.name = strdup(yytext); return REAL_VAL;}

"+"                 {return OP_PLUS;}
"*"                 {return OP_TIMES;}
"/"                 {return OP_DIV;}
"-"                 {return OP_MINUS;}

"AND"               {return OP_AND;}
"OR"                {return OP_OR;}
"~"                 {return OP_NOT;}

"="                 {yylval.comp = Ops::equal; return COMP;}
"~="                {yylval.comp = Ops::diff; return COMP;}
"<"                 {yylval.comp = Ops::less; return COMP;}
">"                 {yylval.comp = Ops::great; return COMP;}
"<="                {yylval.comp = Ops::lessEq; return COMP;}
">="                {yylval.comp = Ops::greatEq; return COMP;}

":"                 {return DOTS;}
":="                {return ASSIGN;}
";"                 {return END;}
","                 {return COMMA;}

"real"              {return T_REAL;}
"int"               {return T_INT;}
"bool"              {return T_BOOL;}

"("                 {return PAR_OP;}
")"                 {return PAR_CL;}

{chars}             {yylval.name = strdup(yytext); return T_ID;}
.                   {yyerror("lexico: simbolo desconhecido: %c.", *yytext);} /*complains about every unknown character*/

%%

void yyerror(const char *s, ...){
    va_list ap;
    va_start(ap, s);
    std::fprintf(stderr, "[Linha %d] Erro ", yylineno);
    std::vfprintf(stderr, s, ap);
    std::fprintf(stderr, "\n");
}
