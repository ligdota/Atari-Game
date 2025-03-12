#include "raster.h"

/*
Data Structures and Functions

Purpose: This file contains functions for plotting various sized bitmaps to the screen at given x,y coordinates.
          Also there is a function to clear the screen from a starting x,y position to an ending x2,y2 position.

*/

/*
Purpose: Plot a 16 pixel wide bitmap representing a digit to the screen at given coordinates
UINT16 * base: 16 bit pointer to the start of the frame buffer to display digit bitmap to the screen
int index: index into the bitmap array indicating which digit to display
int x: x location on screen for the bitmap to display at
int y: y location on screen for the bitmap to display at
UINT16 bitmap[DIGIT_TABLE_SZ]: Values of the bitmap to write to frame buffer, digit_table_sz is the maximum number of values in this array
UINT height: height of the bitmap
Assumptions: If the bitmap is being displayed onto another bitmap it will override the previous bitmap
             Maximum array size is 160
*/
void plot_digit_table_16(UINT16 *base, int index, int x, int y, const UINT16 bitmap[DIGIT_TABLE_SZ], unsigned int height)
{

    int count = 0;
    int shift = x & 15;
    index *= 16;
    base = base + (y * 40) + (x >> 4);

    while (count < height)
    {
        *base = bitmap[index] >> shift;
        if (shift > 0)
        {
            *(base + 1) = bitmap[index] << (WORD_SIZE - shift);
        }
        base += WORD_OFFSET;
        count++;
        index++;
    }

    return;
}

/*
Purpose: Plot a 32 pixel wide bitmap to the screen at given coordinates
UINT32 * base: 32 bit pointer to the start of the frame buffer to display bitmap to the screen
int x: x location on screen for the bitmap to display at
int y: y location on screen for the bitmap to display at
UINT32 bitmap[COIN_SIZE]: Values of the bitmap to write to frame buffer, COIN_SIZE is the maximum number of values in this array for a 32 pixel bitmap
UINT height: height of the bitmap
Assumptions: If the bitmap is being displayed onto another bitmap it will override the previous bitmap.
             Maximum array size is 32
*/
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 bitmap[COIN_SIZE], unsigned int height)
{

    if (x >= 0 && x < (SCREEN_WIDTH - 31) && y >= 0 && y < SCREEN_HEIGHT - 31)
    {

        int i = 0;
        base = base + (y * 20) + (x >> 5);
        while (i < height)
        {
            *base = bitmap[i] >> (x & 31);
            *(base + 1) = bitmap[i] << (LONG_SIZE - (x & 31));
            base += LONG_OFFSET;
            i++;
        }
    }

    return;
}

/*
Purpose: Plot a 64 pixel wide bitmap to the screen at given coordinates
UINT32 * base: pointer to the start of the frame buffer to display bitmaps to the screen
int x: x location on screen for the bitmap to display at
int y: y location on screen for the bitmap to display at
UINT32 bitmap[COIN_SIZE]: Values of the bitmap to write to frame buffer, TIMER_SIZE is the maximum number of values in this array for a 64 pixel bitmap
UINT height: height of the bitmap
Assumptions: If the bitmap is being displayed onto another bitmap it will override the previous bitmap.
             Maximum array size is 64
*/
void plot_bitmap_64(UINT32 *base, int x, int y, const UINT32 bitmap[TIMER_SIZE], unsigned int height)
{

    if ((x >= 0 && x < SCREEN_WIDTH - 63) && y >= 0 && (y < SCREEN_HEIGHT - (height - 1)))
    {
        UINT32 bit_shift = x & 31;
        int i = 0;
        height = (height << 1);

        base = base + (y * 20) + (x >> 5);

        while (i < height)
        {
            *base = bitmap[i] >> bit_shift;

            if (bit_shift != 0)
            {
                *(base + 1) = bitmap[i] << (32 - bit_shift);
            }

            *(base + 1) |= bitmap[i + 1] >> bit_shift;
            if (bit_shift != 0)
            {
                *(base + 2) = bitmap[i + 1] << (32 - bit_shift);
            }
            i += 2;
            base += LONG_OFFSET;
        }
    }
    return;
}

/*
Purpose: Plot a 128 pixel wide bitmap to the screen at x,y coordinates
UINT32 * base: pointer to the start of the frame buffer to display bitmaps to the screen
int x: x location on screen for the bitmap to display at
int y: y location on screen for the bitmap to display at
UINT32 bitmap[COIN_SIZE]: Values of the bitmap to write to frame buffer, PLATFORM_SIZE is the maximum number of values in this array for a 128 pixel bitmap
UINT height: height of the bitmap
Assumptions: x must be divisible by 32 to achieve faster plotting
             Maximum array size is 24
*/
void plot_bitmap_128(UINT32 *base, int x, int y, const UINT32 bitmap[PLATFORM_SIZE], unsigned int height)
{
    int i;
    int counter;

    if ((x >= 0 && x < SCREEN_WIDTH - 127) && y >= 0 && y < SCREEN_HEIGHT - (height - 1))
    {

        base = base + (y * 20) + (x >> 5);
        i = 0;

        for (counter = 0; counter < height; counter++)
        {
            *base |= bitmap[i++];
            *(base + 1) |= bitmap[i++];
            *(base + 2) |= bitmap[i++];
            *(base + 3) |= bitmap[i++];

            base += LONG_OFFSET;
        }
    }
    return;
}

/*
Purpose: Clear the pixels on the screen from x,y to x2,y2
Details:
UINT32 * base: Pointer to the start of the frame buffer to display bitmaps to the screen
int x: starting x location on screen to begin clear
int y: startying y location on screen to begin clear
int x2: ending x location on screen to end clear
int y2: ending y location on screen to end clear

Assumptions: x2 must be greater than x and y2 must be greater than y
Bugs: If two bitmaps occupy the same longword then clearing one of the bitmaps
      will also clear the bits of the other bitmap in the same longword
*/
void clear_region(UINT32 *base, int x, int y, int x2, int y2)
{
    int height = y2 - y;
    int lshift = x & 31;
    int rshift = x2 & 31;
    int row;
    int col;
    int col_start = x >> 5;
    int col_end = x2 >> 5;
    UINT32 mask;
    UINT32 endingMask;
    UINT32 *ptr;
    UINT32 checkBaseMap;

    if (x >= 0 && x2 < SCREEN_WIDTH && y >= 0 && y2 < SCREEN_HEIGHT)
    {
        base += (y * 20) + col_start;

        for (row = 0; row < height; row++)
        {
            ptr = base;

            if (col_start == col_end)
            {
                mask = ((0xFFFFFFFF >> lshift) & (0xFFFFFFFF << (31 - rshift)));
                *ptr &= ~mask;
            }
            else
            {

                mask = (0xFFFFFFFF >> lshift);
                *ptr &= ~mask;
                ptr++;
            }

            for (col = col_start + 1; col < col_end; col++)
            {
                *ptr = 0;
                ptr++;
            }

            endingMask = (0xFFFFFFFF << (31 - rshift));
            *ptr &= ~endingMask;

            base += 20;
        }
    }
}
