/*--- Грамматика ---
	res = stmt
	stmt :: =  while ( cond ) stmt
	stmt ::= print ( param );
	cond ::= param < param
	cond ::= param > param
	cond ::= param
	param ::= ++ var
	param ::= var
	param ::=  num
	var ::= i
*/
#include <iostream>
#include "parser.h"

int main ()
{
	Parser parser;
	parser.open_file ();
	parser.lookahead = parser.scan ();
	parser.res ();
	return 0;
}

