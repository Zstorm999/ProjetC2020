#include "include/displayManager.h"
#include "include/io.h"
#include "include/menu.h"
#include "include/structs.h"
#include "include/train.h"
#include "include/human.h"
#include <unistd.h>
#include <time.h>

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    
    manageMenu(); // return 0: classic mode, return 1: fast mode (because it's easy to implement ^^)
    
    initDisp();
    char** objMap= loadObjectMap("data/objMap.txt");

    Train** Trains= initTrains();

    Human* person = createHuman(50, 10, objMap, Trains);

    srand(time(NULL));

    while(1){
        //manage input here
        char key = key_pressed();
        switch (key)
        {
            case 'q':
                placec(MAX_LINES, 0, '\n', 'w');
                goto quit;
            default:
                break;
        }

        //manage display here
        moveHuman(person);
        showSprite(&person->sprite, 1);
        
        updateTrainUp(Trains[0]);

        usleep(TICK_INTERVAL);
    }
    quit:

    return 0;
}

