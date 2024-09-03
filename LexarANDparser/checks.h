
#ifndef CHECKS_H
#define CHECKS_H
int isDigit(char input){
    if (input<=57 &&input>=48){
        return 1;
    }
    return 0;
}
int isLetter(char input){
    if ((input>=65 && input <=90) || (input >= 97 && input <=122)){
        return 1;
    }
    return 0;
}
int isPlus(char input){
    if (input == 43){
        return 1;
    }
    return 0;
}
int isSemicolon(char input){
    if (input == 59){
        return 1;
    }
    return 0;
}
int isEqual(char input){
    if (input == 61){
        return 1;
    }
    return 0;
}


#endif