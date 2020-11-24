#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

sprite initDisp();
void showSprite(sprite sprite, char cascade); //display a sprite, trimed and colored, and updates the dependencies if cascade is set to 1