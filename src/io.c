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
    //we use strings of 1 to 3 chars, 1 char for ascii and 3 for unicode

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
void placec(int x, int y, unsigned int symbol)
{
    printf("\033[%d;%dH", x, y);
    wprintf(L"%lc", symbol);
    fflush(stdout);
}