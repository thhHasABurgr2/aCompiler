#define TABLESIZE 5
#include<stdlib.h>
#ifndef HASHTABLE
#define HASHTABLE

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++){
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % TABLESIZE;
       
}

unsigned int HashTable[TABLESIZE];

typedef struct{
    const char* key;
    unsigned long val;
}Cell;
typedef struct{
    
}HashTable;
#endif