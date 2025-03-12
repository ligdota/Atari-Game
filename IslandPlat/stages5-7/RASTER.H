#ifndef RASTER_H
#define RASTER_H

#include "types.h"

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 bitmap[COIN_SIZE], unsigned int height);  
void plot_bitmap_64 (UINT32 *base, int x, int y, const UINT32 bitmap[HIGHSCORE_SIZE], unsigned int height);
void plot_bitmap_128 (UINT32 *base, int x, int y, const UINT32 bitmap[PLATFORM_SIZE], unsigned int height);
void clear_region(UINT32 *base, int x, int y, int x2, int y2);
void plot_digit_table_16(UINT16 *base, int index, int x, int y, const UINT16 bitmap[DIGIT_TABLE_SZ], unsigned int height);

#endif
