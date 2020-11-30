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

    debug("done without problems\n");

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
    spawn->spawnPoints = NULL;
    spawn->objMap = NULL;
    spawn->bg = NULL;

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


    //loading spawner position
    for(int i=yMin; i<yMax; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            //if spawnable tile, we add it to the list
            if(spawn->objMap[i][j] == spawnChar){
                spawn->spawnPoints =  _pointLAppend(spawn->spawnPoints, i, j);
            }
        }
    }

    //always spawn a human at the first found spawnPoint (y is -1 cause sprite position and real position differ)
    spawn->personList = createHuman((spawn->spawnPoints->x) - 3 , (spawn->spawnPoints->y) + 2 , spawn);

    return spawn;
}

//apply moveHuman to all Humans currently used by spawner  
void updateSpawner(Spawner* spawn){
    //if for whatever reason the spawner is non existent, just drop
    if(spawn == NULL) return;
    Human* list = spawn->personList;

    while (list != NULL)
    {
        moveHuman(list);
        list = list->next;
    }
    
}
