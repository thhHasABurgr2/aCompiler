#include "HashTable.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(void){
    Cell** headCell=(Cell**)malloc(TABLESIZE*sizeof(Cell*));
    
    for(int i =0;i<TABLESIZE;i++){
        headCell[i]=NULL;
    }
    insert(headCell,"if",1);
    insert(headCell,"then",2);
    insert(headCell,"while",3);

    unsigned int ind = look(headCell,"then");
    printf("%d",ind);
    
   
} 