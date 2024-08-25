#include <stdio.h>
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    
    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }
    
    unsigned long before_mod = hash;
    unsigned long after_mod = before_mod % 7;
    
    printf("Before mod: %lu\n", before_mod);
    printf("After mod:  %lu\n", after_mod);
    
    return after_mod;
}

int main() {
    hash("in");
}