/*--- Грамматика ---
    stmt ::= try { a’ } cc
    a’ ::= aa’ | a
    a ::= print expr; | throw expr; | stmt
    cc ::= catch ( expr ) { a’ } cc | catch ( expr ) { a’ }
*/
#include "parser.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cctype>
#include <io.h>

#define MAX_LEXEM 15

Parser::Parser ()
{
}

Parser::~Parser ()
{
}

void Parser::open_file ()
{
  if (!fopen("fio.txt","r")) {
      printf("Error. Cannot open file");
      return;
    }
  file = fopen ("fio.txt", "r");
  lookahead = -1;

}

int Parser::scan ()
{
  char ch;
  char lexem [MAX_LEXEM];
  int j=0;
  for (int i=0; i < MAX_LEXEM; i++)
    lexem[i]='\0';
  while(true)
    {
      ch=fgetc(file);
      if (ch != ' ' && ch != EOF)
        {
          lexem[j] = ch;
          j++;
        }
      else
        break;
    }

  printf ("Lexem '%s' analyzed as ", lexem);

  if ((lexem[0]=='t') &&
      (lexem[1]=='r') &&
      (lexem[2]=='y'))
    {
      printf ("TRY\n");
      lookahead = TRY;
    }
  else if ((lexem[0]=='p') &&
           (lexem[1]=='r') &&
           (lexem[2]=='i') &&
           (lexem[3]=='n') &&
           (lexem[4]=='t'))
    {
      printf ("PRINT\n");
      lookahead = PRINT;
    }
  else if ((lexem[0]=='t') &&
           (lexem[1]=='h') &&
           (lexem[2]=='r') &&
           (lexem[3]=='o') &&
           (lexem[4]=='w'))
    {
      printf ("THROW\n");
      lookahead = THROW;
    }
  else if ((lexem[0]=='c') &&
           (lexem[1]=='a') &&
           (lexem[2]=='t') &&
           (lexem[3]=='c') &&
           (lexem[4]=='h'))
    {
      printf ("CATCH\n");
      lookahead = CATCH;
    }
  else if ((lexem[0]=='e') &&
           (lexem[1]=='x') &&
           (lexem[2]=='p') &&
           (lexem[3]=='r'))
    {
      printf ("EXPR\n");
      lookahead = EXPR;
    }
  else if (lexem[0] == '(')
    {
      printf ("OP_BR\n");
      lookahead = OP_BR;
    }
  else if (lexem[0] == ')')
    {
      printf ("CL_BR\n");
      lookahead = CL_BR;
    }
  else if (lexem[0] == '{')
    {
      printf ("OP_FIG_BR\n");
      lookahead = OP_FIG_BR;
    }
  else if (lexem[0] == '}')
    {
      printf ("CL_FIG_BR\n");
      lookahead = CL_FIG_BR;
    }
  else if (lexem[0] == ';')
    {
      printf ("TCHKZPT\n");
      lookahead = TCHKZPT;
    }
  else if (lexem[0] == '\0')
    {
      printf ("FIN\n");
      lookahead = FIN;
    }

  return lookahead;
}

void Parser::match ( int t )
{
  if (lookahead == t)
    {
      lookahead = scan();
    }
  else if (lookahead == '\0')
    return;
  else
    {
      err ("Invalid input, don't match the expectations");
    }
}

void Parser::err ( std::string str )
{
  std::cout << std::endl;
  std::cout << str << std::endl;
  exit (1);
}

int Parser::res ()
{
  stmt();
  printf ("\nScan successfull!\n");
  return lookahead;
}

int Parser::stmt ()
{
  if (lookahead == TRY)
    {
      match (TRY);
      match (OP_FIG_BR);
      stmt();
      match (CL_FIG_BR);
      ctch();
    }
  else if (lookahead == PRINT)
    {
      match (PRINT);
      match (EXPR);
      match (TCHKZPT);
    }
  else if (lookahead == THROW)
    {
      match (THROW);
      match (EXPR);
      match (TCHKZPT);
    }
  else
    err ("Invalid input in stmt");
  return lookahead;
}

int Parser::ctch ()
{
  if (lookahead == CATCH)
    {
      match (CATCH);
      match (OP_BR);
      match (EXPR);
      match (CL_BR);
      match (OP_FIG_BR);
      stmt();
      match (CL_FIG_BR);
      ctch();
    }
  return lookahead;
}
