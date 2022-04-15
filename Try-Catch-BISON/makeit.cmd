bison -d e.y
rem bison --h
flex e.l
C:\MinGW\bin\gcc -o test.exe lex.yy.c e.tab.c
pause
rem test