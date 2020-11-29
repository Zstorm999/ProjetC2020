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

int setUpdateCountBeforeNextArrival()
{
    return FRAMERATE*(MININTERVALTRAIN+(rand()%(MAXINTERVALTRAIN-MININTERVALTRAIN)));
}

Train* train_create(int lane)
{
    //allocating memory space
    Train* newTrain = (Train*)malloc(sizeof(Train));
    if(!newTrain){
        fprintf(stderr, "Error while allocating Train struct\n");
        return NULL;
    }

    newTrain->velocity= 0;
    newTrain->visible= false;
    newTrain->arrived= false;
    
    newTrain->updatesBeforeArrival= setUpdateCountBeforeNextArrival()/2;

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
        train->toUpdateFirst[0]->container.xMin= (train->spriteTrain.container.x+TRAIN_SIZE-5)+train->velocity; //piece of terrain
        train->toUpdateFirst[0]->container.xMax= train->spriteTrain.container.x+TRAIN_SIZE-train->velocity;

        train->spriteTrain.container.x+= train->velocity;
        if(train->spriteTrain.container.x > 0)
            train->spriteTrain.container.xMax= MAP_WIDTH-train->spriteTrain.container.x;

        //CONCLUDE & DISPLAY:
        if(train->spriteTrain.container.x < -(TRAIN_SIZE-train->velocity+1))
            train->visible= false;
        else
        {
            int i= 0;
            while(train->toUpdateFirst[i] != NULL && train->spriteTrain.container.x < MAP_WIDTH-TRAIN_SIZE-train->velocity) //will print a chunck of the terrain at the back of the train an then the travelers
            {
                showSprite(train->toUpdateFirst[i], 0);
                i++;
            }
            showSprite(&train->spriteTrain, 1);
        }
    }
    placec(45, 0, L'\0', 'r'); wprintf(L"posx: %d  ", train->spriteTrain.container.x);
}

void moveLowerTrain(Train* train)
{
    if(train->visible)
    {
        //SETUP:
        train->toUpdateFirst[0]->container.xMin= train->spriteTrain.container.x; //piece of terrain
        train->toUpdateFirst[0]->container.xMax= train->spriteTrain.container.x+4+train->velocity;

        int xUppTrain= *(train->misc); //*train->misc is the x coordinate of the upper train (initialised in "initTrains()")
        train->toUpdateFirst[1]->container.x= xUppTrain;
        train->toUpdateFirst[1]->container.xMin= train->spriteTrain.container.x-xUppTrain-train->velocity; //bg train
        train->toUpdateFirst[1]->container.xMax= train->spriteTrain.container.x-xUppTrain+5+train->velocity;

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

/**
 * Wait for the train to arrive (count down using "updateBeforeArrival"),
 * if the train is arrived, the countown is frozen at -1, the train apear will move each update until it reach the dead stop. 
 * The counter will then count down the time of stop using the interval ]-1 : -FRAMERATE*(HALT_TIME)-1] and it will be notified that the train is arrived.
 * The count down will be reseted like if an other train were to come, "arrived" will be reverted to "false",
 * and the the train will accelerate in the other way to leave the screen.
 */
void updateTrainUp(Train* tr)
{
    //Arrival at the station: 
    if(tr->updatesBeforeArrival==0)
    {
        tr->updatesBeforeArrival= -1;
        tr->visible= true;
        tr->spriteTrain.container.x= MAP_WIDTH;
        tr->velocity= -4;
    }
    else if(tr->updatesBeforeArrival== -1 && !tr->arrived)
    {
        //slow down
        if (40 < tr->spriteTrain.container.x && tr->spriteTrain.container.x < 70)
            tr->velocity= -3;
        else if (30 < tr->spriteTrain.container.x && tr->spriteTrain.container.x < 40)
            tr->velocity= -2;     
        else if (22< tr->spriteTrain.container.x && tr->spriteTrain.container.x < 30) 
            tr->velocity= -1;
        else if (tr->spriteTrain.container.x<22) //will move every other update
        {
            if (tr->clkComute)
            {
                tr->velocity= -1;
                tr->clkComute= false;
            }
            else
            {
                tr->velocity= 0;
                tr->clkComute= true;
            }
        }

        //apply move
        moveUpperTrain(tr);
        if (tr->spriteTrain.container.x== 12)   //12 (30-18) is the stop positing of the upper train
            tr->arrived= true;
    }

    //Stay still at the station:
    if (tr->arrived)
    {
        tr->updatesBeforeArrival--;
        if (tr->updatesBeforeArrival== -FRAMERATE*(HALT_TIME)-1)
        {
            tr->arrived= false;
            tr->updatesBeforeArrival= setUpdateCountBeforeNextArrival();
        }
    }

    //Leave the station:
    if (!tr->arrived && tr->updatesBeforeArrival!= 0 && tr->updatesBeforeArrival!= -1 && tr->visible)
    {
        //accelerate
        if ( 2 < tr->spriteTrain.container.x)
        {
            if (tr->clkComute)
            {
                tr->velocity= -1;
                tr->clkComute= false;
            }
            else
            {
                tr->velocity= 0;
                tr->clkComute= true;
            }
        }
        else if (-15 < tr->spriteTrain.container.x && tr->spriteTrain.container.x < 2)
            tr->velocity= -1;     
        else if (-40 < tr->spriteTrain.container.x && tr->spriteTrain.container.x < -15) 
            tr->velocity= -2;
        else if (tr->spriteTrain.container.x < -65)
            tr->velocity= -3;


        //apply move
        moveUpperTrain(tr);
        tr->updatesBeforeArrival--;
    }

    placec(45, 0, L'\0', 'r'); wprintf(L"time: %d      ", tr->updatesBeforeArrival/FRAMERATE); //debug

    //not in the station:
    if(!tr->visible)
        tr->updatesBeforeArrival--;
}