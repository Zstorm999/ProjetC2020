#include "include/displayManager.h"
#include "include/io.h"
#include "include/train.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    sprite BgScrap= initDisp();

    Train* TrainUpper= train_create(0);
    Train* TrainLower= train_create(1);
    TrainUpper->sprite.nextSprite[0]= &TrainLower->sprite;
    BgScrap.container.xMax= 6;                  //set up wall obstruction on the left
    BgScrap.container.yMin= 21;                 //
    BgScrap.container.yMax= 26;                 //
    TrainLower->sprite.nextSprite[0]= &BgScrap; //
    showSprite(TrainUpper->sprite, 1);

    return 0;
}

