%{

#include <QString>
#include <QDebug>

#define YY_DECL extern "C" int yylex()

#include "parser.h"

extern void yyerror(QString s);

%}

%option noyywrap

DIGIT [0-9]

%%

{DIGIT}+ {
                yylval.value = atoi(yytext);
                return INTCONST;
         }

"(" 	{
                return ('(');
        }

")" 	{
                return (')');
        }

"+" 	{
                return ('+');
        }

"-" 	{
                return ('-');
        }
%%
