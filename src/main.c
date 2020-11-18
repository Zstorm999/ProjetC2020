#include "include/displayManager.h"
#include "include/io.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");

    sprite Sprite;
    Sprite.img = loadSpriteFromFile("data/staticMap.txt");
    Sprite.container.x= Sprite.container.y= Sprite.container.xMin= Sprite.container.yMin= 0;
    Sprite.container.xMax= MAX_COLUMNS;
    Sprite.container.yMax= MAX_LINES;
    Sprite.nextSprite= NULL;
    showSprite(Sprite);

    return 0;
}

