#include "include/displayManager.h"
#include "include/io.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");

<<<<<<< Updated upstream
    sprite Sprite;
    Sprite.img = loadSpriteFromFile("data/staticMap.txt");
    Sprite.container.x= Sprite.container.y= Sprite.container.xMin= Sprite.container.yMin= 0;
    Sprite.container.xMax= MAX_COLUMNS;
    Sprite.container.yMax= MAX_LINES;
    Sprite.nextSprite= NULL;
    showSprite(Sprite);
=======
    int** sprite = loadSpriteFromFile("data/staticMap.txt");
    
    //wprintf((wchar_t*)("%c"), );
    //wprintf((wchar_t*)("%c"), );
    //wprintf((wchar_t*)("%c"), sprite[0][7]);
    showSprite(sprite);
    wprintf(L"%lc\n", sprite[3][7]);

>>>>>>> Stashed changes

    return 0;
}

