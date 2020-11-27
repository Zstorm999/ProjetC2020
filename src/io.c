#include "include/io.h"
#include <stdio.h>

wchar_t** loadSpriteFromFile(char* pathToFile)
{
    FILE* file = fopen(pathToFile, "r");

    if(!file)
    {
        fprintf(stderr, "Error while loading file in %s\n", pathToFile);
        return NULL;
    }

    //allocating sprite first dimension
    wchar_t** sprite = (int**)calloc(MAX_LINES, sizeof(wchar_t*));
    if(!sprite){
        fprintf(stderr, "Error while allocating sprite first dimension\n");
        return NULL;
    }


    for(int i=0; i<MAX_LINES; i++){
        //allocating sprite second dimension
        sprite[i] = (wchar_t*)calloc(MAX_COLUMNS, sizeof(wchar_t));
        if(!sprite[i]){
            fprintf(stderr, "Error while allocating sprite second dimension\n");
            free(sprite);
            //should improve memory management here
            return NULL;
        }
    }
    //now that the sprite is corectly allocated, we can fill it

    for(int i=0; i<MAX_LINES; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            wchar_t c = fgetwc(file);

            if(c == EOF) goto out;
            else
            {
                sprite[i][j] = c;
                if(c == '\n') break; //end of line
            }

        }
    }

    out:

    fclose(file);
    fflush(stdin);

    return sprite;
}

void destroySprite(int** sprite){
    for(int i=0; i< MAX_COLUMNS; i++){
        free(sprite[i]);
    }
    free(sprite);
}

/*print a char at the selected coordinates,
every coordinates originates from the top left corner*/
void placec(int x, int y, wchar_t symbol, char color)
{
    wprintf(L"\033[%d;%dH", x, y);
     switch(color)
    {
        case 'w': //white
            wprintf(L"\033[01;37m");
            break;
        case 'y': //yellow
            wprintf(L"\033[01;33m");
    }
    wprintf(L"%lc", symbol);
}

//similar to loadSprite but less memory consuming
char** file2Mask(char* mskFilePath)
{
    FILE* file = fopen(mskFilePath, "r");

    if(!file)
    {
        fprintf(stderr, "Error while loading file in %s\n", mskFilePath);
        return NULL;
    }

    //allocating mask first dimension
    char** mask = (char**)calloc(MAX_LINES, sizeof(char*));
    if(!mask){
        fprintf(stderr, "Error while allocating mask first dimension\n");
        return NULL;
    }


    for(int i=0; i<MAX_LINES; i++){
        //allocating mask second dimension
        mask[i] = (char*)calloc(MAX_COLUMNS, sizeof(char));
        if(!mask[i]){
            fprintf(stderr, "Error while allocating mask second dimension\n");
            free(mask);
            return NULL;
        }
    }

    for(int i=0; i<MAX_LINES; i++)
    {
        for(int j=0; j<MAX_COLUMNS; j++)
        {
            char c = fgetwc(file);

            if(c == EOF) goto out;
            else
            {
                mask[i][j] = c;
                if(c == '\n') break; //end of line
            }

        }
    }

    out:
    fclose(file);
    fflush(stdin);

    return mask;
}

void debug(const char* message){
    FILE* f = fopen("debug.log", "a");

    if(!f){
        fprintf(stderr, "error while opening error file\n");
        return;
    }

    fprintf(f, message);

    fclose(f);
}