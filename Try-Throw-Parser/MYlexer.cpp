#include "MYlexer.h"

int lookahead;
std::string text;

int scan() {
	std::string lastToken = "";
	while (1) {
		char c = getchar();
		// lastToken += c; 
		// this lastToken made an error when parsed text began with ' '
		// solution - dropped it to final else before while
		if (c == ' ' || c == '\t' || c == '\r') { ; }
		else if (c == '\n') {
			return -1;
		}

		else if (c == 't') {
			ungetc(c, stdin);
			int result = isTryOrThrow();
			if (result == 1) {
				lookahead = TRY;
				return lookahead;
			}
			else if (result == 2) {
				lookahead = THROW;
				return lookahead;
			}
			else if (result == 3) {
				lookahead = TEXT;
				return lookahead;
			}
		}
		
		else if (c == 'p') {
			ungetc(c, stdin);
			if (isPrint()) {
				lookahead = PRINT;
				return lookahead;
			}
			else {
				lookahead = TEXT;
				return lookahead;
			}
		}
		
		else if (c == 'c') {
			ungetc(c, stdin);
			if (isCatch()) {
				lookahead = CATCH;
				return lookahead;
			}
			else {
				lookahead = TEXT;
				return lookahead;
			}
		}
		
		else if (c == '{') {
			lookahead = LPAREN;
			return lookahead;
		}
		
		else if (c == ';') {
			lookahead = TCHKZPT;
			return lookahead;
		}
		
		else if (c == '}') {
			lookahead = RPAREN;
			return lookahead;
		}
		
		else if (c == '(') {
			lookahead = OPEN;
			return lookahead;
		}
		
		else if (c == ')') {
			lookahead = CLOSE;
			return lookahead;
		}		

		else {
		lastToken += c;
			while (c != ' ' && c!= ';' && c != ')') {
				c = getchar();
				lastToken += c;
			}
			ungetc(c, stdin);
			lookahead = TEXT;
			text = lastToken;
			return lookahead;
		}
	}
}

int isTryOrThrow() {
	std::string buf = "";
	char m;
	m = getchar();
	while (m != ' ' && m != '}' && m != ';') {
		buf += m;
		m = getchar();
	}
	ungetc(m,stdin);
	buf.length();
	if (strcmp (buf.c_str(), "try") == 0)
		return 1;
	else if (strcmp(buf.c_str(), "throw") == 0)
		return 2;
	else { 
		text = buf; 
		return 3;
	}
		
}

bool isPrint() {
	std::string buf = "";
	char m;
	m = getchar();
	while (m != ' ' && m != '}' && m != ';') {
		buf += m;
		m = getchar();
	}
	ungetc(m, stdin);
	if (strcmp(buf.c_str(), "print") == 0)
		return true;
	else {
		text = buf;
		return false;
	}
}

/*bool isCatch() {
	char str[5];
	int i = 0;
	for (i; i < 5; i++) {
		str[i] = getchar();
	}
	std::cout << strcmp(str, "catch") << std::endl;
	if (strcmp(str, "catch") == 0)
		return true;
	else
		return false;
}*/
bool isCatch() {
	std::string buf = "";
	char m;
	m = getchar();
	while (m != ' ' && m != '}' && m != ';') {
		buf += m;
		m = getchar();
	}
	ungetc(m, stdin);
	if (strcmp(buf.c_str(), "catch") == 0)
		return true;
	else
	{
		text = buf;
		return false;	
	}
}

int error(std::string errorMessage) {
	std::cout << errorMessage << "\n";
	exit(EXIT_FAILURE);
}