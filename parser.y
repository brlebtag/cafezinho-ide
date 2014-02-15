%{

#include <QString>
#include <QDebug>

extern "C" int yylex();
extern "C" FILE *yyin;
extern int yylineno;

void yyerror(const char *s);

int teste = 10;

%}

%union
{
        int value;
}

%token <value> INTCONST

%start calc

%%


calc: Expr  { qDebug()<<"executado!"<<endl; };

Expr: Expr '+' Term | Term | Term '-' F;

Term: F { };

F: INTCONST { } | '(' Expr ')' { };

%%

void yyerror(const char *s)
{
    qDebug()<<s<<endl;
}
