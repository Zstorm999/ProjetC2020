#include "include/displayManager.h"
#include "include/io.h"
#include "include/menu.h"
#include "include/structs.h"
#include "include/train.h"
#include "include/spawner.h"
#include <unistd.h>
#include <time.h>

int main()
{
    int ret;
    ret = system("clear");
    ret = system("tput civis");

    setlocale(LC_ALL, "");
    
    //manageMenu(); // return 0: classic mode, return 1: fast mode (because it's easy to implement ^^)
    
    initDisp();

    //Train** Trains= initTrains();

    Spawner* spawnUp = initSpawner(0, 20);

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
        updateSpawner(spawnUp);
        showSprite(&spawnUp->personList->sprite, 1);
        
        updateTrainUp(Trains[0]);
        updateTrainDown(Trains[1]);

        usleep(TICK_INTERVAL);
    }
    quit:

    ret = system("tput cnorm");

    return 0;
}

