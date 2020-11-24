#include "include/displayManager.h"
#include "include/io.h"
#include <wchar.h>

void showSprite(sprite sprite)
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
    
    int i= 0;
    while(sprite.nextSprite[i]!= NULL)
    {
        showSprite(*sprite.nextSprite[i]);
        i++;
    }
}