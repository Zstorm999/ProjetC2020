#include "include/human.h"

Human* createHuman(int x, int y){
    Human* person = (Human*)malloc(sizeof(Human));
    if(!person){
        fprintf(stderr, "Error while allocating Human structure\n");
        return NULL;
    }

    person->movType = IDLE;
    person->posX = 0;
    person->posY = 0;
    person->sprite = NULL;
}

void destroyHuman(Human* person){
    free(person);
}

int assignSpritetoHuman(Human* person, char** sprite){
    if(sprite == NULL){
        fprintf(stderr, "Error, sprite is NULL\n");
        return 0;
    }

    person->sprite = sprite;
    return 1;
}

