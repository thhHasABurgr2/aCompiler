
#include "Line.h"
#include "token.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(void){
    /*Cell** headCell=(Cell**)malloc(TABLESIZE*sizeof(Cell*));
    
    for(int i =0;i<TABLESIZE;i++){
        headCell[i]=NULL;
    }
    insert(headCell,"if",1);
    insert(headCell,"then",2);
    insert(headCell,"while",3);

    unsigned int ind = look(headCell,"then");
    printf("%d",ind);
*/
    Line* line=(Line*)malloc(sizeof(Line));
    initLine(line);
    appendCharToLine(line,'a');
    appendCharToLine(line,'b');
    putc(line->stuff[0],stdout);
    putc(line->stuff[1],stdout);
    freeLines(line);
    //Token* token=(Token*)malloc(sizeof(Token));


    
   
} 