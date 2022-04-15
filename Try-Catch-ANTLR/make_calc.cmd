set path=C:\MinGW\bin
echo *** Creating source files from calc.g ***
antlr-2.7.5.exe calc.g
echo *** Compiling source files, creating executable calc.exe ***
g++ -o acalc Main.cpp CalcLexer.cpp CalcParser.cpp CalcTreeWalker.cpp -lantlr -I.
echo *** Followed input will be passed to acalc.exe ***
type test.in
echo *** Running acalc.exe file with listed input ***
acalc.exe <test.in
pause