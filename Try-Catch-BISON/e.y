%{
	#include <stdio.h>
%}


%token THROW PRINT CATCH ID TRY


%%


p : stmt '\n' { printf("Done\n"); 
			};
  | error '\n'
  ;
  
stmt
	: TRY '{' aa '}' c
	; 
	
aa
	: a aa
	| a
	;

a 
	: PRINT expr ';'  
	| THROW expr ';'
	| stmt
	;

	
c 
	:  CATCH '(' expr ')' '{' aa '}' c
	|  CATCH '(' expr ')' '{' aa '}'
	

expr
    	:  ID
	;


%%


main() { yyparse(); }
yyerror( mes ) char *mes; {  printf( "error: '%s'", mes ); }