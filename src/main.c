#include "include/displayManager.h"
#include "include/io.h"
#include "include/train.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");

    sprite Bg;
    Bg.img= loadSpriteFromFile("data/staticMap.txt");
    Bg.container.x= Bg.container.y= Bg.container.xMin= Bg.container.yMin= 0;
    Bg.container.xMax= MAX_COLUMNS;
    Bg.container.yMax= MAX_LINES;
    Bg.nextSprite= calloc(1, sizeof(sprite*));
    Bg.maskMap= NULL;
    Bg.color= 'w';
    showSprite(Bg);

    Train* TrainUpper= train_create(0);
    Train* TrainLower= train_create(1);
    Bg.container.xMax= 6;
    Bg.container.yMin= 22;
    TrainUpper->sprite.nextSprite[0]= &TrainLower->sprite;
    TrainUpper->sprite.nextSprite[1]= &Bg;
    showSprite(TrainUpper->sprite);

    return 0;
}

