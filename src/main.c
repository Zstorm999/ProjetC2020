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
    system("clear");
    setlocale(LC_ALL, "");
    
    manageMenu(); // return 0: classic mode, return 1: fast mode (because it's easy to implement ^^)
    
    system("tput civis"); //disable cursor
    initDisp();

    Train** Trains= initTrains();

    Spawner* spawnUp = initSpawner(0, 20, 'E');

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
        
        updateTrains(Trains);

        usleep(TICK_INTERVAL);
    }
    quit:
    
    system("tput cnorm"); //enable cursor

    return 0;
}

