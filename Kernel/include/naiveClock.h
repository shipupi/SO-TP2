#ifndef NAIVE_CLOCK_H
#define NAIVE_CLOCK_H

#include <stdint.h>
uint64_t getTime(uint64_t value);
uint64_t getSeconds();
uint64_t getMinutes();
uint64_t getHours();
void showTime();

#endif
