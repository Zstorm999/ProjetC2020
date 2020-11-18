typedef struct rectangle
{                   //exemple:          x                               0   xMin       xMax
    int x;          //         +--------+--------+-------------> X    0 +----+----------+--+    "xMin, xMax, yMin, yMax" are selecting an area
    int y;          //         |        '                               |                  |    in the rectangle, relative to x, y
    int yMin;       //       y + ---    +--------+                 yMin +    +----------+  |
    int yMax;       //         |        |  rect  |                      |    |          |  |
    int xMin;       //         |        +--------+                 yMax +    +----------+  |
    int xMax;       //         V                                        +------------------+
} rectangle;        //         Y

typedef struct sprite
{
    rectangle container; //the sprite will be located at container.x, y, but displayed only for the selected area (cf rectangle)
    char** img;
    char** maskMap;
    struct sprite** nextSprite; //while rendering a sprite, we must make sure to render every sprites that are overlaying it
} sprite;
