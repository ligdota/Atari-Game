#include "render.h"


/*
purpose: Plot a static image of all game objects to the screen
inputs: model - Structure containing all game objects, type *Model
        base -  Starting address of the frame buffer, type UINT32*
*/
void render(const Model *model, UINT32 *base) {
    int platformsIndex = 0;
    int spidersIndex = 0;
    int i = 0;

    static Stickman prevStickman;
    static Spider prevSpiders[4];
    static Timer prevTimer;
    static int firstRun = 1;


    
    if (firstRun) {
    for (platformsIndex; platformsIndex < NUMBEROFPLATFORMS; platformsIndex++) {
    renderPlatforms(&model->platforms[platformsIndex], base);
    }

    renderCoin(&model->coin, base);
    renderTimer(&model->timer, base);
    renderDigits(&model->timer, base);
    renderHeart(&model->heart, base);


    renderStickman(&model->stickman, base);

    for (spidersIndex; spidersIndex < NUMBEROFENEMIES; spidersIndex++) {
    renderSpiders(&model->spiders[spidersIndex], base);
    }



    prevStickman = model->stickman;
    for (i = 0; i < NUMBEROFENEMIES; i++) {
        prevSpiders[i] = model->spiders[i];
    }
    prevTimer = model->timer;

    firstRun = 0;
    }
    else {

        for (i = 0; i < NUMBEROFPLATFORMS; i++) {
                renderPlatforms(&model->platforms[i], base);
        }
        renderCoin(&model->coin, base);
        renderTimer(&model->timer, base);
        renderHeart(&model->heart, base);
        renderDigits(&model->timer, base);
        
        
        if (model->stickman.x != prevStickman.x || model->stickman.y != prevStickman.y || model->stickman.state != prevStickman.state)  {

                
                clear_region(base, prevStickman.x, prevStickman.y, prevStickman.x + STICKMAN_HEIGHT, prevStickman.y + STICKMAN_HEIGHT);
                renderStickman(&model->stickman, base);
                prevStickman = model->stickman;
        }

        for (i = 0; i < NUMBEROFENEMIES; i++) {
                if (model->spiders[i].x != prevSpiders[i].x) {
                        clear_region(base, prevSpiders[i].x, prevSpiders[i].y, prevSpiders[i].x + SPIDER_SIZE, prevSpiders[i].y + SPIDER_HEIGHT);
                        renderSpiders(&model->spiders[i], base);
                        prevSpiders[i] = model->spiders[i];
                }
        }

        

    }

return;
}

/*
purpose: Plot the stickman to the screen based on its current state
inputs: stickman - Structure containing the current stickman properties, type Stickman*
        base - Starting address of the frame buffer, type UINT32*
*/
void renderStickman(const  Stickman *stickmanModel, UINT32 *base) {

    plot_bitmap_32(base, stickmanModel->x, stickmanModel->y, stickman32, STICKMAN_HEIGHT);
return;
}

/*
purpose: Plot a platform to the screen based on the current platform properties
inputs: platform - Structure containing the current platform properties, type Platform*
        base - Starting address of the frame buffer, type UINT32*
*/
void renderPlatforms(const Platform *platformModel, UINT32 *base) {

    plot_bitmap_128(base, platformModel->x, platformModel->y, platform, PLATFORM_HEIGHT);

return;
}

/*
purpose: Plot a spider to the screen based on the current spider properties
inputs: model - Structure containing the current spider properties, type Spider* 
        base - Starting address of the frame buffer, type UINT32*
*/
void renderSpiders(const Spider *spiderModel, UINT32 *base) {

    plot_bitmap_64(base, spiderModel->x, spiderModel->y, spider, SPIDER_HEIGHT);

return;
}

/*
purpose: Plot the coin to the screen based on the current coin properties
inputs: model - Structure containing the current coin properties, type Coin*
        base - Starting address of the frame buffer, type UINT32*
*/
void renderCoin(const Coin *coinModel, UINT32 *base) {
plot_bitmap_32(base, coinModel->x, coinModel->y, coin, COIN_HEIGHT);
return;
}


/*
purpose: Plot the players heart to the screen
inputs: heartModel - Structure containing the heart properties
        base - Starting address of the frame buffer, type UINT32*
*/
void renderHeart(const Heart *heartModel, UINT32 *base) {
        plot_bitmap_32(base, heartModel->x, heartModel->y, heart, heartModel->height);
}

void renderDigits(const Timer *timerModel, UINT32 *base) {
plot_digit_table_16(base, timerModel->tens, timerModel->x + 16, timerModel->y + 15, digitTable, DIGIT_TABLE_HEIGHT);
plot_digit_table_16(base, timerModel->ones, timerModel->x + 32, timerModel->y + 15, digitTable, DIGIT_TABLE_HEIGHT);
}

/*
purpose: Plot the timer box, label, and digits to the screen based on the current timer properties
inputs: timer - Structure containing all of the timer properties, type Timer*
        base - Starting address of the frame buffer, type UINT32*
*/
void renderTimer(const Timer *timerModel, UINT32 *base) {
plot_bitmap_64(base, timerModel->x, timerModel->y, timer, TIMER_HEIGHT);
return;
}