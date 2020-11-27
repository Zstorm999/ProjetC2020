#ifndef _HUMAN_H
#define _HUMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "io.h"
#include "globals.h"

typedef enum Movement{SPAWNING, IDLE, RANDOM} Movement;

typedef struct Human{

    sprite sprite;

    Movement movType;
} Human;


Human* createHuman(int x, int y);
void destroyHuman(Human* person);

void moveHuman(Human* person);


#endif //_HUMAN_H