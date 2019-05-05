
#include "stdio.h"

int printNumbers() {
	int a =0, b=0;
	while(b < 1000) {
		a++;
		if (a%25000000 == 0)
		{
			b++;
			puint(b);
		}
	}
	return 1;
}