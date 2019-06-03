#ifndef VESADRIVER_H
#define VESADRIVER_H
#include <stdint.h>



#define cursorYStart 10
#define cursorXStart 10
#define maxLines 38
#define maxY cursorYStart + 20 * maxLines

void putPixel(uint64_t x,uint64_t y, unsigned char r, unsigned char g, unsigned char b);

void clearAll();
void clearFrom(int x, int y);

void nextLine(int section);
void deleteChar(int section);
void fillRect(uint64_t x, unsigned char y, uint16_t width, uint16_t height, unsigned char r, unsigned char g, unsigned char b);
void printChar(unsigned char myChar, unsigned char r, unsigned char g, unsigned char b, int section);
void printWhiteString(char *str);
void prevLine(int section);
void printString(char *str, unsigned char r, unsigned char g, unsigned char b, int section);
void printInt(int num);
void pl(char * string);
void initializeVideoDriver();
void vesa_addSplit();
void vesa_removeSplit();
void drawSplitSeparator();
void clearSplitSeparator();
void shiftUp(int section);
int strlength(const char * str);
#endif