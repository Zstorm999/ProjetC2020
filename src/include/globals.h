#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <stdbool.h>

extern int Global_TrainUpNextStop; //remaining time before up train arrives
extern int Global_TrainDownNextStop; //remaining time before down train arrives

extern bool Global_TrainUpIsArrived;
extern bool Global_TrainDownIsArrived;

extern char** Global_ObjectMap;

#define FRAMERATE 5
#define TICK_INTERVAL 1000000/FRAMERATE

#endif //_GLOBALS_H