/**
 * - Copyright 01/11/2020
 *
 * This source code is released the GNU GPLv3's policy,
 * thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
 * distribute and/or modify any of part of the project
 * 
 * the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
 * disclaim all copyright interest in the program ProjectC2020
 */

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