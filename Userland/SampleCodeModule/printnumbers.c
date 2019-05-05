
#include "stdio.h"
#include "syscalls.h"

int printNumbers() {
	int a =0, b=0;
	while(b < 20) {
		a++;
		if (a%25000000 == 0)
		{
			if (b == 10)
			{
				os_sleep();
			}
			b++;
			puint(b);
		}
	}
	return 1;
}