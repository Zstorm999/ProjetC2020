#ifndef _HUMAN_H
#define _HUMAN_H

#include <stdio.h>

typedef enum Movement{IDLE, RANDOM} Movement;

typedef struct Human{

    //this will be overwritten
    char** sprite;

    Movement movType;
    
    int posX;
    int posY;
} Human;


Human* createHuman(int x, int y);
void destroyHuman(Human* person);

//assigns a sprite to a Human, return 0 if failed
int assignSpritetoHuman(Human* person, char** sprite);

#endif //_HUMAN_H