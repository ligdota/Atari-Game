#include "model.h"



void moveStickman(Stickman *stickman)
{

    stickman->x += stickman->deltaX;
    
    stickman->y += stickman->deltaY;
    

    stickman->deltaX = 0;
    stickman->deltaY = 0;

    return;
}

void moveSpider(Spider *spiders)
{
    int count = 0;
    for (count; count < spiders->numSpiders; count++) {
    if (spiders[count].moveTimer > 70) {
    spiders[count].x += spiders[count].deltaX;
    spiders[count].moveTimer = 1;
    }
    else {
        spiders[count].moveTimer++;
    }
    }
    return;
}




void decrementTimer(Timer *timer)
{

      if (timer->ones == 0) {
                timer->tens--;
                timer->ones = 9;
            }
            else {
                timer->ones--;
            }

    return;
}


