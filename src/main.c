#include "include/displayManager.h"
#include "include/io.h"
#include "include/train.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    initDisp();

    Train** Trains= initTrains();
    //showSprite(Trains[0]->spriteTrain, 1);

    return 0;
}

