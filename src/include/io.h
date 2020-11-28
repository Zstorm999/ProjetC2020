#ifndef _IO_H
#define _IO_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "globals.h"

#define MAX_LINES 60
#define MAX_COLUMNS 200

wchar_t** loadSpriteFromFile(char* pathToFile);         //load a file into a matrix
void placec(int x, int y, wchar_t symbol, char color);  //print a char at the selected loccation
char** file2Mask(char* mskFilePath);                    //load a simple file into a matrix used as mask
char key_pressed();
void loadObjectMap(char* path);

void debug(const char* message);

#endif //_IO_H