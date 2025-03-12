#include "island.h"

/*
Purpose: Main() Runs the game loop for the game and checks if a frame has passed in order to check if events have occurred
         AlignBuffer() uses an array of 32256 bytes which sets the address to 256-aligned required by the Atari-ST in order
         to accomplish double buffering
         Test Model is a structure of structures containing all the game objects and their properties
*/

UINT8 doubleBuffer[32255];
void *doubleBufferAligned;

UINT8 doubleBufferStarting;

int main() {



        Model testModel = {

        {32, 348, 0, 0, 1, 0, 32, 32, 140, 1, IDLESTATE},
        {
            {32, 380, 0, 14, 128, 2},   /* starting platform*/
            {224, 356, 0, 14, 128, 2},  /* 2nd platform*/
            {352, 332, 0, 14, 128, 2}, /* 3rd plat contains spider*/
            {224, 100, 0, 14, 128, 2}, /* platform with coin */
            {160, 308, 0, 14, 128, 2}, /* 4th platform */
            {0, 285, 0, 14, 128, 2}, /* 5th platform contains spider*/
            {192, 262, 0, 14, 128, 2}, /* 6th platform*/
            {320, 242, 0, 14, 128, 2}, /* 7th platform*/
            {480, 220, 0, 14, 128, 2}, /* 8th platform contains spider*/
            {288, 196, 0, 14, 128, 2}, /* 9th platform */
            {128, 172, 0, 14, 128, 2}, /* 10th platform*/
            {64, 116, 0, 14, 128, 2}, /*  2nd last platform contains spider*/
            {320, 148, 0, 14, 128, 2},  /* 11th platform */
            {416, 124, 0, 14, 128, 2}
            },
            /* spider platform indexes are 2,5,8,11*/
        {
            {352, 300, 4, 64, 24, 4, 2, 1, 1},
            {0, 253, 4, 64, 24, 4, 5, 1, 1},
            {480, 188, 4, 64, 24, 4, 8, 1, 1},
            {416, 92, 4, 64, 24, 4, 13, 1, 1}},
        {576, 0, 6, 0, 64, 32},
        {256, 68, 32, 32},
        {0, 0, 32, 32}};

long old_ssp;
UINT32 currCounter;


    UINT8 vblValue;
    UINT32 *base32 = Physbase();        
    UINT32 *doublebuff;
    int quit = FALSE;
    UINT32 timeBefore, timeNow, timeElapsed;
    UINT32 *tempBase;

    alignBuffer();
  

    doublebuff = doubleBufferAligned;

    render(&testModel, base32); 
    timeBefore = get_time();

    while (!quit) {
        
        long *vblCounter = (long *)0x462;
        old_ssp = Super(0);
        currCounter = *vblCounter;
        while (*vblCounter == currCounter) {

        }
        Super(old_ssp);
        render(&testModel, doublebuff);
        Setscreen(doublebuff, -1, -1);
        base32 = Physbase();
        tempBase = doublebuff;
        doublebuff = base32;
        base32 = tempBase;

      
        getKey();
        if (detectWKeyPress()) requestJumpStickman(&testModel.stickman, testModel.platforms);
        if (detectAKeyPress()) requestMoveStickmanLeft(&testModel.stickman);
        if (detectDKeyPress()) requestMoveStickmanRight(&testModel.stickman);
        if (detectQKeyPress()) quit = TRUE;

      
        timeNow = get_time();
        timeElapsed = timeNow - timeBefore;
        if (timeElapsed > 0) {
            stickmanGravity(&testModel.stickman);
            moveStickman(&testModel.stickman);
            checkPlatformStickmanCollisions(&testModel.stickman, testModel.platforms);
            checkSpidersStickmanCollisions(&testModel.stickman, testModel.spiders);
            checkCoinStickmanCollision(&testModel.stickman, &testModel.coin);
            detectScreenCollision(&testModel.stickman);
            moveSpider(testModel.spiders);
            keepSpidersOnPlatforms(testModel.spiders, testModel.platforms);
            timerDecrement(&testModel.timer);
            if (endGame(&testModel.stickman, &testModel.timer)) quit = TRUE;

            timeBefore = timeNow;
        }
    }

    Setscreen(base32, -1, -1); 
    return 0;
}



/*
Purpose: Align the address of the double buffer to 256
Inputs: none
Assumptions: None
*/
void alignBuffer() {
    doubleBufferStarting = ((UINT8) &doubleBuffer[0]) % 256;
    
    if (doubleBufferStarting == 0) {
        doubleBufferAligned = &doubleBuffer[0];

    }
    else {
        doubleBufferAligned = &doubleBuffer[256 - doubleBufferStarting];
    }
    
}


/*
Purpose: Get the amount of time thats passed since the last frame
*/

UINT32 get_time() {

    long old_ssp;
    UINT32 currentTime;
    long *timer = (long) 0x462;



    old_ssp = Super(0);
    currentTime = *timer;
    Super(old_ssp);

    return currentTime;

}