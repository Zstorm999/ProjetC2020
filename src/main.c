/**
 * - Copyright 01/11/2020
 *
 * This source code is released the GNU GPLv3's policy,
 * thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
 * distribute and/or modify any of part of the project
 * 
 * the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
 * discaim all copyright interest in the program ProjectC2020
 */

#include "include/displayManager.h"
#include "include/io.h"
#include "include/menu.h"
#include "include/structs.h"
#include "include/train.h"
#include "include/spawner.h"
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

void sighandler(int);

int main()
{
    signal(SIGINT, sighandler);

    setlocale(LC_ALL, "");
    system("stty -echo"); //enable input playback
    srand(time(NULL));

    Train** trains = NULL;
    Spawner* spawnUp = NULL;
    Spawner* spawnDown = NULL;

    while(1){//general menu loop
        system("clear");

        system("tput cnorm"); //enable cursor
        int next = manageMenu(); // return 0: classic mode, return 1: only trains (because we are running out of time ^^)
        system("tput civis"); //disable cursor

        initDisp();

        trains = initTrains();
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
        if(trains[0] != NULL) train_destroy(trains[0]);
        if(trains[1] != NULL) train_destroy(trains[1]);

    }
    quit:

    if(spawnUp != NULL) destroySpawner(spawnUp);
    if(spawnDown != NULL) destroySpawner(spawnDown);
    if(trains[0] != NULL) train_destroy(trains[0]);
    if(trains[1] != NULL) train_destroy(trains[1]);
    
    system("stty echo"); //enable input playback
    system("tput cnorm"); //enable cursor

    return 0;
}

void sighandler(int signum)
{
    system("stty echo"); //enable input playback
    system("tput cnorm"); //enable cursor
    exit(0);
}