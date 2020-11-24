#include "include/train.h"
#include "include/io.h"
#include "include/structs.h"

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
    newTrain->sprite.container.x= BASE_POSX;
    newTrain->sprite.container.xMin= 0;
    newTrain->sprite.container.xMax= TRAIN_SIZE;
    newTrain->sprite.container.yMin= 0;
    newTrain->sprite.color= 'y';

    switch (lane)
    {
    case 0:
        newTrain->sprite.container.y= LANE_TOP;
        newTrain->sprite.img= loadSpriteFromFile("data/trainUpper.txt");
        newTrain->sprite.maskMap= file2Mask("data/maskTrainUpper.txt");
        newTrain->sprite.container.yMax= 8;
        newTrain->sprite.nextSprite= calloc(1, sizeof(sprite*));            //will only be overlayed by the lower train
        break;

    case 1:
        newTrain->sprite.container.y = LANE_BOT;
        newTrain->sprite.img= loadSpriteFromFile("data/trainLower.txt");
        newTrain->sprite.maskMap= file2Mask("data/maskTrainLower.txt");
        newTrain->sprite.container.yMax= 6;
        newTrain->sprite.nextSprite= calloc(85, sizeof(sprite*));           //can be overlayed by many things
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
        free(train->sprite.img[i]);
    }
    free(train->sprite.img);

    free(train);
}


