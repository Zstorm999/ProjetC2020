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

#include "include/displayManager.h"
#include "include/structs.h"

void initDisp()
{
    sprite* Bg= getBackground();
    showSprite(Bg, 0);
}

/**
 * Print a sprite, trimed by the sub coordinates and ignoring the parts defined by its mask map (transparency).
 * In cascade mode, showSprite will recuvively updates the next sprites, coresponding to the next overlaying graphic layers.
 */
void showSprite(sprite* sprite, char cascade)
{
    for(int i=sprite->container.yMin; i<sprite->container.yMax; i++)
    {
        for(int j=sprite->container.xMin; j<sprite->container.xMax; j++)
        {
            if(((sprite->container.y+i)>=0) && ((sprite->container.x+j)>=0))
                if(sprite->maskMap==NULL || sprite->maskMap[i][j]=='0')
                    placec(sprite->container.y+i, sprite->container.x+j, sprite->img[i][j], sprite->color);
        }
    }
    if(cascade==1)
    {
        if(sprite->nextSprite!=NULL)
        {
            int i= 0;
            while(sprite->nextSprite[i]!= NULL)
            {
                showSprite(sprite->nextSprite[i], 1);
                i++;
            }
        }
    }
}

/**
 * Provide a new instance of the background sprite
 */
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
