#include "include/spawner.h"

//point list management

_pointL* _pointLCreate(int x, int y){
    _pointL* point = (_pointL*)malloc(sizeof(_pointL));
    if(!point){
        fprintf(stderr, "Error in points linked list allocation\n");
        return NULL;
    }

    point->x = x;
    point->y = y;
    point->next = NULL;


    return point;
}

_pointL* _pointLAppend(_pointL* list, int x, int y){
    if(list == NULL) 
        return _pointLCreate(x, y);
    else{
        list->next = _pointLAppend(list->next, x, y);
        return list;
    }
}

void _pointLClear(_pointL* list){
    if(list == NULL) return;
    if(list->next != NULL){
        _pointLClear(list->next);     
    }
    free(list);
}

//------------------------------------------------------------------------------
//spawner management

Spawner* createSpawner(){
    Spawner* spawn = (Spawner*)malloc(sizeof(Spawner));
    if(!spawn){
        fprintf(stderr, "Unable to allocate memory for spawner");
        return NULL;
    }

    spawn->personList = NULL;
    spawn->nbPersons = 0;
    spawn->spawnPoints = NULL;
    spawn->nbSPoints = 0;
    spawn->objMap = NULL;
    spawn->bg = NULL;

    spawn->nextSpawnCounter = 5;
    spawn->containsPlayer = false;

    return spawn;
}

void destroySpawner(Spawner* spawn){
    //TODO : destroy linked list for persons

    _pointLClear(spawn->spawnPoints);

    for(int i=0; i<MAX_LINES; i++){
        free(spawn->objMap[i]);
    }
    free(spawn->objMap);

    //TODO: implement a function to deallocate sprite

    free(spawn);
}

Spawner* initSpawner(int yMin, int yMax, char spawnChar, bool containsPlayer){

    Spawner* spawn = createSpawner();
    if(!spawn){
        return NULL;
    }

    spawn->bg = getBackground();
    spawn->objMap = loadObjectMap("data/objMap.txt");

    spawn->renderArray = (sprite**)calloc(yMax - yMin, sizeof(sprite*));
    if(!spawn->renderArray){
        fprintf(stderr, "Error while allocating render array\n");
        return NULL;
    }

    spawn->yMin = yMin;
    spawn->yMax = yMax;

    //loading spawner position
    for(int i=yMin; i<yMax; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            //if spawnable tile, we add it to the list
            if(spawn->objMap[i][j] == spawnChar){
                spawn->spawnPoints =  _pointLAppend(spawn->spawnPoints, j, i);
                spawn->nbSPoints++;

                char msg[100];
                sprintf(msg, "%d\n", i);
                debug(msg);
            }
        }
    }

    //always spawn a human at the first found spawnPoint (y is -1 cause sprite position and real position differ)
    spawn->personList = createHuman((spawn->spawnPoints->x) , (spawn->spawnPoints->y) - 2, spawn);

    spawn->containsPlayer = containsPlayer;
    if(containsPlayer){
        spawn->personList = appendHuman(spawn->personList, (spawn->spawnPoints->next->x) , (spawn->spawnPoints->next->y) - 2, spawn);
        spawn->personList->next->movType = PLAYER;
        spawn->personList->next->sprite.color = 'r';
    }

    return spawn;
}

//apply moveHuman to all Humans currently used by spawner  
void updateSpawner(Spawner* spawn, PlayerInput input){
    //if for whatever reason the spawner is non existent, just drop (this happens when no humans are used)

    debug("Point 1\n");

    if(spawn == NULL) return;
    Human* list = spawn->personList;


    for(int i = spawn->yMin; i<spawn->yMax; i++){
        spawn->renderArray[i - spawn->yMin] = NULL;
    }

    debug("POint 2\n");

    while (list != NULL)
    {
        debug("2.a ");
        list->sprite.nextSprite[0] = NULL; //resetting cascade

        debug("2.b ");

        moveHuman(list, input);

        debug("2.c ");

        //adding the sprite in the array
        int realY = list->sprite.container.y - spawn->yMin;

        debug("2.d ");
        char msg[100];
        sprintf(msg, "%d %d %d ", list->sprite.container.y, spawn->yMin, realY);
        debug(msg);

        spawn->renderArray[realY] =  appendSprite(spawn->renderArray[realY], &list->sprite);

        debug("2.e ");

        list = list->next;

        debug("2.f\n");
    }
    
    debug("Point 3\n");

    if(spawn->nextSpawnCounter == 0  && spawn->nbPersons < MAX_HUMANS){
        int nbp = spawn->nbSPoints;
        int pos = rand()%nbp;
        _pointL* list = spawn->spawnPoints;

        for(int i=0; i < pos; i++){
            //there should be absolutely no problem here, since linked list is static (I miss vector from C++... T_T )
            list = list->next;
        }

        spawn->personList = appendHuman(spawn->personList, list->x , list->y -2 , spawn);
        spawn->nbPersons++;

        spawn->nextSpawnCounter = FRAMERATE/2  + rand()%(2*FRAMERATE); //spaw between 0.5 and 2.5 sec later
    }
    else if(spawn->nbPersons < MAX_HUMANS){
            spawn->nextSpawnCounter--;
    }

    debug("Point 4\n");

    //rendering sprites
    for(int i = spawn->yMin; i<spawn->yMax; i++){
        if(spawn->renderArray[i - spawn->yMin] != NULL){
            showSprite(spawn->renderArray[i-spawn->yMin], 1);
        }
    }

    debug("Point 5\n");
    
}
