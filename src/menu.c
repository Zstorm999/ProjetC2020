#include "include/menu.h"
#include "include/io.h"
#include "include/displayManager.h"
#include "include/structs.h"
#include <stdlib.h>
#include <linux/input.h>
#include <wchar.h>

void drawBox(Rectangle* shape)
{
    char colo= 'w'; //color
    int i;
    placec(shape->xMin, shape->yMin, L'┌', colo);
    placec(shape->yMax, shape->xMin, L'└', colo);
    placec(shape->xMin, shape->xMax, L'┐', colo);
    placec(shape->yMax, shape->xMax, L'┘', colo);
    for(i= (shape->yMin)+2; i<shape->yMax; i++)
    {
        placec(i, shape->yMin, L'│', colo);
    }
    for(i= shape->yMin+2; i<shape->yMax; i++)
    {
        placec(i, shape->xMax, L'│', colo);
    }
    for(i= shape->xMin+2; i<shape->xMax; i++)
    {
        placec(shape->xMin, i, L'─', colo);
    }
    for(i= shape->xMin+2; i<shape->xMax; i++)
    {
        placec(shape->yMax, i, L'─', colo);
    }
}

void drawTitle(){
    sprite* titleSprite= (sprite*)malloc(sizeof(sprite));
    titleSprite->img= loadSpriteFromFile("data/Title.txt");
    titleSprite->spriteName= L"Title";
    titleSprite->container.x= LEFTALIGN;
    titleSprite->container.y= Y_TITLE;
    titleSprite->container.xMin= 0;
    titleSprite->container.xMax= LEN_TITLE;
    titleSprite->container.yMin= 0;
    titleSprite->container.yMax= HEI_TITLE;
    titleSprite->color= 'w';
    titleSprite->maskMap= NULL;
    showSprite(*titleSprite, 0);
}

Choice* appendNewChoice(Choice* prev, wchar_t* text)
{
    Choice* NewChoice= (Choice*)malloc(sizeof(Choice));
    NewChoice->text= text;
    NewChoice->next= NULL;
    if(prev!= NULL)
    {
        prev->next= NewChoice;
        NewChoice->prev= prev;
        NewChoice->rank= prev->rank+1;
        NewChoice->selected= false;
    }
    else {
        NewChoice->rank= 0;
        NewChoice->prev= NULL;
        NewChoice->selected= true;
    }
    return NewChoice;
}

void drawChoice(Choice* item)
{
    int len= wcslen(item->text);
    int xMin= LEFTALIGN;
    char colo;
    if(item->selected)
        colo= 'y';
    else
        colo= 'w'; 
    for(int i= 0; i<len; i++)
    {
        placec(Y_STRTCHOICE+(item->rank*CHOICE_SPACING), i+xMin, item->text[i], colo);
    }
}

int menuUp(Choice* FirstItem){
    Choice* currSel= FirstItem; //currently selected
    while(!currSel->selected)   //look for the selected item
    {
        currSel= currSel->next;
    }
    if(currSel->prev!=NULL)
    {
        currSel->selected= false;
        currSel->prev->selected= true;
        drawChoice(currSel);
        drawChoice(currSel->prev);
        currSel= currSel->prev;
    }
    return currSel->rank;
}

int menuDown(Choice* FirstItem){
    Choice* currSel= FirstItem; //currently selected
    while(!currSel->selected)   //look for the selected item
    {
        currSel= currSel->next;
    }
    if(currSel->next!=NULL)
    {
        currSel->selected= false;
        currSel->next->selected= true;
        drawChoice(currSel);
        drawChoice(currSel->next);
        currSel= currSel->next;
    }
    return currSel->rank;
}

int navigateMenu(Choice* FirstItem)
{
    Choice currSel= *FirstItem;
    while(!currSel.selected)   //look for the selected item
    {
        currSel= *currSel.next;
    }
    int rankSelected= currSel.rank;
    char currKey;
    while(currKey!='\n')
    {
        currKey= '\0';
        while(currKey=='\0')
        {
            currKey= key_pressed();
        }
        if(currKey==27)
        {
            if(key_pressed()==91)
            {              //to press an arrow key send the sequence 27, 91, [65..68]
                char arrowKey= key_pressed();   //65:up, 66:down, 68:left, 67:right
                switch (arrowKey)
                {
                    case 65: //arrow up
                        rankSelected= menuUp(FirstItem);
                        break;
                    case 66: //arrow down
                        rankSelected= menuDown(FirstItem);
                        break;
                }
            }
        }
    }
    return rankSelected;
}

int manageMenu()
{
    drawTitle();

    Choice* cLaunchClassic= appendNewChoice(NULL, L"Start in classic mode");
    Choice* cLaunchFast= appendNewChoice(cLaunchClassic, L"Start in fast mode");
    Choice* cQuit= appendNewChoice(cLaunchFast, L"Quit");

    drawChoice(cLaunchClassic);
    drawChoice(cLaunchFast);
    drawChoice(cQuit);

    Rectangle* border = (Rectangle*)malloc(sizeof(Rectangle));
    border->xMin= 0; border->xMax= FULL_WIDTH;
    border->yMin= 0; border->yMax= FULL_HEIGHT;
    drawBox(border);

    menuDown(cLaunchClassic);
    int choiceRank= navigateMenu(cLaunchClassic);

    //terminate the program if "quit" is choosen (fluidity concerns: no prompt)
    if(choiceRank==2)
    {
        system("clear");
        exit(0);
    }

    return choiceRank;
}