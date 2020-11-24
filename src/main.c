#include "include/displayManager.h"
#include "include/io.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");

    int** sprite = loadSpriteFromFile("data/staticMap.txt");
    
    //wprintf((wchar_t*)("%c"), );
    //wprintf((wchar_t*)("%c"), );
    //wprintf((wchar_t*)("%c"), sprite[0][7]);
    showSprite(sprite);
    wprintf(L"%lc\n", sprite[3][7]);


    return 0;
}

