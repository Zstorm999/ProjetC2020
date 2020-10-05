#include "include/io.h"


int main(){

    char** arr = loadSpriteFromFile("data/trainUpper.txt");
    
    printf("%c\n", arr[2][1]);
    
    return 0;
}

