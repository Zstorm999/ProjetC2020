#include "include/spawner.h"

Human* createHuman(int x, int y, Spawner* creator){

    Human* person = (Human*)malloc(sizeof(Human));
    if(!person){
        fprintf(stderr, "Error while allocating Human structure\n");
        return NULL;
    }

    person->sprite.img = loadSpriteFromFile("data/person.txt");
    setRectDims(&person->sprite.container, x, y, 0, 1, 0, 2);
    person->sprite.color = 'y';
    person->sprite.maskMap = NULL;
    person->sprite.nextSprite = (sprite**)calloc(1, sizeof(sprite*));
    if(!person->sprite.nextSprite){
        fprintf(stderr, "Unable to allocate memory for next sprite array");
        return NULL;
    }

    person->sprite.spriteName = L"Bob";


    person->movType = SPAWNING;
    person->next = NULL;
    person->creator = creator;

    //we need at least 1 for counter to work
    person->counter = 10 + (rand()%90);
    person->orientation = 0;


    return person;
}

void destroyHuman(Human* person){
    if(person == NULL) return;

    destroySprite(person->sprite.img);

    destroyHuman(person->next);
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

Human* findPreviousHuman(Human* list, Human* ptr){
    if(list == NULL) return NULL;
    if(list->next == ptr) return list;
    return findPreviousHuman(list->next, ptr);
}

void removeHumanFromList(Human* person){
    Human* previous = findPreviousHuman(person->creator->personList, person);
    //previous can be NULL if Human is not in the list(which can never happen), or if person is the first element of the list
    if(previous != NULL){
        if(previous->next != person){return;}
        previous->next = person->next;
    }
    else if(person == person->creator->personList){
        person->creator->personList = person->next;
    }
    //at this point person is effectively removed from the list

    sprite* Bg = person->creator->bg;
    //Bg->color = 'e';
    Bg->container.xMin = person->sprite.container.x;
    Bg->container.yMin = person->sprite.container.y;
    Bg->container.xMax = person->sprite.container.x + person->sprite.container.xMax;
    Bg->container.yMax = person->sprite.container.y + person->sprite.container.yMax;

    //erasing sprite
    showSprite(Bg, 0);

    person->next = NULL;
    person->creator->nbPersons--;

    destroyHuman(person);
}

//we need this so that we update the list in reverse order
void updateAllHumans(Human* list, PlayerInput input){
    if(list == NULL) return;
    updateAllHumans(list->next, input);

    list->sprite.nextSprite[0] = NULL; //resetting cascade


    if(moveHuman(list, input)){

        //adding the sprite in the array
        Spawner* spawn = list->creator;
        int realY = list->sprite.container.y - spawn->yMin;
        spawn->renderArray[realY] =  appendSprite(spawn->renderArray[realY], &list->sprite);
    }

}

//returns 1 on success, 0 on failure
int tryMove(Human* person, double angle){
    person->orientation += angle;

    int xtry = round(cos(person->orientation));
    int ytry = round(sin(person->orientation));

    //converting coords 
    int futureX = person->sprite.container.x + xtry;
    int futureY = person->sprite.container.y + ytry + 2;

    char obj = person->creator->objMap[futureY][futureX];

    if(obj != '0' && obj != 'd'){

        sprite* Bg = person->creator->bg;
        Bg->container.xMin = person->sprite.container.x;
        Bg->container.yMin = person->sprite.container.y;
        Bg->container.xMax = person->sprite.container.x + person->sprite.container.xMax;
        Bg->container.yMax = person->sprite.container.y + person->sprite.container.yMax;


        //erasing sprite
        showSprite(Bg, 0);

        person->sprite.container.x += xtry;
        person->sprite.container.y += ytry;


        return 1;
    }

    return 0;
}

//returns 0 if Human was destroyed in the process
int moveHuman(Human* person, PlayerInput input){
    int next = rand()%100;

    if(person->movType != PLAYER){
        char obj = person->creator->objMap[person->sprite.container.y+2 ][person->sprite.container.x];
        if(obj == 'S'){
            removeHumanFromList(person);
            return 0;
        }

        if(obj == 'M' && person->creator->train->arrived){
            removeHumanFromList(person);
            return 0;
        }
        
        if(person->creator->train->arrived){
            if(person->movType == RANDOM || person->movType == IDLE || person->movType == SPAWNING){
                if(next < 70){ //70% chance they want to take the train
                    person->movType = EMBARQUING;
                }
            }
        }
        else{
            if(person->movType == EMBARQUING){
                person->movType = RANDOM;
            }
        }
    }


    switch (person->movType)
    {
    case IDLE: //any idle person has a small chance of starting moving next time
        if(next < 5) //10% chance
            person->movType = RANDOM;
        break;

    case RANDOM:
        if(next < 35){ //35% chance forward
            tryMove(person, 0);
        }
        else if(next < 55){ //20% chance up 45deg
            tryMove(person, PI/4);
        }
        else if(next < 75){ //20% chance down 45deg
            tryMove(person, -PI/4);
        }
        else if(next < 81){ //6% chance up 90deg
            tryMove(person, PI/2);
        }
        else if(next < 87){ //6% chance down 90deg
            tryMove(person, -PI/2); 
        }
        else if(next < 90){ //3% chance up 135deg
            tryMove(person, 3*PI/4);
        }
        else if(next < 94){ //3% chance down 135deg
            tryMove(person, -3*PI/4);
        }
        else if(next < 96){ //2% chance going backward
            tryMove(person, PI);
        }
        else{ // 4% chance going idle
            person->movType = IDLE;
        }
        break;

    case SPAWNING:
    //when spawning, humans wills always go on a straight line for some time

        if(!tryMove(person, 0)){
            if(next < 50){//50% chance turning right or left
                if(!tryMove(person, -PI/2))
                    tryMove(person, PI);
            }
            else{
                if(!tryMove(person, PI/2))
                    tryMove(person, PI);
            }
        }

        person->counter--;
        if(person->counter == 0){
            person->movType = RANDOM;
        }
        break;
    
    case PLAYER:
        if(input == NONE) break;

        if(input == UP) person->orientation = PI/2;
        if(input == DOWN) person->orientation = -PI/2;
        if(input == LEFT) person->orientation = PI;
        if(input == RIGHT) person->orientation = 0;
        tryMove(person, 0);
        break;

    case EMBARQUING:
        {
            double targetX;
            double targetY = (person->sprite.container.y > 23)?25:16;

            double x = (double)person->sprite.container.x;
            double y = (double)person->sprite.container.y;

            if(x < 46){
                targetX = 33.f;

            }
            else if(x < 68){
                targetX = 57.f;

            }
            else if(x < 89){
                targetX = 78.f;

            }
            else{
                targetX = 100.f;
            }

            double targetAngle;
            if(x != targetX){
                targetAngle = atan((y-targetY)/(x-targetX));
            }
            else{
                targetAngle = (person->sprite.container.y > 23)?(PI/2):(-PI/2);
            }

            person->orientation = targetAngle;
            tryMove(person, 0);
            break;
        }

    default:
        break;
    }

    return 1;

}

