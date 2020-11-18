#include "include/io.h"


int main()
{
    system("clear");

    /*unsigned int** arr = loadSpriteFromFile("data/trainUpper.txt");
    unsigned int testChar= L'ↀ';                                              //according to this test the "L" is mandatory

    

    printf("test: %lc, %u, %lc, %lc", L'Ð', arr[0][4], testChar, arr[0][4]);       //TODO fix arr content not showing up properly
    placec(3, 3, L'ↀ');                                                           //at least this shit works
    printf("\r\n");*/

    setlocale(LC_ALL, "");

    char** sprite = loadSpriteFromFile("data/staticMap.txt");
    showSprite(sprite);


    return 0;
}

