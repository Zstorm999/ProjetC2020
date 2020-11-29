#ifndef _DISPLAYMANAGER_H
#define _DISPLAYMANAGER_H

#include "io.h"
#include "structs.h"
#include <stdlib.h>
#include <wchar.h>

#define MAX_ELEM_ON_ROW 85

void initDisp();
void showSprite(sprite* sprite, char cascade); //display a sprite, trimed and colored, and updates the dependencies if cascade is set to 1
sprite* getBackground();

#endif //_DISPLAYMANAGER_H