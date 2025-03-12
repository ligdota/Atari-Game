#include "events.h"


/*
Purpose: Restrict spiders to movement to the platform they are spawned on
Inputs: Pointers to the Array of spider structures and array of platform structures
Assumptions: Spider structure current platform attribute must be the index of the platform its spawned on in the array of Platforms
*/
void keepSpidersOnPlatforms(Spider *spider, Platform *platform)
{
    int count = 0;
    for (count; count < spider->numSpiders; count++) {
    if (spider[count].x <= platform[spider[count].currPlatform].x || (spider[count].x + SPIDER_SIZE) >= (platform[spider[count].currPlatform].x + platform[spider[count].currPlatform].width))
    {
        spider[count].deltaX *= -1;
    }
    }
    return;
}

/*
Purpose: sets the Stickmans horizontal velocity to negative
Inputs: Pointer to the Stickman structure
Assumptions: None
*/
void requestMoveStickmanLeft(Stickman *stickman)
{
        stickman->deltaX = -MOVE;
    
    return;
}

/*
Purpose: Sets the Stickmans horizontal velocity to positive
Inputs: Pointer to the Stickman structure
Assumptions: None
*/
void requestMoveStickmanRight(Stickman *stickman)
{
   
    stickman->deltaX = MOVE;
  return;
}

/*
Purpose: Restrict the player to jumping every 110 clock cycles
        And restrict the player from jumping if there is a platform above within
        the jumping range
Inputs: Pointers to the Stickman structure and array of Platform structures
Assumptions: None
*/

void requestJumpStickman(Stickman *stickman, Platform *platforms) {
    int i;
    int headCollision = 0;

   
    for (i = 0; i < NUMBEROFPLATFORMS; i++) {
       
        if (stickman->y + JUMP < platforms[i].y + platforms[i].height &&  
            stickman->y > platforms[i].y &&                              
            stickman->x + stickman->width > platforms[i].x &&             
            stickman->x < platforms[i].x + platforms[i].width) {           
            headCollision = 1;
            break;
        }
    }

   
    if (!headCollision && stickman->state == IDLESTATE && stickman->jumpingTimer >= 110) {
        stickman->state = JUMPSTATE;
        stickman->jumpingTimer = 0;
        stickman->deltaY = JUMP;  
    }
}



/*
Purpose: Apply a downward force to the stickman after he has been in the air for 110 clock cycles
Inputs: Pointer to the Stickman structure
Assumptions: None
*/
void stickmanGravity(Stickman *stickman) {
    if (stickman->state == JUMPSTATE && stickman->jumpingTimer > 110) {
        stickman->state = FALLSTATE;

    }
    if (stickman->state == FALLSTATE) {
        stickman->deltaY = FALL;
    }

      stickman->jumpingTimer++;
      return;
}

/*
Purpose: Sets the losing condition if the player collides with a screen edge
Inputs: Pointer to the Stickman structure
Assumptions: None
*/
void detectScreenCollision(Stickman *stickman) {
    if (stickman->y > SCREEN_HEIGHT - stickman->height || stickman->x < 0 || stickman->x + stickman->width > SCREEN_WIDTH) {
        stickman->health--;
    } 
    return;
}




/*
Purpose: If the winning condition is met calculate the players final score
Inputs: Stickman structure and Highscore structure and Timer structure
Assumptions: None
*/
/*
void calculateFinalScore(Stickman *stickman, Highscore *highscore, Timer *timer) {

    if (stickman->hasCoin == 1) {
        while (timer->ones != -1) {
            if (timer->ones == 0 && timer->tens == 0) {
                timer->ones = -1;
            }
            if (highscore->ones == 9) {
                highscore->tens++;
                highscore->ones = 0;
            }
            else {
                highscore->ones++;
            }
            if (timer->ones == 0 && timer->tens > 0) {
                timer->tens--;
                timer->ones = 9;
            }
            else {
                timer->ones--;
            }
            
        }
    }
    return; 
}
*/


