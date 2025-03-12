#ifndef TYPES_H
#define TYPES_H


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTE_OFFSET 80
#define WORD_OFFSET 40
#define LONG_OFFSET 20
#define WORD_SIZE 16
#define LONG_SIZE 32

typedef enum {IDLESTATE, MOVESTATE, JUMPSTATE, FALLSTATE} STATE;
#define DIGIT_TABLE_SZ 160
#define DIGIT_TABLE_HEIGHT 16

#define GAME_OVER_SZ 196
#define GAME_OVER_HEIGHT 49

#define STICKMAN_SIZE 32
#define STICKMAN_HEIGHT 32
#define STICKMAN_WIDTH 32
#define STICKMAN_MIDDLE 16


#define HEART_SIZE 32
#define HEART_HEIGHT 32

#define COIN_SIZE 32
#define COIN_HEIGHT 32

#define PLATFORM_SIZE 24
#define PLATFORM_HEIGHT 2

#define JUMP -32
#define MOVE 4

#define NULL 0

#define FALL 8

#define MOVE_LEFT_KEY 97
#define MOVE_RIGHT_KEY 100
#define JUMP_KEY 119
#define QUIT_KEY 113
#define SPACE_KEY 32



#define SPIDER_SIZE 64
#define SPIDER_HEIGHT 32
#define SPIDER_PLAT_OFFSET 28
#define STICKMAN_PLAT_OFFSET 28

#define TIMER_SIZE 64
#define TIMER_HEIGHT 32

#define HIGHSCORE_SIZE 64
#define HIGHSCORE_HEIGHT 32

#define STICKMAN_X_START 32
#define STICKMAN_Y_START 600

#define NUMBEROFENEMIES 4
#define NUMBEROFPLATFORMS 14

#define ONPLATFORM 1
#define OFFPLATFORM 0

#define TRUE 1 
#define FALSE 0


typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef unsigned char UINT8;


#endif

/*
enemy is 21 tall
player is 32 tall
timer is 32 tall
highscore is 32 tall
coin is 32 tall
rainbow is 32 tall 
platform is 4 tall
*/
