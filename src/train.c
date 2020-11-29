#include "include/train.h"
#include "include/io.h"
#include "include/structs.h"
#include "include/displayManager.h"
#include <stdlib.h>
#include <wchar.h>
#include "include/globals.h"
#include "string.h"

/**
*movements:
*   UpperTrain: <-----------
*   LowerTrain: ----------->
*/

Train* train_create(int lane)
{
    //allocating memory space
    Train* newTrain = (Train*)malloc(sizeof(Train));
    if(!newTrain){
        fprintf(stderr, "Error while allocating Train struct\n");
        return NULL;
    }

    newTrain->velocity= 0;
    newTrain->visible= true;
    newTrain->arrived= false;
    newTrain->updatesBeforeArrival= FRAMERATE* (int)(40.0+(60*(rand()/RAND_MAX)));
    newTrain->spriteTrain.container.x= BASE_POSX;
    newTrain->spriteTrain.container.xMin= 0;
    newTrain->spriteTrain.container.xMax= TRAIN_SIZE;
    newTrain->spriteTrain.container.yMin= 0;
    newTrain->spriteTrain.color= 'y';
    newTrain->toUpdateFirst= NULL;

    switch (lane)
    {
    case 0:
        newTrain->spriteTrain.container.y= LANE_TOP;
        newTrain->spriteTrain.img= loadSpriteFromFile("data/trainUpper.txt");
        newTrain->spriteTrain.maskMap= file2Mask("data/maskTrainUpper.txt");
        newTrain->spriteTrain.container.yMax= 8;
        newTrain->spriteTrain.nextSprite= (sprite**)calloc(2, sizeof(sprite*));            //will only be overlayed by the lower train
        newTrain->toUpdateFirst= (sprite**)calloc(MAX_ELEM_ON_ROW+1, sizeof(sprite*));
        newTrain->spriteTrain.spriteName= L"Train Up";
        break;

    case 1:
        newTrain->spriteTrain.container.y = LANE_BOT;
        newTrain->spriteTrain.img= loadSpriteFromFile("data/trainLower.txt");
        newTrain->spriteTrain.maskMap= file2Mask("data/maskTrainLower.txt");
        newTrain->spriteTrain.container.yMax= 6;
        newTrain->spriteTrain.nextSprite= (sprite**)calloc(MAX_ELEM_ON_ROW+1, sizeof(sprite*));           //can be overlayed by many things
        newTrain->toUpdateFirst= (sprite**)calloc(3, sizeof(sprite*));                                      //overlap upper train and ground
        newTrain->spriteTrain.spriteName= L"Train Down";
        break;

    default:
        fprintf(stderr, "Error: %d is not a valid lane number", lane);
        return NULL;
        break;
    }

    return newTrain;
}

void train_destroy(Train* train)
{
    for(int i=0; i<MAX_LINES; i++)
    {
        free(train->spriteTrain.img[i]);
    }
    free(train->spriteTrain.img);

    free(train);
}

Train** initTrains()
{
    Train** Trains= (Train**)calloc(2, sizeof(Train*));
    Trains[0]= train_create(0); //train up
    Trains[1]= train_create(1); //train down
    Trains[0]->spriteTrain.nextSprite[0]= &Trains[1]->spriteTrain;

    //every pieces required to rebuild the background after a move
    Trains[0]->toUpdateFirst[0]= getBackground();
    Trains[0]->toUpdateFirst[0]->container.yMin= LANE_TOP;
    Trains[0]->toUpdateFirst[0]->container.yMax= LANE_TOP+8;
    Trains[1]->toUpdateFirst[0]= getBackground();
    Trains[1]->toUpdateFirst[0]->container.yMin= LANE_BOT;
    Trains[1]->toUpdateFirst[0]->container.yMax= LANE_BOT+6;
    sprite* rebuildUpperTrain= (sprite*)malloc(sizeof(sprite));
    memcpy(rebuildUpperTrain, &Trains[0]->spriteTrain, sizeof(sprite));
    rebuildUpperTrain->container.yMin= 4;
    Trains[1]->toUpdateFirst[1]= rebuildUpperTrain;
    Trains[1]->misc= &Trains[0]->spriteTrain.container.x;


    //setup the wall obstructions (tunnel partialy hiding the train)
    sprite* wallLeft= getBackground();   //get the wall out of the original bg map
    wallLeft->container.xMax= 7;
    wallLeft->container.yMin= 21;
    wallLeft->container.yMax= 26;
    wallLeft->spriteName= L"BG Chunk Wall Left";
    Trains[1]->spriteTrain.nextSprite[0]= wallLeft;
    sprite* wallRight= getBackground();  //get the wall out of the original bg map
    wallRight->container.xMin= 124;
    wallRight->container.yMin= 21;
    wallRight->container.yMax= 26;
    wallRight->spriteName= L"BG Chunk Wall Right";
    Trains[1]->spriteTrain.nextSprite[1]= wallRight;

    return Trains;
}

void moveUpperTrain(Train* train)
{
    if(train->visible)
    {
        //SETUP:
        train->toUpdateFirst[0]->container.xMin= train->spriteTrain.container.x+TRAIN_SIZE-4;
        train->toUpdateFirst[0]->container.xMax= train->spriteTrain.container.x+TRAIN_SIZE-train->velocity;

        train->spriteTrain.container.x+= train->velocity;
        
        //CONCLUDE & DISPLAY:
        if(train->spriteTrain.container.x < -(TRAIN_SIZE+train->velocity+1))
            train->visible= false;
        else
        {
            int i= 0;
            while(train->toUpdateFirst[i]!=NULL) //will print a chunck of the terrain at the back of the train an then the travelers
            {
                showSprite(train->toUpdateFirst[i], 0);
                i++;
            }
            showSprite(&train->spriteTrain, 1);
        }
    }
}

void moveLowerTrain(Train* train)
{
    if(train->visible)
    {
        //SETUP:
        train->toUpdateFirst[0]->container.xMin= train->spriteTrain.container.x; //bg map
        train->toUpdateFirst[0]->container.xMax= train->spriteTrain.container.x+4;

        int xUppTrain= *(train->misc); //*train->misc is the x coordinate of the upper train (initialised in "initTrains()")
        train->toUpdateFirst[1]->container.x= xUppTrain;
        train->toUpdateFirst[1]->container.xMin= train->spriteTrain.container.x-xUppTrain-train->velocity; //bg train
        train->toUpdateFirst[1]->container.xMax= train->spriteTrain.container.x-xUppTrain+4;

        train->spriteTrain.container.x+= train->velocity;
        if(train->spriteTrain.container.x+TRAIN_SIZE > MAP_WIDTH) //trim train past the end of the right tunnel
            train->spriteTrain.container.xMax-= train->velocity;

        //CONCLUDE & DISPLAY:
        if(train->spriteTrain.container.x > (MAP_WIDTH - train->velocity))
        {
            train->visible= false;
        }            
        else
        {
            showSprite(train->toUpdateFirst[0], 0); //print a chunck of terrain at the back of the train
            if(abs(xUppTrain - train->spriteTrain.container.x) < TRAIN_SIZE)
            {
                showSprite(train->toUpdateFirst[1], 0); //print a chunck of the other train at the back of the train
            }
            showSprite(&train->spriteTrain, 1);
        }
    }
}