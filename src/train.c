#include "include/train.h"

Train* train_create(char* file, int lane){
    //allocating memory space
    Train* newTrain = (Train*)malloc(sizeof(Train));
    if(!newTrain){
        fprintf(stderr, "Error while allocating Train struct\n");
        return NULL;
    }

    newTrain->sprite = loadSpriteFromFile(file);
    newTrain->velocity = 0;
    newTrain->visible = false;
    newTrain->xPos = 0;

    //positionning on correct yPos 
    switch (lane)
    {
    case 0:
        newTrain->yPos = LANE_TOP;
        break;

    case 1:
        newTrain->yPos = LANE_BOT;
        break;

    default:
        newTrain->yPos =0;
        break;
    }

    return newTrain;
}

void train_destroy(Train* train){
    for(int i=0; i<MAX_LINES; i++){
        free(train->sprite[i]);
    }
    free(train->sprite);

    free(train);
}


