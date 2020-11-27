#include "include/displayManager.h"
#include "include/io.h"
#include "include/train.h"
#include "include/human.h"

int main()
{
    system("clear");

    setlocale(LC_ALL, "");
    initDisp();

    Human* person = createHuman(50, 10);
    showSprite(person->sprite, 1);

    return 0;
}

