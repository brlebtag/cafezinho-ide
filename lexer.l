%{
#include <stdio.h>
#include "arvore_abstrata.h"
#include "parser.h"
#include "CompThread.h"
#include "CompInfo.h"

#define YY_DECL extern "C" int yylex()

extern void yyerror(NBloco * bloco, const char *s);
extern bool erro_lexico;
extern bool erro_compilador;

using namespace std;

QString ultimo_token;

%}


D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
ID 			[_a-zA-Z][_a-zA-Z0-9]*
OC 			[0-7]

%option noyywrap
%option yylineno

%%

0[xX]{H}+			{
/* Numero Hexadecimal*/
                        QString ss = yytext;
                        bool ok;
                        yylval.ival = ss.toInt(&ok, 16);
                        ultimo_token = ss;
                        return(INT_CONST);
                    }

0{OC}+				{
/* Numero Octeto */
                        QString ss = yytext;
                        bool ok;
                        yylval.ival = ss.toInt(&ok, 8);
                        ultimo_token = ss;
                        return(INT_CONST);
                    }

0?{D}+			{
/* Numero Inteiro */
                        QString ss = yytext;
                        bool ok;
                        yylval.ival = ss.toInt(&ok, 10);
                        ultimo_token = ss;
                        return(INT_CONST);
                    }

{D}+{E}		{
/* Numero real  */
                        QString ss = yytext;
                        bool ok;
                        yylval.ival = ss.toDouble(&ok);
                        ultimo_token = ss;
                        return(REAL_CONST);
                    }

{D}*"."{D}+({E})? {
/* Numero real  */
                            QString ss = yytext;
                            bool ok;
                            yylval.ival = ss.toDouble(&ok);
                            ultimo_token = ss;
                            return(REAL_CONST);
                        }

{D}+"."{D}*({E})?	{
/* Numero real  */
                            QString ss = yytext;
                            bool ok;
                            yylval.ival = ss.toDouble(&ok);
                            ultimo_token = ss;
                            return(REAL_CONST);
                        }
"/*"		{
                register int c;
                for ( ; ; )
                {
                    while ( (c = yyinput()) != '*' && c != EOF );
                    if ( c == '*' )
                    {
                        while ( (c = yyinput()) == '*' );
                        if ( c == '/' )
                        {
                            break;
                        }
                    }
                    if ( c == EOF )
                    {
                        erro_lexico = true;
                        yyerror(0, "COMENTARIO NAO TERMINA" );
                        break;
                    }
                }
            }

"\""		{
                QString val;

                register int c;
                for ( ; ; )
                {
                    while ( (c = yyinput()) != '\"' && c != EOF && c != '\n' && c !='\\')
                        val+=c;

                    if(c == '\\')
                    {
                        /*Eu ignoro o proximo caractere pq \\ é o caracter de escape*/
                        c = yyinput();
                        if(c==EOF)
                        {
                            erro_lexico = true;
                            yyerror(0, "CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA" );
                            break;
                        }
                        else
                            val+=c;
                    }
                    if( c == '\"')
                    {
                        yylval.sval = new QString(val) ;
                        ultimo_token = "PALAVRA LITERAL";
                        return ::PALAVRA_LITERAL;
                        break;
                    }
                    if( c == '\n')
                    {
                        erro_lexico = true;
                        yyerror(0, "CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA" );
                        break;
                    }
                    if ( c == EOF )
                    {
                        erro_lexico = true;
                        yyerror(0, "CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA" );
                        break;
                    }
                }
            }

"**="		{
                ultimo_token = "**=";
                return ::POT_ATRIBUICAO;
            }

">>="		{
                ultimo_token = ">>=";
                return ::DIR_ATRIBUICAO;
            }

"<<="		{
                ultimo_token = "<<=";
                return ::ESQ_ATRIBUICAO;
            }

"+="		{
                ultimo_token = "+=";
                return ::ADICAO_ATRIBUICAO;
            }

"-="		{
                ultimo_token = "-=";
                return ::SUBTRACAO_ATRIBUICAO;
            }

"*="		{
                ultimo_token = "*=";
                return ::MULT_ATRIBUICAO;
            }

"/="		{
                ultimo_token = "/=";
                return ::DIV_ATRIBUICAO;
            }

"%="		{
                ultimo_token = "%=";
                return ::MOD_ATRIBUICAO;
            }

"&="		{
                ultimo_token = "&=";
                return ::E_ATRIBUICAO;
            }

"^="		{
                ultimo_token = "^=";
                return ::XOR_ATRIBUICAO;
            }

"|="		{
                ultimo_token = "|=";
                return ::OU_ATRIBUICAO;
            }

">>"		{
                ultimo_token = ">>";
                return ::DIR_OP;
            }

"<<"		{
                ultimo_token = "<<";
                return ::ESQ_OP;
            }

"++"		{
                yylval.ival = yylineno;
                ultimo_token = "++";
                return INC_OP;
            }

"--"		{
                yylval.ival = yylineno;
                ultimo_token = "--";
                return DEC_OP;
            }

"&&"		{
                ultimo_token = "&&";
                return ::E_OP;
            }

"||"		{
                ultimo_token = "||";
                return ::OU_OP;
            }

