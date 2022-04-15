#include <stdio.h>
#include "MYlexer.h"

extern int lookahead;
extern std::string text;

using namespace std;

/*
*  грамматика
*
* stmt ::= try { a' } cc
* a' ::= a b
* a ::= print expr; | throw expr; | stmt
* b ::= a' | Epsilon
* cc ::= catch ( expr ) { a' } [cc]
*
*/

string stmt(bool executable);
string aI(bool executable);
string b(bool executable);
string a(bool executable); 
string cc(bool executable, string nameOfException, bool catchedSomething); 

// TRY Block
string stmt(bool executable) {
	string nameOfException = "";
	if (lookahead != TRY) error("Expected try");
	scan();
	if (lookahead != LPAREN) error("Expected {");
	scan();
	nameOfException = aI(executable);
	if (lookahead != RPAREN) error("Expected }");
	scan();
	return cc(executable && nameOfException != "", nameOfException, false);
}

// a'
string aI(bool executable) {
	string nameOfException1 = a(executable);
	string nameOfException2 = b(executable && (nameOfException1 == ""));
	return nameOfException1 != "" ? nameOfException1 : nameOfException2;
}

// а
string a(bool executable) {
	string nameOfException = "";
	string printText;
	switch (lookahead) {
	case (THROW):
		scan();
		nameOfException = text;
		scan();
		if (lookahead != TCHKZPT) error("Expected ;");
		scan();
		if (executable) return nameOfException;
		break;
	case (TRY):
		return stmt(executable);
		break;
	case (PRINT):
		scan();
		if (executable)
			cout << "Simple print: " << text << endl;
		scan();
		if (lookahead != TCHKZPT) error("Expected ;");
		scan();
		break;
	default: error("Expected try or throw or print");
	}
	return "";
}

// b
string b(bool executable) {
	if (lookahead == TRY || lookahead == PRINT || lookahead == THROW)
		return aI(executable);
	return "";
}

// CATCH Block
string cc(bool executable, string nameOfException, bool catchedSomething) {
	string nameOfException1 = "";
	string nameOfException2 = "";
	if (lookahead != CATCH) error("Expected catch");
	scan();
	if (lookahead != OPEN) error("Expected (");
	scan();
	string catchedException = text;
	scan();
	if (lookahead != CLOSE) error("Expected )");
	scan();
	if (lookahead != LPAREN) error("Expected {");
	scan();
	nameOfException1 = aI(executable && (catchedException == nameOfException));
	if (lookahead != RPAREN) error("Expected }");
	scan();
	if (lookahead == CATCH)
		nameOfException2 = cc(executable, nameOfException, catchedSomething || (nameOfException == catchedException));
	else if (!catchedSomething && (nameOfException != catchedException))
		nameOfException2 = nameOfException;
	//nameOfException2 = ccI(executable, nameOfException, catchedSomething || (nameOfException == catchedException));
	return nameOfException1 != "" ? nameOfException1 : nameOfException2;
}

int main()
{
	string nameOfException = "";
	scan();
	nameOfException = stmt(true);
	if (nameOfException != "")
		cout << "Not catched Exception: " << nameOfException << endl;
	system("PAUSE>>NULL");
	return 0;
}