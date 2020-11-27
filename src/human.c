#include "include/human.h"

Human* createHuman(int x, int y){
    Human* person = (Human*)malloc(sizeof(Human));
    if(!person){
        fprintf(stderr, "Error while allocating Human structure\n");
        return NULL;
    }

    person->movType = SPAWNING;

    person->sprite.img = loadSpriteFromFile("data/person.txt");
    setRectDims(&person->sprite.container, x, y, 0, 1, 0, 2);
    person->sprite.color = 'y';
    person->sprite.maskMap = NULL;
    person->sprite.nextSprite = NULL;
    person->sprite.spriteName = L"Bob";

}

void destroyHuman(Human* person){
    free(person);
}


//returns 1 on success, 0 on failure
int tryMove(Human* person, int xtry, int ytry){
    return 0;
}

void moveHuman(Human* person){
    int next = rand()%100;

    switch (person->movType)
    {
    case IDLE: //any idle person has a small chance of starting moving next time
        if(next < 20) //20% chance
            person->movType = RANDOM;
        break;

    case RANDOM:
        if(next < 20){ //20% chance going up
            tryMove(person, 0, -1);
        }
        else if(next < 40){ //20% chance going down
            tryMove(person, 0, 1);
        }
        else if(next < 60){ //20% chance going left
            tryMove(person, -1, 0);
        }
        else if(next < 80){ //20% chance going right
            tryMove(person, 1, 0);
        }
        else{ //20% chance going idle
            person->movType = IDLE;
        }
        break;

    case SPAWNING:
    //this is simply trying all 4 directions one at a time...
        if(!tryMove(person, 0, -1))
            if(!tryMove(person, 0, 1))
                if(!tryMove(person, -1, 0))
                    tryMove(person, 1, 0);

    default:
        break;
    }

}