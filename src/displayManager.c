#include "include/displayManager.h"
#include "include/io.h"

void init()
{

}

void showSprite(sprite sprite){
    for(int i=sprite.container.yMin; i<sprite.container.yMax; i++){
        for(int j=sprite.container.xMin; j<sprite.container.xMax; j++){
            //printf("%c", sprite.img[i][j]);                                       //work
            placec(sprite.container.x+i ,sprite.container.y+j , sprite.img[i][j]);  //almost work
        }
    }
}