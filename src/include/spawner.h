#ifndef _SPAWNER_H
#define _SPAWNER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846

#include "structs.h"
#include "io.h"
#include "globals.h"
#include "displayManager.h"
#include "train.h"

typedef struct Human Human;

//struct declaration

//structure only used inside spawner, should never be called otherwise
typedef struct _pointL{
    int x;
    int y;

    struct _pointL* next;
} _pointL;

#define MAX_HUMANS 20

//responsible for creating and handling humans
typedef struct Spawner{
    //linked lists
    struct Human* personList;
    int nbPersons;
    struct _pointL* spawnPoints;
    int nbSPoints;

    int yMin, yMax;
    int nextSpawnCounter;

    sprite** renderArray;
    
    //reference for all Humans to use
    char** objMap;
    sprite* bg;

} Spawner;

//describes movement type
enum Movement{SPAWNING, IDLE, RANDOM};


struct Human{
    sprite sprite;
    enum Movement movType;
    int counter; //general purpose counter
    double orientation;
    int frameCounter; //counter for printing

    //linked list
    Human* next;

    //extenal references:
    struct Spawner* creator;
    //char** objmap;
};

Human* createHuman(int x, int y, struct Spawner* creator); //must provide the two trains, the train will then be chosen using the human's y pos
void destroyHuman(Human* person);
void moveHuman(Human* person);
Human* appendHuman(Human* list, int x, int y, Spawner* creator);

Spawner* createSpawner();
void destroySpawner(Spawner* spawn);
Spawner* initSpawner(int yMin, int yMax, char spawnChar);
void updateSpawner(Spawner* spawn);

#endif //_SPAWNER_H

