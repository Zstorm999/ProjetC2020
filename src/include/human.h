#ifndef _HUMAN_H
#define _HUMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "io.h"
#include "train.h"

typedef enum Movement{SPAWNING, IDLE, RANDOM} Movement;

typedef struct Human{
    sprite sprite;
    Movement movType;

    //extenal references:
    char** objmap;
    Train* train;
} Human;


Human* createHuman(int x, int y, char** objMap, Train** trains); //must provide the two trains, the train will then be chosen using the human's y pos
void destroyHuman(Human* person);

void moveHuman(Human* person);


#endif //_HUMAN_H