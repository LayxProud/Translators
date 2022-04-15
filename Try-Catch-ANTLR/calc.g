options {
	language="Cpp";
}

class CalcParser extends Parser;
options {
	genHashLines = true;		// include line number information
	buildAST = true;			// uses CommonAST by default
}

file [bool externalCond]
{
std::vector<std::string> exeptions;
}
	: exeptions = stmt[exeptions]  EOF //{std::cout <<"file := stmt  "<< '\n';}
	;

stmt [std::vector<std::string> exeptions] returns [std::vector<std::string> result]
{
	bool cond = true;
}
	: TRY^ LCURLYBRACE result = aa[exeptions, cond] RCURLYBRACE c[result] //{std::cout <<"file := aa  C  "<< '\n';}
	; 
	
aa [std::vector<std::string> exeptions, bool cond] returns [std::vector<std::string> result]
{
	std::vector<std::string> result_2;
}
	: (result = a[exeptions,cond] result_2 = aa[result,cond])=> (result = a[exeptions,cond] result_2 = aa[result,cond]) {result = result_2;}
	| (result = a[exeptions,cond])
	;

a [std::vector<std::string> exeptions,bool cond] returns [std::vector<std::string> result]
{
	std::string name;
}
	:THROW^ name = expr SEMI {exeptions.push_back(name); result = exeptions;}
	|PRINT^ name = expr SEMI {if(cond) std::cout <<name<< '\n';result = exeptions;} 
	|result = stmt[exeptions]
	;

	
c [std::vector<std::string> exeptions]
{
	std::string var_name;
	bool cond  = false;
	std::vector<std::string> result;
}
	: (CATCH^ LPAREN var_name=expr {for (unsigned i=0; i<exeptions.size(); i++){ if (exeptions[i]==var_name) cond = true;}} RPAREN LCURLYBRACE result = aa[exeptions, cond] RCURLYBRACE)+
	;
	


expr returns[std::string result]
    	:  i: ID {result = i->getText().c_str();}
	;



class CalcLexer extends Lexer;
options {
k=2;
}
WS_	:	(' '
	|	'\t'
	|	'\n'
	|	'\r')
		{ _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; }
	;


THROW: ("throw")
	;

TRY: ("try")
	;

CATCH: ("catch")
	;

LPAREN:	'('
	;

RPAREN:	')'
	;

LCURLYBRACE: '{'
	;
	
RCURLYBRACE: '}'
	;

PRINT: ("print")	
	;
	
SEMI:	';'
	;

ID
 : 'A'..'Z'
 ('A'..'Z'|'a'..'z' | '_' | '0'..'9')*
 ;




class CalcTreeWalker extends TreeParser;
	
file returns [int r] 
	: stmt  EOF //{std::cout <<"file := a  "<< '\n';}
	;

stmt
	: #(TRY LCURLYBRACE aa RCURLYBRACE c)
	; 
	
aa
	: (a)+
	;

a 
	: #(PRINT expr SEMI)   //{std::cout <<"a := b  "<< '\n';}
	| #(THROW expr SEMI)
	| stmt
	;

	
c 
	:  (#(CATCH LPAREN expr RPAREN LCURLYBRACE aa RCURLYBRACE c))=>#(CATCH LPAREN expr RPAREN LCURLYBRACE aa RCURLYBRACE c)
	|  (#(CATCH LPAREN expr RPAREN LCURLYBRACE aa RCURLYBRACE))=>#(CATCH LPAREN expr RPAREN LCURLYBRACE aa RCURLYBRACE)
	;
	


expr
    	:  i: ID
	;