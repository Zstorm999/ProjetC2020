#include "include/io.h"

unsigned int** loadSpriteFromFile(char* pathToFile)
{
    FILE* file = fopen(pathToFile, "r");

    if(!file)
    {
        fprintf(stderr, "Error while loading file in %s\n", pathToFile);
        return NULL;
    }

    unsigned int **strArray = (unsigned int**)malloc(MAX_LINES*sizeof(unsigned int*));
    if(!strArray)
    {
        fprintf(stderr, "Error while allocating string\n");
        fclose(file);
        return NULL;
    }

    for(int i=0; i<MAX_LINES; i++)
    {
        strArray[i]= NULL;
    }

    size_t linesize =0;
    int i= 0;
    char err= 1;
    unsigned int *tmpLine; //allow to do some work on the string before affecting it in its final form
    while (err >= 0)
    {
        linesize= 0;
        err = getline(&tmpLine, &linesize, file);
        strArray[i]= tmpLine; //TODO must affectate each char individualy with the cast "L"
        i++;
    }

    fclose(file);
    fflush(stdin);

    return strArray;
}

/*print a char at the selected coordinates,
every coordinates originates from the top left corner*/
void placec(int x, int y, unsigned int symbol)
{
    printf("\033[%d;%dH%lc", x, y, symbol); //%lc on casted L for extended char set
    fflush(stdout);
}