#include "include/displayManager.h"
#include "include/io.h"
#include "include/menu.h"
#include "include/structs.h"
#include "include/train.h"
#include "include/human.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    
    manageMenu();
    
    /*initDisp();

    Train** Trains= initTrains();
    //showSprite(Trains[0]->spriteTrain, 1);
    */
    Human* person = createHuman(50, 10);
    showSprite(person->sprite, 1);

    return 0;
}

