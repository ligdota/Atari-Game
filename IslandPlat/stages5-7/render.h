#include "model.h"
#include "bitmaps.h"
#include "RASTER.h"
#include "types.h"

void render(const Model *model, UINT32 *base);
void renderStickman(const  Stickman *stickmanModel, UINT32 *base);
void renderPlatforms(const Platform *platformModel, UINT32 *base);
void renderSpiders(const Spider *spiderModel, UINT32 *base);
void renderCoin(const Coin *coinModel, UINT32 *base);
void renderTimer(const Timer *timerModel, UINT32 *base);
void renderHeart(const Heart *heartModel, UINT32 *base);
void renderDigits(const Timer *timerModel, UINT32 *base);