/*
Purpose: Checks left and right collisions for the Stickman and all Spiders on screen
Inputs: Pointers to the Stickman structure and Spider structure
Assumptions: None
*/
void checkSpidersStickmanCollisions(Stickman *stickman, Spider *spiders) 
{
    int i = 0;
    for (i; i < spiders->numSpiders; i++) {
        Spider *spider = &spiders[i];

        if (stickman->x < spider->x + spider->width && 
            stickman->x + stickman->width > spider->x && 
            stickman->y < spider->y + spider->height && 
            stickman->y + stickman->height > spider->y) { 
            stickman->health--; 
        }
    }
            return; 
}


/*
Purpose: Checks collisions between the stickmans right edge and a spiders left edge
Inputs: Pointers to the Stickman structure and Spider structure
Assumptions: None
*/
void checkSpiderStickmanCollisionRight(Stickman *stickman, Spider *spider)
{
    if (stickman->y == spider->y && stickman->x + stickman->width >= spider->x &&
        stickman->x <= spider->x)
    {
        stickman->health = 0;
    }

    return;
}

/*
Purpose: Checks for a collision between the stickmans left edge and a spiders right edge
Inputs: Pointers to the Stickman structure and Spider structure
Assumptions: None
*/
void checkSpiderStickmanCollisionLeft(Stickman *stickman, Spider *spider)
{

    if (stickman->y == spider->y && stickman->x <= spider->x + spider->width &&
        stickman->x >= spider->x)
    {
        stickman->health = 0;
    }

    return;
}

/*
Purpose: Stops the stickman from falling when landing on a platform
Inputs: Pointers to the Stickman structure and an array of Platform structures
Assumptions: None
*/



void checkPlatformStickmanCollisions(Stickman *stickman, Platform *platforms) {
    int onPlatform = 0;
    
    int i;

    for (i = 0; i < platforms->numPlatforms; i++) {
        /* Check for landing on the platform (vertical collision) */
        if (stickman->y + stickman->height >= platforms[i].y &&
            stickman->y + stickman->height <= platforms[i].y + FALL &&
            stickman->x + stickman->width > platforms[i].x &&
            stickman->x < platforms[i].x + platforms[i].width) {

            stickman->y = platforms[i].y - STICKMAN_HEIGHT;
            stickman->deltaY = 0;
            stickman->state = IDLESTATE;
            stickman->onPlatform = 1;
            onPlatform = 1;
        }
        /* check right side collision with platform*/
       if (stickman->x + stickman->width + MOVE >= platforms[i].x &&
    stickman->x + stickman->width <= platforms[i].x && 
    stickman->y + stickman->height > platforms[i].y && 
    stickman->y < platforms[i].y + platforms[i].height) { 
        stickman->x -= MOVE; 
}
    /* check left side collision*/
    if (stickman->x - MOVE <= platforms[i].x + platforms[i].width && 
    stickman->x > platforms[i].x + platforms[i].width && 
    stickman->y + stickman->height > platforms[i].y && 
    stickman->y < platforms[i].y + platforms[i].height) { 
        stickman->x += MOVE; 
        stickman->deltaX = 0; 
}
        

    }

   

    if (!onPlatform) {
        stickman->onPlatform = 0;
        if (stickman->state != JUMPSTATE) {
            stickman->state = FALLSTATE;
            stickman->deltaY = FALL; 
        }
    }
}


/*
Purpose: Decrement the timer every 1 second
Inputs: Pointer to the Timer structure
Assumptions: None
*/

void timerDecrement(Timer *timer) {
    

    if (timer->decrementTimer >= 70) {
        timer->decrementTimer = 1;
        if (timer->ones == 0) {
            timer->tens--;
            timer->ones = 9;
        }
        else {
        timer->ones--;
        }

    }
    else {
        timer->decrementTimer++;
    }

}

/*
Purpose: Sets the winning condition if the stickman picks up the coin
Inputs: Pointers to the Stickman structure and coin structure
Assumptions: None
*/

void checkCoinStickmanCollision(Stickman *stickman, Coin *coin)
{
    if (stickman->y == coin->y &&
        stickman->x <= coin->x + coin->width &&
        stickman->x + stickman->width >= coin->x + coin->width)
    {
        stickman->hasCoin = 1;
    }

    return;
}

/*
Purpose: Ends the game if a winning condition is true
Inputs: Pointers to the Stickman structure and Timer structure
Assumptions: None
*/
int endGame(Stickman *stickman, Timer *timer)
{
    return stickman->hasCoin || (timer->tens == 0 && timer->ones == 0) || stickman->health == 0;
}


