#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>

/*--- Грамматика ---
    stmt ::= try { a’ } cc
    a’ ::= aa’ | a
    a ::= print expr; | throw expr; | stmt
    cc ::= catch ( expr ) { a’ } cc | catch ( expr ) { a’ }
*/

class Parser
{
public:
    int lookahead;

    Parser ();
    ~Parser();

    int scan ();
	void match ( int );
	void err ( std::string );
	int res ();
	void open_file ();

private:
	FILE* file;
	//int variables[10];
	//int variables_count;

	int stmt ();
    int ctch ();
};

enum
{
    TRY,
	PRINT,
    THROW,
    CATCH,
    EXPR,
	OP_BR, // (
	CL_BR, // )
    OP_FIG_BR, // {
    CL_FIG_BR, // }
    TCHKZPT, // ;
    FIN // /0
};

#endif // PARSER_H
