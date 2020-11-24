#ifndef _TRAIN_H
#define _TRAIN_H

#include "io.h"
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

#define LANE_TOP 15;
#define LANE_BOT 19;
#define TRAIN_SIZE 106;
#define BASE_POSX 0; //12;

typedef struct _Train Train;
struct _Train{
    sprite sprite;

    bool visible;
    float velocity; //positive = left to right, negative = right to left
};

//creates a new Train
//file should contain the sprite of the train, as a char[][]
//line should be 0 for top lane, and 1 for bottom lane
Train* train_create(int lane);
void train_destroy(Train* train);

#endif //_TRAIN_H