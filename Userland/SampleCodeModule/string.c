#include "string.h"

int strcmp(char * str1, char * str2) {
	while(1) {
		if (*str1 != *str2) {
			return *str1 < *str2 ? -1 : 1;
		} else if (*str1 == '\0') {
			return 0;
		}
		str1++;
		str2++;
	}
}


int strlen(char * string) {
	int i = 0;
	while(*(string + i)) {
		i++;
	} 
	return i;
} 

