#include "include/train.h"
#include "include/io.h"
#include "include/structs.h"
#include "include/displayManager.h"

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
        newTrain->spriteTrain.nextSprite= (sprite**)calloc(1, sizeof(sprite*));            //will only be overlayed by the lower train
        newTrain->spriteTrain.spriteName= L"Train Up";
        break;

    case 1:
        newTrain->spriteTrain.container.y = LANE_BOT;
        newTrain->spriteTrain.img= loadSpriteFromFile("data/trainLower.txt");
        newTrain->spriteTrain.maskMap= file2Mask("data/maskTrainLower.txt");
        newTrain->spriteTrain.container.yMax= 6;
        newTrain->spriteTrain.nextSprite= (sprite**)calloc(85, sizeof(sprite*));           //can be overlayed by many things
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
    Train** Trains= calloc(2, sizeof(Train*));
    Trains[0]= train_create(0); //train up
    Trains[1]= train_create(1); //train down
    Trains[0]->spriteTrain.nextSprite[0]= &Trains[1]->spriteTrain;

    //setup the wall obstructions (tunnel partialy hiding the train)
    sprite wallLeft= getBackground();   //get the wall out of the original bg map
    wallLeft.container.xMax= 6;
    wallLeft.container.yMin= 21;
    wallLeft.container.yMax= 26;
    wallLeft.spriteName= L"BG Chunk Wall Left";
    Trains[1]->spriteTrain.nextSprite[0]= &wallLeft;
    sprite wallRight= getBackground();  //get the wall out of the original bg map
    wallRight.container.xMin= 125;
    wallRight.container.yMin= 21;
    wallRight.container.yMax= 26;
    wallRight.spriteName= L"BG Chunk Wall Right";
    Trains[1]->spriteTrain.nextSprite[1]= &wallRight;
    
    showSprite(Trains[0]->spriteTrain, 1);//!!!TO REMOVE
    return Trains;
}