/**
 * - Copyright 01/11/2020
 *
 * This source code is released the GNU GPLv3's policy,
 * thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
 * distribute and/or modify any of part of the project
 * 
 * the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
 * discaim all copyright interest in the program ProjectC2020
 */

#include "include/structs.h"

void setRectDims(Rectangle* rect, int x, int y, int xMin, int xMax, int yMin, int yMax){
    rect->x = x;
    rect->y = y;
    rect->xMin = xMin;
    rect->xMax = xMax;
    rect->yMin = yMin;
    rect->yMax = yMax;
}

sprite* appendSprite(sprite* list, sprite* ptr){
    if(list == NULL) return ptr;
    list->nextSprite[0] = appendSprite(list->nextSprite[0], ptr);
    return list;
}

sprite* getLastSprite(sprite* list){
    if(list == NULL) return NULL;
    if(list->nextSprite[0] == NULL){
        return list;
    }
    return getLastSprite(list->nextSprite[0]);
}