"**"		{
                ultimo_token = "**";
                return ::POT_OP;
            }

"<="		{
                ultimo_token = "<=";
                return ::LE_OP;
            }

">="		{
                ultimo_token = ">=";
                return ::GE_OP;
            }

"=="		{
                ultimo_token = "==";
                return ::EQ_OP;
            }

"!="		{
                ultimo_token = "!=";
                return ::NE_OP;
            }

";"			{
                ultimo_token = ";";
                return ';';
            }

"{"			{
                yylval.ival = yylineno;
                ultimo_token = "{";
                return '{';
            }

","			{
                ultimo_token = ",";
                return ',';
            }

"}"			{
                ultimo_token = "}";
                return '}';
            }

":"			{
                ultimo_token = ":";
                return ':';
            }

"="			{
                ultimo_token = "=";
                return '=';
            }

"("			{
                yylval.ival = yylineno;
                ultimo_token = "(";
                return '(';
            }

")"			{
                ultimo_token = ")";
                return ')';
            }

"["			{
                yylval.ival = yylineno;
                ultimo_token = "[";
                return '[';
            }

"]"			{
                ultimo_token = "]";
                return ']';
            }

"&"			{
                ultimo_token = "&";
                return '&';
            }

"!"			{
                ultimo_token = "!";
                return '!';
            }

"~"			{
                ultimo_token = "~";
                return '~';
            }

"-"			{
                ultimo_token = "-";
                return '-';
            }

"+"			{
                ultimo_token = "+";
                return '+';
            }

"*"			{
                ultimo_token = "*";
                return '*';
            }

"/"			{
                ultimo_token = "/";
                return '/';
            }

"%"			{
                ultimo_token = "%";
                return '%';
            }

">"			{
                ultimo_token = ">";
                return ::BT_OP;
            }

"<"			{
                ultimo_token = "<";
                return ::LT_OP;
            }

"^"			{
                ultimo_token = "^";
                return '^';
            }


"|"			{
                ultimo_token = "|";
                return '|';
            }

"?"			{
                ultimo_token = "?";
                return '?';
            }


"'"			{
                register int a = yyinput(), b=yyinput();
                if(a=='\\'&&b=='\''&& (a=yyinput())=='\'')
                {

                    //esta composicao e '\'' que é OK!
                    ultimo_token = "\'";
                    yylval.ival = (int) '\'' ;
                    return CAR_CONST;
                }
                else if(a!='\''&&b=='\'')
                {
                    //esta composicao e 'c' onde c!=vazio
                    ultimo_token = a;
                    yylval.ival = (int) a ;
                    return CAR_CONST;
                }
                else
                {
                    erro_lexico = true;

                    if(a=='\'')
                    {
                        yyerror(0, "CONSTANTE CARACTERE VAZIA" );
                    }
                    else
                    {
                        yyerror(0, "ESTOURO DE CONSTANTE CARACTERE" );
                    }
                }

            }

"nulo"	    {
                ultimo_token = "nulo";
                return NULO;
            }

"car" 		{
                ultimo_token = "car";
                return CAR;
            }

"real" 		{
                ultimo_token = "real";
                return ::REAL;
            }

"int"		{
                ultimo_token = "int";
                return ::INT;
            }

"retorne"	{
                yylval.ival = yylineno;
                ultimo_token = "retorne";
                return ::RETORNE;
            }

"leia"		{
                yylval.ival = yylineno;
                ultimo_token = "leia";
                return ::LEIA;
            }

"escreva"	{
                yylval.ival = yylineno;
                ultimo_token = "escreva";
                return ::ESCREVA;
            }

"novalinha"	{
                yylval.ival = yylineno;
                ultimo_token = "novalinha";
                return ::NOVA_LINHA;
            }

"se" 		{
                yylval.ival = yylineno;
                ultimo_token = "se";
                return ::SE;
            }

"senao" 	{
                yylval.ival = yylineno;
                ultimo_token = "senao";
                return SENAO;
            }

"entao"		{
                ultimo_token = "entao";
                return ENTAO;
            }

"enquanto"	{
                yylval.ival = yylineno;
                ultimo_token = "enquanto";
                return ::ENQUANTO;
            }

"execute"	{
                ultimo_token = "execute";
                return EXECUTE;
            }

"e" 		{
                ultimo_token = "e";
                return ::E_OP;
            }

"ou"		{
                ultimo_token = "ou";
                return ::OU_OP;
            }

"terminar"	{
                ultimo_token = "terminar";
                yylval.ival = yylineno;
                return ::TERMINAR;
            }

"limpar"	{
                ultimo_token = "limpar";
                yylval.ival = yylineno;
                return ::LIMPAR;
            }

{ID}+ 		{
                ultimo_token = "IDENTIFICADOR ";
                ultimo_token += yytext;
                yylval.sval = new QString(yytext) ;
                return ::IDENTIFICADOR;
            }


[ \t\v\r\n\f] ; /* eat up whitespace */

.			{
                erro_lexico = true;
                QString erro = "JUNTO AO TOKEN";
                erro += yytext;
                ultimo_token = yytext;
                yyerror(0, erro.toLocal8Bit().constData());
            }

%%
