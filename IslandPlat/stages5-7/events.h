#ifndef EVENTS_H
#define EVENTS_H
#include "model.h"
#include "TYPES.H"

void keepSpidersOnPlatforms(Spider *spider, Platform *platform);
void requestMoveStickmanLeft(Stickman *stickman);
void requestMoveStickmanRight(Stickman *stickman);
void requestJumpStickman(Stickman *stickman, Platform *platforms);
void stickmanGravity(Stickman *stickman);
void detectScreenCollision(Stickman *stickman);
void checkSpidersStickmanCollisions(Stickman *stickman, Spider *spiders);
void checkSpiderStickmanCollisionLeft(Stickman *stickman, Spider *spiders);
void checkSpiderStickmanCollisionRight(Stickman *stickman, Spider *spiders);
void checkPlatformStickmanCollisions(Stickman *stickman, Platform *platforms);
void timerDecrement(Timer *timer);
void checkCoinStickmanCollision(Stickman *stickman, Coin *coin);
int endGame(Stickman *stickman, Timer *timer);


#endif