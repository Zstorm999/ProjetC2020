#ifndef _TRAIN_H
#define _TRAIN_H

#include "io.h"
#include <stdlib.h>
#include <stdbool.h>

#define LANE_TOP 0;
#define LANE_BOT 1;

typedef struct _Train Train;
struct _Train{
    unsigned int** sprite;

    unsigned int xPos;
    unsigned int yPos;

    bool visible;

    float velocity; //positive = left to right, negative = right to left
};

//creates a new Train
//file should contain the sprite of the train, as a char[][]
//line should be 0 for top lane, and 1 for bottom lane
Train* train_create(char* file, int lane);
void train_destroy(Train* train);

#endif //_TRAIN_H