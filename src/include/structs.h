#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <wchar.h>

typedef struct Rectangle
{                   //exemple:          x                               0   xMin       xMax
    int x;          //         +--------+--------+-------------> X    0 +----+----------+--+    "xMin, xMax, yMin, yMax" are selecting an area
    int y;          //         |        '                               |                  |    in the rectangle, relative to x, y
    int yMin;       //       y + ---    +--------+                 yMin +    +----------+  |
    int yMax;       //         |        |  rect  |                      |    |          |  |
    int xMin;       //         |        +--------+                 yMax +    +----------+  |
    int xMax;       //         V                                        +------------------+
} Rectangle;        //         Y

typedef struct sprite
{
    Rectangle container;        //the sprite will be located at container.x, y, but displayed only for the selected area (cf rectangle)
    wchar_t** img;
    char color;
    char** maskMap;
    struct sprite** nextSprite; //while rendering a sprite, we must make sure to render every sprites that are overlaying it
    wchar_t* spriteName;        //mainly for debuging purpose
} sprite;

void setRectDims(Rectangle* rect, int x, int y, int xMin, int xMax, int yMin, int yMax); 
sprite* appendSprite(sprite* list, sprite* ptr);
sprite* getLastSprite(sprite* list);

#endif //_STRUCT_H