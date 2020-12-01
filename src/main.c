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
    
    setlocale(LC_ALL, "");
    
     
    
    system("tput civis"); //disable cursor
    srand(time(NULL));

    while(1){//general menu loop
        system("clear");

        int next = manageMenu(); // return 0: classic mode, return 1: fast mode (because it's easy to implement ^^)

        initDisp();

        Train** Trains= initTrains();
        Spawner* spawnUp = NULL;

        if(next == 0){
            spawnUp = initSpawner(0, 20, 'E', true);
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
            updateSpawner(spawnUp, direction);
            
            updateTrains(Trains);

            usleep(TICK_INTERVAL);
        }

        menu:
        //free spawners and trains here
        if(spawnUp != NULL) destroySpawner(spawnUp);

    }
    quit:
    
    system("tput cnorm"); //enable cursor

    return 0;
}

