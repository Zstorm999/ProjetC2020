#include "include/spawner.h"

Human* createHuman(int x, int y, Spawner* creator){
    debug("entered\n");

    Human* person = (Human*)malloc(sizeof(Human));
    if(!person){
        fprintf(stderr, "Error while allocating Human structure\n");
        return NULL;
    }

    debug("created struct Human\n");

    person->sprite.img = loadSpriteFromFile("data/person.txt");
    setRectDims(&person->sprite.container, x, y, 0, 1, 0, 2);
    person->sprite.color = 'y';
    person->sprite.maskMap = NULL;
    person->sprite.nextSprite = NULL;
    person->sprite.spriteName = L"Bob";

    debug("sprite init\n");

    person->movType = SPAWNING;

    person->next = NULL;

    person->creator = creator;

    debug("end\n");

    return person;
}

void destroyHuman(Human* person){
    free(person);
}


//returns 1 on success, 0 on failure
int tryMove(Human* person, int xtry, int ytry){
    //converting coords 
    int futureX = person->sprite.container.x + xtry;
    int futureY = person->sprite.container.y + ytry + 2;

    char obj = person->creator->objMap[futureY][futureX];

    if(obj != '0' && obj != 'd'){
        debug("Entered\n");

        sprite* Bg = person->creator->bg;
        //Bg->color = 'e';
        Bg->container.xMin = person->sprite.container.x;
        Bg->container.yMin = person->sprite.container.y;
        Bg->container.xMax = person->sprite.container.x + person->sprite.container.xMax;
        Bg->container.yMax = person->sprite.container.y + person->sprite.container.yMax;


        //erasing sprite
        showSprite(Bg, 0);

        person->sprite.container.x += xtry;
        person->sprite.container.y += ytry;

        //showSprite(&person->sprite, 1);

        return 1;
    }

    return 0;
}

void moveHuman(Human* person){
    int next = rand()%100;
    

    switch (person->movType)
    {
    case IDLE: //any idle person has a small chance of starting moving next time
        if(next < 5) //10% chance
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

        person->movType = RANDOM;
        break;

    default:
        break;
    }

}