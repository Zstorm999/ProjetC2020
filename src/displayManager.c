#include "include/displayManager.h"
#include "include/io.h"
#include <stdlib.h>
#include <wchar.h>

sprite initDisp()
{
    sprite Bg;
    Bg.img= loadSpriteFromFile("data/staticMap.txt");
    Bg.container.x= Bg.container.y= Bg.container.xMin= Bg.container.yMin= 0;
    Bg.container.xMax= MAX_COLUMNS;
    Bg.container.yMax= MAX_LINES;
    Bg.maskMap= NULL;
    Bg.color= 'w';
    Bg.nextSprite= calloc(1, sizeof(sprite*));
    showSprite(Bg, 0);
    return Bg;
}

void showSprite(sprite sprite, char cascade)
{
    for(int i=sprite.container.yMin; i<sprite.container.yMax; i++)
    {
        for(int j=sprite.container.xMin; j<sprite.container.xMax; j++)
        {
            if(((sprite.container.y+i)>=0) && ((sprite.container.x+j)>=0))
                if(sprite.maskMap==NULL || sprite.maskMap[i][j]=='0')
                    placec(sprite.container.y+i, sprite.container.x+j, sprite.img[i][j], sprite.color);
        }
    }
    
    if(cascade==1)
    {
        int i= 0;
        while(sprite.nextSprite[i]!= 0)
        {
            showSprite(*sprite.nextSprite[i], 1);
            i++;
        }
    }
}