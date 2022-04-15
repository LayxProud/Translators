%{
#define YYSTYPE int
#include "e.tab.h"
#include <stdlib.h>
%}
/*
%{
	#include<stdio.h>
	#include "e.tab.h"
	#include<stdlib.h>
	extern int yylval;
%}
*/

%option noyywrap yylineno
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
NUMBER   [0-9]+

%%

[A-Z][a-z0-9_]*	{ 
		yylval = yytext;
		return ID  ;    
		}


"throw"       	return THROW;
"try"		return TRY;
"catch"		return CATCH;
"print"		return PRINT;

[+?:=,();\n{}] 	{
		   
			yylval = yytext[0];
			return *yytext;
		}
\n          {
                //printf("\nLine %d:", yylineno-1);
                return yytext[0];
            }


%%