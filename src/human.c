<<<<<<< Updated upstream
#include "include/human.h"
=======
#include "include/spawner.h"

Human* createHuman(int x, int y, Spawner* creator){
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
=======

    person->movType = SPAWNING;
    person->next = NULL;
    person->creator = creator;

    //we need at least 1 for counter to work
    person->counter = 1 + (rand()%100);
    person->orientation = 0;
    person->frameCounter = 0;

    return person;
>>>>>>> Stashed changes
}

void destroyHuman(Human* person){
    free(person);
}

Human* appendHuman(Human* list, int x, int y, Spawner* creator){
    if(list == NULL) 
        return createHuman(x, y, creator);
    else{
        list->next = appendHuman(list->next, x, y, creator);
        return list;
    }
}


//returns 1 on success, 0 on failure
int tryMove(Human* person, int xtry, int ytry){
    //converting coords 
    int futureX = person->sprite.container.x + xtry;
    int futureY = person->sprite.container.y + ytry + 2;

    char obj = Global_ObjectMap[futureY][futureX];
    char msg[100];
    sprintf(msg, " : %d\n", obj);
    debug(msg);

    if(obj != '0' && obj != 'd'){
<<<<<<< Updated upstream
        debug("Entered\n");
=======

        sprite* Bg = person->creator->bg;
        //Bg->color = 'e';
        Bg->container.xMin = person->sprite.container.x;
        Bg->container.yMin = person->sprite.container.y;
        Bg->container.xMax = person->sprite.container.x + person->sprite.container.xMax;
        Bg->container.yMax = person->sprite.container.y + person->sprite.container.yMax;


        //erasing sprite
        showSprite(Bg, 0);

>>>>>>> Stashed changes
        person->sprite.container.x += xtry;
        person->sprite.container.y += ytry;

        return 1;
    }

    return 0;
}

void moveHuman(Human* person){
    int next = rand()%100;
<<<<<<< Updated upstream
    char msg[100];
    sprintf(msg, "%d : %d %d\n", next, person->sprite.container.x, person->sprite.container.y);
    debug(msg);
=======


    if(person->frameCounter != 0){
        person->frameCounter--;
        return;
    }
    //frameCounter is 0;
    person->frameCounter = 3;
    //since humans have the same framerate, but different spawning frame, this will result in them moving differently (up to 5 different movement)
>>>>>>> Stashed changes

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

        person->movType = RANDOM;
        break;

    default:
        break;
    }

}