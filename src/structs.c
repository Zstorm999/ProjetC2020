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