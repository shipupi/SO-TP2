#ifndef VIDIO_H
#define VIDIO_H
#include <stdint.h>

void placePixel(uint64_t x, uint64_t y, uint64_t red,uint64_t green,uint64_t blue);
void drawRectangle(uint64_t xCenter, uint64_t yCenter, uint64_t xOffset, uint64_t yOffset, uint64_t red,uint64_t green,uint64_t blue);

void drawRectangleFromCorner(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint64_t red,uint64_t green,uint64_t blue);
void drawWhiteRectangleFromCorner(uint64_t x, uint64_t y, uint64_t width, uint64_t height);
void drawCharInScreen(int  x, int  y, unsigned char myChar, unsigned char r, unsigned char g, unsigned char b, unsigned char size);
void drawStringInScreen(int x, int y, char * str , unsigned char r, unsigned char g, unsigned char b, unsigned char size);
#endif
