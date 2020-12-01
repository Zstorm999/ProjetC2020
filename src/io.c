/**
 * - Copyright 01/11/2020
 *
 * This source code is released the GNU GPLv3's policy,
 * thus, is hereby granted the legal permission, to any individual obtaining a copy of this file, to copy,
 * distribute and/or modify any of part of the project
 * 
 * the autors, CLEMENT Aimeric and ARCHAMBEAU Thomas
 * disclaim all copyright interest in the program ProjectC2020
 */

#include "include/io.h"


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

void destroySprite(wchar_t** sprite){
    for(int i=0; i< MAX_LINES; i++){
        free(sprite[i]);
    }
    free(sprite);
}

/*print a char at the selected coordinates,
every coordinates originates from the top left corner*/
void placec(int y, int x, wchar_t symbol, char color)
{
    wprintf(L"\033[%d;%dH", y, x);
     switch(color)
    {
        case 'w': //white
            wprintf(L"\033[0;37m");
            break;
        case 'W': //white
            wprintf(L"\033[01;37m");
            break;
        case 'y': //yellow
            wprintf(L"\033[0;33m");
            break;
        case 'Y': //yellow
            wprintf(L"\033[01;33m");
            break;
        case 'r':
            wprintf(L"\033[0;31m");
            break;
        case 'R':
            wprintf(L"\033[01;31m");
            break;
        case 'e':
            wprintf(L"\033[41;31m");
            break;
    }
    wprintf(L"%lc", symbol);
    //wprintf(L"\e[0m");
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

char key_pressed(){
    struct termios oldterm, newterm;
    int oldfd; 
    char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    newterm = oldterm; 
    newterm.c_lflag &= ~(ICANON | ECHO);

    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);  
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    c = getchar();

    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    if (c != EOF) {
        ungetc(c, stdin);
        result = getchar();
    }
    return result;
}

char** loadObjectMap(char* path){
    FILE* f = fopen(path, "r");

    if(!f){
        fprintf(stderr, "Unable to open file %s\n", path);
        return NULL;
    }

    char** objectMap;
    objectMap = (char**)calloc(MAX_LINES, sizeof(char*));
    if(!objectMap){
        fprintf(stderr, "Error while creating object map first dimension\n");
        fclose(f);
        return NULL;
    }


    for(int i=0; i<MAX_LINES; i++){
        objectMap[i] = (char*)calloc(MAX_COLUMNS, sizeof(char));
        if(!objectMap[i]){
            fprintf(stderr, "Error while creating object map second dimension\n");
            fclose(f);
            return NULL;
        }
    }

    for(int i=0; i<MAX_LINES; i++){
        for(int j=0; j<MAX_COLUMNS; j++){

            char c =fgetc(f);

            if(c == EOF) goto out;
            else{
                objectMap[i][j] = c;
                if(c == '\n') break; //newline
            }
        }
    }

    out:

    fclose(f);
    return objectMap;
}