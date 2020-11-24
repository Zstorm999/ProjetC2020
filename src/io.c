#include "include/io.h"

wchar_t** loadSpriteFromFile(char* pathToFile)
{
    FILE* file = fopen(pathToFile, "r");

    if(!file)
    {
        fprintf(stderr, "Error while loading file in %s\n", pathToFile);
        return NULL;
    }

    printf("passed l13-io\r\n");
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

        for(int j=0; j<MAX_COLUMNS; j++){
            sprite[i][j]= "\0\0\0"; //FIXME core dumped, can't find i>0 for the next lines
            printf("%d:%d\r\n", i, j);
        }
    }
    printf("passed l40-io\r\n");
    //now that the sprite is corectly allocated, we can fill it
    //we use strings of 1 to 3 chars, 1 char for ascii and 3 for unicode

    for(int i=0; i<MAX_LINES; i++){
        for(int j=0; j<MAX_COLUMNS; j++){
            wchar_t c = fgetwc(file);

            if(c == EOF) goto out;
            else
            {
                if(c >= 0 && c <= 127)  //if ascii
                {
                    sprite[i][j][0]= c;
                    sprite[i][j][1]= '\0';
                    sprite[i][j][2]= '\0';
                    j+= 2;
                }
                else {                  //if unicode
                    sprite[i][j][0]= c; //it will overflow over 2 slots
                }

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

void showSprite(wchar_t** sprite){

    for(int i=0; i<MAX_LINES; i++){
        for(int j=0; j<MAX_COLUMNS; j++){

            wprintf(L"%lc", sprite[i][j]);
            if(sprite[i][j] == '\n') break;

        }
    }

}

/*print a char at the selected coordinates,
every coordinates originates from the top left corner*/
void placec(int x, int y, char* symbol)
{
    printf("\033[%d;%dH", x, y);
    printf("%s", symbol);
    fflush(stdout);
}