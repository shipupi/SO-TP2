#ifndef LIB_H
#define LIB_H

#include <stdint.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);
int upper_power_of_two(int v);
char *cpuVendor(char *result);
int power(int base,int n);
int l2(int n); 

#endif

