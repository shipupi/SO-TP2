#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
void * memcopy(void * destination, const void * source, uint64_t length);
void * memclear(void * buffer, uint64_t length);
#endif
