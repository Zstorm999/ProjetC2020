#include "include/displayManager.h"
#include "include/io.h"

void init()
{

}

void showSprite(sprite sprite){
    for(int i=sprite.container.yMin; i<sprite.container.yMax; i++)
    {
        for(int j=sprite.container.xMin; j<sprite.container.xMax; j++)
        {
            //printf("%c", sprite.img[i][j]);                                           //work
            if(((sprite.container.y+i)>=0) && ((sprite.container.x+j)>=0))
                placec(sprite.container.y+i, sprite.container.x+j, sprite.img[i][j]);   //almost work
        }
    }
}