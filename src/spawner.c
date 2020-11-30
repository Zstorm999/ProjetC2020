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

    spawn->yMin = 0;
    spawn->yMax = 0;

    spawn->nextSpawnCounter = 6;

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

Spawner* initSpawner(int yMin, int yMax, char spawnChar){
    Spawner* spawn = createSpawner();
    if(!spawn){
        return NULL;
    }

    spawn->bg = getBackground();
    spawn->objMap = loadObjectMap("data/objMap.txt");
    spawn->yMin = yMin;
    spawn->yMax = yMax;

    spawn->renderArray = (sprite**)calloc(yMax - yMin ,sizeof(sprite*));
    if(!spawn->renderArray){
        fprintf(stderr, "Error while creating render array");
        return NULL;
    }


    //loading spawner position
    for(int i=yMin; i<yMax; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            //if spawnable tile, we add it to the list
            if(spawn->objMap[i][j] == spawnChar){
                spawn->spawnPoints =  _pointLAppend(spawn->spawnPoints, i, j);
                spawn->nbSPoints++;
            }
        }
    }

    /*char msg[100];
    sprintf(msg, "%d\n", spawn->nbSPoints);
    debug(msg);*/

    //always spawn a human at the first found spawnPoint (y is -1 cause sprite position and real position differ)
    spawn->personList = createHuman((spawn->spawnPoints->x) - 3 , (spawn->spawnPoints->y) + 2 , spawn);
    spawn->nbPersons++;

    return spawn;
}

//apply moveHuman to all Humans currently used by spawner  
void updateSpawner(Spawner* spawn){
    //if for whatever reason the spawner is non existent, just drop
    if(spawn == NULL) return;

    Human* list = spawn->personList;

    //resetting the array for rendering
    for(int i = spawn->yMin; i<spawn->yMax; i++){
        spawn->renderArray[i- spawn->yMin] = NULL;
    }

    while (list != NULL)
    {
        list->sprite.nextSprite = NULL; //resetting cascade
        moveHuman(list);

        //adding the sprite in the array
        int realY = list->sprite.container.y - spawn->yMin;
        spawn->renderArray[realY] =  appendSprite(spawn->renderArray[realY], &list->sprite);

        list = list->next;
    }
    
    if(spawn->nextSpawnCounter == 0){
        int nbp = spawn->nbSPoints;
        int pos = rand()%nbp;
        _pointL* list = spawn->spawnPoints->next;

        for(int i=1; i < pos; i++){
            //there should be absolutely no problem here, since linked list is static (I miss vector from C++... T_T )
            list = list->next;
        }

        spawn->personList = appendHuman(spawn->personList, list->x - 3, list->y + 2, spawn);
        spawn->nbPersons++;

        
        char msg[100];
        sprintf(msg, "%d", spawn->personList->counter);
        debug(msg);


        spawn->nextSpawnCounter = 10; //FRAMERATE/2  + rand()%(2*FRAMERATE); //spaw between 0.5 and 2.5 sec later
    }
    else{
        spawn->nextSpawnCounter--;
    }

    //rendering sprites
    for(int i = spawn->yMin; i<spawn->yMax; i++){
        if(spawn->renderArray[i - spawn->yMin] != NULL){
            showSprite(spawn->renderArray[i-spawn->yMin], 1);
        }
    }
    
}
