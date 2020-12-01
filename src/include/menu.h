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

#ifndef _MENU_H
#define _MENU_H

#include "structs.h"
#include <stdbool.h>
#include <wchar.h>

#define FULL_WIDTH 132
#define FULL_HEIGHT 33
#define Y_TITLE 8
#define LEN_TITLE 117
#define HEI_TITLE 6
#define Y_STRTCHOICE 21
#define CHOICE_SPACING 1
#define LEFTALIGN 9;

typedef struct _Choice Choice;
struct _Choice{
    int rank;
    wchar_t* text;
    bool selected;
    Choice* prev;
    Choice* next;
};

void drawBox(Rectangle* shape);
void drawTitle();
Choice* appendNewChoice(Choice* prev, wchar_t* text);
void drawChoice(Choice* item);
int menuUp(Choice* FirstItem);      //return the rank of the selected choice
int menuDown(Choice* FirstItem);    //return the rank of the selected choice
int navigateMenu(Choice* FirstItem);
int manageMenu();                   //return execution mode

#endif //_MENU_H