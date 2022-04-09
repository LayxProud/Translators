#include <stdio.h>
#include "MYlexer.h"

extern int lookahead;
extern std::string text;
std::string nameOfException;
std::string catchedException;
bool tryTrue = true;

/*
*  грамматика
*
* stmt ::= try { a' } cc
* a' ::= a b
* a ::= throw expr; | stmt
* b ::= a' | Epsilon
* cc ::= catch ( expr ) { d' } cc'
* cc' ::= cc | Epsilon
* d' ::= print expr; d
* d ::= d' | Epsilon
*
*/

void stmt(bool firstTry);
bool aI(bool flag);
void b(bool flag);
void a(bool flag);
void cc(bool flag);
void ccI();
bool dI(bool flag);
void d();

// блок try
void stmt(bool firstTry) {
	if (firstTry) {
		scan(); 
		if (lookahead != TRY) error("Expected try");
	}
	scan();
	if (lookahead != LPAREN) error("Expected {");
	aI(true);
	if (lookahead != RPAREN) error("Expected }");
	cc(true);
}

// а штрих
bool aI(bool flag) {
	a(flag);
	b(true);
	return flag;
}

// а
void a(bool flag) {
	if (flag) {
		scan();
	}
	switch (lookahead){
		case (THROW): 
			scan();
			nameOfException = text;	
			scan();
			if (lookahead != TCHKZPT) error("Expected ;");
		break;
		case (TRY): 
			stmt(false);
		break;
		default: error("Expected try or throw");
	}
}

// b
void b(bool flag) {
	if (flag && tryTrue) scan();
	else if (!tryTrue)
		tryTrue = !tryTrue;
	if (lookahead == TRY || lookahead == THROW)
		aI(false);
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
	scan();
	if (lookahead != CLOSE) error("Expected )");
	scan();
	if (lookahead != LPAREN) error("Expected {");
	dI(true);
	//if (flag) {
		//scan();
	//}
	if (lookahead != RPAREN) error("Expected }");
	ccI();
}

// d штрих
bool dI(bool flag){
	if (flag){
		scan();
		if (lookahead != PRINT) error("Expected print");
	}
	scan();
	if (strcmp(nameOfException.c_str(), catchedException.c_str()) == 0)
		std::cout << "Your output: " << text << std::endl;
	scan();
	if (lookahead != TCHKZPT) error("Expected ;");
	d();
	return flag;
}

// d
void d(){
	scan();
	if (lookahead == PRINT)
		dI(false);
}

// кетч штрих
void ccI() {
	scan();
	if (lookahead == CATCH)
		cc(false);
	else if (lookahead == THROW) 
		tryTrue = false;
}

int main()
{
	stmt(true);
	system("PAUSE>>NULL");
	return 0;
}