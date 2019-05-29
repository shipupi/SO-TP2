#include <stdint.h>
#include "include/scheduler/PCB.h"
#include "include/ipc/ipc.h"
#include "include/memoryManager/memoryManager.h"

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

//Poorman's printf
void printf(char * str) {
	ipc_write(DEFAULT_FDOUT, str, MAXFDSIZE);
}


void printn(uint64_t num) {
  char string[10];
  int remainder;
  int index = 0;
  int reverseIndex = 0;
  char aux;
  int length;
  if (num == 0){
    string[0] = '0';
    printf(string);
    return;
  }
  else {
    while (num > 0){
      remainder = num % 10;
      string[index++] = remainder + '0';
      num /= 10;
    }
  }
  string[index] = 0;
  length = index;
  while (reverseIndex < length / 2){
    aux = string[--index];
    string[index] = string[reverseIndex];
    string[reverseIndex++] = aux;
  }
  printf(string);
}