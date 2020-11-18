#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#define MAX_LINES 60
#define MAX_COLUMNS 200

char** loadSpriteFromFile(char* pathToFile);  //load a file into a matrix
void placec(int x, int y, char symbol);       //print a char at the selected loccation

#endif //_IO_H