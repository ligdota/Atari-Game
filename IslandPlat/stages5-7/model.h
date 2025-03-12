#ifndef MODEL_H
#define MODEL_H
#include "TYPES.H"

typedef struct {

    unsigned int x, y;  /* position coordinates*/
    int deltaX, deltaY; /* horizontal and vertical displacement per clock tick */
    unsigned int health; /*players health points, max value 1*/
    unsigned int hasCoin; /*flag to end game loop and decide winner/loser*/
    unsigned int width, height; /* bitmap width and height */
    unsigned int jumpingTimer; /*timer for player jump*/
    unsigned int onPlatform; /* boolean to track if player is falling*/
    STATE state;
} Stickman;


typedef struct {

    unsigned int x, y;  /* position coordinates*/
    int deltaX;         /* horizontal displacement per clock tick*/
    unsigned int width, height; /* bitmap width and height */
    unsigned int numSpiders; /* number of enemies on screen max val = 4*/
    unsigned int currPlatform;  /* used to keep spider on its original spawned platform after movement*/
    unsigned int alive;   /* values are 0 for dead and 1 for alive*/
    unsigned int moveTimer; /* controls how fast the spiders can move*/
} Spider;



typedef struct {
    unsigned int x, y;  /* position coordinates*/
    unsigned int ContainsEnemy; /* platform contains enemy*/
    unsigned int numPlatforms;  /* max platforms on screen = 14*/
    unsigned int width, height; /* bitmap width and height */
} Platform;



typedef struct {
    unsigned int x, y;  /* position coordinates*/
    int tens, ones; /* timer value to display and index into digit bitmap max value = 30*/
    unsigned int decrementTimer;  /* timer to determine when to decrement */
    unsigned int width, height; /* bitmap width and height */
} Timer;


typedef struct {
    unsigned int x,y;   /* position coordinates */
    unsigned int width, height; /* bitmap width and height */
} Coin;


typedef struct {
    unsigned int x,y;   /* position coordinates*/
    unsigned int width, height; /* bitmap width and height*/
} Heart;



typedef struct {
    Stickman stickman;
    Platform platforms[14];
    Spider spiders[4];
    Timer timer;
    Coin coin;
    Heart heart;
} Model;



void moveStickman(Stickman* stickman);
void moveSpider(Spider *spiders);
void decrementTimer(Timer *timer);



#endif
