#ifndef _DISPLAYMANAGER_H
#define _DISPLAYMANAGER_H

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"


void initDisp();
void showSprite(sprite sprite, char cascade); //display a sprite, trimed and colored, and updates the dependencies if cascade is set to 1
sprite getBackground();

#endif //_DISPLAYMANAGER_H