#include "include/io.h"

char** loadSpriteFromFile(char* pathToFile){
    FILE* file = fopen(pathToFile, "r");

    if(!file){
        fprintf(stderr, "Error while loading file in %s\n", pathToFile);
        return NULL;
    }

    char** strArray = (char**)malloc(MAX_LINES*sizeof(char*));
    if(!strArray){
        fprintf(stderr, "Error while allocating string\n");
        fclose(file);
        return NULL;
    }

    for(int i=0; i<MAX_LINES; i++){
        strArray[i]=NULL;
    }

    size_t lineSize =0;
    int i=0; 
    int err = getline(&strArray[i], &lineSize, file);
    while (err >= 0)
    {
        lineSize =0;
        i++;
        err = getline(&strArray[i], &lineSize, file);
    }

    fclose(file);

    return strArray;
}
