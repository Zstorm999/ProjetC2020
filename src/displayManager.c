#include "include/displayManager.h"

void initDisp()
{
    sprite* Bg= getBackground();
    showSprite(*Bg, 0);
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
        if(sprite.nextSprite!=NULL)
        {
            int i= 0;
            while(sprite.nextSprite[i]!= NULL)
            {
                showSprite(*sprite.nextSprite[i], 1);
                i++;
            }
        }
    }
}

sprite* getBackground()
{
    sprite* Bg = (sprite*)malloc(sizeof(sprite));
    if(!Bg){
        fprintf(stderr, "error while creating background\n");
        return NULL;
    }

    Bg->img= loadSpriteFromFile("data/staticMap.txt");
    setRectDims(&(Bg->container), 0, 0, 0, MAX_COLUMNS, 0, MAX_LINES);

    Bg->maskMap= NULL;
    Bg->color= 'w';
    Bg->nextSprite= NULL;
    Bg->spriteName= L"BG Default";
    return Bg;
}
