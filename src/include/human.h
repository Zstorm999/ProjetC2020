extern struct Spawner;


#ifndef _HUMAN_H
#define _HUMAN_H

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "io.h"
#include "globals.h"
#include "displayManager.h"
#include "train.h"
#include "spawner.h"

//struct declaration
enum Movement{SPAWNING, IDLE, RANDOM};

typedef struct Human Human;
struct Human{
    sprite sprite;
    enum Movement movType;

    //linked list
    Human* next;

    //extenal references:
    struct Spawner* creator;
    //char** objmap;
};

Human* createHuman(int x, int y, struct Spawner* creator); //must provide the two trains, the train will then be chosen using the human's y pos
void destroyHuman(Human* person);

void moveHuman(Human* person);

#endif //_HUMAN_H

