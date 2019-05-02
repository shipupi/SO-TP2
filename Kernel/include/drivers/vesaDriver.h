#ifndef VESADRIVER_H
#define VESADRIVER_H
#include <stdint.h>

void putPixel(uint64_t x,uint64_t y, unsigned char r, unsigned char g, unsigned char b);

void clearAll();
void clearFrom(int x, int y);

void nextLine();
void fillRect(unsigned char startX, unsigned char startY, uint16_t width, uint16_t height, unsigned char r, unsigned char b, unsigned char c);
void printChar(unsigned char myChar, unsigned char r, unsigned char g, unsigned char b);
void printWhiteString(char *str);
void printString(char *str, unsigned char r, unsigned char g, unsigned char b);
void deleteChar();
void printInt(int num);
void printUint(uint64_t num);
#endif