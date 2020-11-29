#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdbool.h>
#include "structs.h"

int Global_TrainUpNextStop; //remaining time before up train arrives
int Global_TrainDownNextStop; //remaining time before down train arrives

bool Global_TrainUpIsArrived;
bool Global_TrainDownIsArrived;

char** Global_ObjectMap;

sprite* Global_Background;

#define FRAMERATE 5
#define TICK_INTERVAL 1000000/FRAMERATE

#endif //_GLOBALS_H