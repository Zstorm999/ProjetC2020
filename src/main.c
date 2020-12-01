#include "include/displayManager.h"
#include "include/io.h"
#include "include/menu.h"
#include "include/structs.h"
#include "include/train.h"
#include "include/spawner.h"
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

int main()
{
    
    setlocale(LC_ALL, "");
    
    
    system("tput civis"); //disable cursor
    srand(time(NULL));

    while(1){//general menu loop
        system("clear");

        int next = manageMenu(); // return 0: classic mode, return 1: fast mode (because it's easy to implement ^^)

        initDisp();

        Train** trains= initTrains();
        Spawner* spawnUp = NULL;
        Spawner* spawnDown = NULL;
        int spawnerUpdate = 0;

        if(next == 0){
            bool isPlayerUp;
            if(rand()%2 == 0) isPlayerUp = true;
            else isPlayerUp = false;            

            spawnUp = initSpawner(0, 20, 'E', isPlayerUp, trains[0], true);
            spawnDown = initSpawner(21, 38, 'E', !isPlayerUp, trains[1], false); //no need to update a train
        }


        while(1){
            //manage input here
            char key = key_pressed();

            PlayerInput direction = NONE;

            switch (key)
            {
                case 'q':
                    placec(MAX_LINES, 0, '\n', 'w');
                    goto menu;
                case 27:
                    if(key_pressed() == 91){
                        char c = key_pressed();
                        switch (c)
                        {
                        case 65:
                            direction = DOWN;
                            break;
                        case 66:
                            direction = UP;
                            break;
                        case 67:
                            direction = RIGHT;
                            break;
                        case 68:
                            direction = LEFT;
                            break;
                        default:
                            break;
                        }
                    }
                    else{ //27 is also the code for ESC
                        placec(MAX_LINES, 0, '\n', 'w');
                        goto quit;
                    }
                    break;
                
                default:
                    break;
            }


            //manage display here
            if(spawnerUpdate == 0){
                updateSpawner(spawnUp, direction);
                updateSpawner(spawnDown, direction);
                spawnerUpdate = 1;
            }
            else{
                spawnerUpdate = 0;
            }

            
            updateTrains(trains);

            usleep(TICK_INTERVAL);
        }

        menu:
        //free spawners and trains here
        if(spawnUp != NULL) destroySpawner(spawnUp);
        if(spawnDown != NULL) destroySpawner(spawnDown);

    }
    quit:
    
    system("tput cnorm"); //enable cursor

    return 0;
}

