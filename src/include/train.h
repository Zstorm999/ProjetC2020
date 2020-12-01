/**
 * This source code is under the GPLv3's policy,
 * thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
 * distribute and/or modify any of part of the project
 * 
 * the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
 * discaim all copyright interest in the program ProjectC2020
 */

#ifndef _TRAIN_H
#define _TRAIN_H

#include "io.h"
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

#define LANE_TOP 15
#define LANE_BOT 19
#define TRAIN_SIZE 106
#define BASE_POSX  -TRAIN_SIZE;
#define TRAIN_COLOR 'Y'

#define MININTERVALTRAIN 30 //38  //seconds, the interval betwin each train is randomized
#define MAXINTERVALTRAIN 93 //120 //seconds
#define HALT_TIME 10 //18         //seconds

typedef struct _Train Train;
struct _Train{
    //attributes which define the object:
    sprite spriteTrain;
    bool visible;
    bool arrived;
    int updatesBeforeArrival;
    float velocity;         //positive = left to right, negative = right to left
    
    //attributes used by the object:
    sprite** toUpdateFirst; //is used to rebuild the background while updating location (not automated)
    int* misc;
    sprite* doorOpen;
    sprite* doorClose;
    bool clkComute; //is used for very slow movement (velocity= 0.5)
};

//creates a new Train
//file should contain the sprite of the train, as a char[][]
//line should be 0 for top lane, and 1 for bottom lane
Train* train_create(int lane);
void train_destroy(Train* train);
Train** initTrains();
void moveUpperTrain(Train* train);
void moveLowerTrain(Train* train);
void updateTrainUp(Train* train);
void updateTrainDown(Train* trains);
void updateTrains(Train** trains);

#endif //_TRAIN_H