#ifndef STDIO_H
#define STDIO_H

#include <stdint.h>

void pint(int num);
void puint(uint64_t num);
char getChar();
void putChar(char c);
void printf(char * str);
void scanf(char * str, int bytes);
char getCharWithZero();

#endif