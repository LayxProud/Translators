#include <stdio.h>
#include <vector>
#include <algorithm>
#include "MYlexer.h"

extern int lookahead;
extern std::string text;
std::vector <std::string> throwExecptions;
std::string nameOfException;
std::vector <std::string> catchExceptions;
std::string catchedException;
bool tryTrue = true;
bool catchedSomething = false;

using namespace std;

/*
*  грамматика
*
* stmt ::= try { a' } cc
* a' ::= a b
* a ::= print expt; | throw expr; | stmt
* b ::= a' | Epsilon
* cc ::= catch ( expr ) { a' } cc'
* cc' ::= cc | Epsilon
*
*/

void stmt(bool firstTry);
bool aI(bool flag, bool catchedSomething);
void b(bool flag);
void a(bool flag, bool catchedSomething);
void cc(bool flag);
void ccI();

// блок try
void stmt(bool firstTry) {
	if (firstTry) {
		scan(); 
		if (lookahead != TRY) error("Expected try");
	}
	scan();
	if (lookahead != LPAREN) error("Expected {");
	aI(true, catchedSomething);
	if (lookahead != RPAREN) error("Expected }");
	cc(true);
}

// а штрих
bool aI(bool flag, bool catchedSomething) {
	a(flag, catchedSomething);
	b(true);
	return flag;
}

// а
void a(bool flag, bool catchedSomething) {
	if (flag) {
		scan();
	}

	string printText;
	switch (lookahead){
		case (THROW): 
			scan();
			nameOfException = text;
			throwExecptions.push_back(nameOfException);
			scan();
			if (lookahead != TCHKZPT) error("Expected ;");
		break;
		case (TRY): 
			stmt(false);
		break;
		case (PRINT):
			if (catchedSomething == false) {
				scan();
				printText = text;
				cout << "Simple print: " << printText << endl;
				scan();
				if (lookahead != TCHKZPT) error("Expected ;");
			}
			else {
				catchedSomething = false;
				scan();
				printText = text;
				/*if (strcmp(nameOfException.c_str(), catchedException.c_str()) == 0)
					cout << "Your output: " << printText << endl;*/
				if (std::find(throwExecptions.begin(), throwExecptions.end(), catchedException) != throwExecptions.end()) {
					/* v contains x */
					cout << "Your output: " << printText << endl;
				}
				else
					cout << "No such exception: " << catchedException << endl;
				scan();
				if (lookahead != TCHKZPT) error("Expected ;");
			}
		break;
		default: error("Expected try or throw or print");
	}
}

// b
void b(bool flag) {
	if (flag && tryTrue) scan();
	else if (!tryTrue)
		tryTrue = !tryTrue;
	if (lookahead == TRY || lookahead == THROW || lookahead == PRINT)
		aI(false, catchedSomething);
}

// блок catch
void cc(bool flag) {
	if (flag) {
		scan();
		if (lookahead != CATCH) error("Expected catch");	
	}
	scan();
	if (lookahead != OPEN) error("Expected (");
	scan();
	catchedException = text;
	catchedSomething = true;
	scan();
	if (lookahead != CLOSE) error("Expected )");
	scan();
	if (lookahead != LPAREN) error("Expected {");
	aI(true, catchedSomething);
	//if (flag) {
		//scan();
	//}
	if (lookahead != RPAREN) error("Expected }");
	ccI();
}

// кетч штрих
void ccI() {
	scan();
	if (lookahead == CATCH)
		cc(false);
	//else if (lookahead == THROW) 
	else
		tryTrue = false;
}

int main()
{
	stmt(true);
	system("PAUSE>>NULL");
	return 0;
}