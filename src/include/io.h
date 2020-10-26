#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#define MAX_LINES 40

unsigned int** loadSpriteFromFile(char* pathToFile);  //load a file into a matrix
void placec(int x, int y, unsigned int symbol);       //print a char at the selected loccation

#endif //_IO_H