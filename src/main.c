#include "include/displayManager.h"
#include "include/io.h"
#include "include/train.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    initDisp();

    Train** trains = initTrains();
    showSprite(trains[0]->spriteTrain, 1);

    return 0;
}

