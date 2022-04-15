#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <string>

#define TEXT 256 // expr
#define TRY 257 // try
#define PRINT 258 // print
#define CATCH 259 // catch
#define THROW 260 // throw
#define OPEN 261 // (	
#define CLOSE 264 // )
#define LPAREN 262 // {
#define RPAREN 263 // }
#define TCHKZPT 265 // ;

int scan();
int isTryOrThrow();
bool isPrint();
bool isCatch();
int error(std::string errorMessage);

#endif
