/*
lang:
only escape sequence im going to process is \n
letter = 'A'|...|'Z'|'a'|...|'z'
digit  = '0'|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'
number = digit digit*
identifier = letter (letter|digit)*
operator = '='
keyword = '+'|'-'|'*'|'/'
esc = '\n'
openPar='('
closePar=')'
statement = identifier operator identifier keyword 
closedStatement= openPar statement closedPar

time to make DFA

*/
#include<stdio.h>
#include<stdlib.h>

int main(void){
    int countChar=0;
    FILE* fopen("exe.toyYEHE","r");
    while (countChar != EOF){
        
    }
    
}