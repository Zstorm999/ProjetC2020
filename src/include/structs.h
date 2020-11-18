typedef struct rectangle
{                   //exemple:          x                               0   xMin       xMax
    int x;          //         +--------+--------+-------------> X    0 +----+----------+--+    "xMin, xMax, yMin, yMax" are meant to select an area
    int y;          //         |        '                               |                  |    in the rectangle, relative to x, y
    int yMin;       //       y + ---    +--------+                 yMin +    +----------+  |
    int yMax;       //         |        |  rect  |                      |    |          |  |
    int xMin;       //         |        +--------+                 yMax +    +----------+  |
    int xMax;       //         V                                        +------------------+
} rectangle;        //         Y

typedef struct sprite
{
    rectangle container;
    char** img;
    char** maskMap;
    struct sprite* nextSprite;
} sprite;