
#include "stdio.h"
#include "syscalls.h"

int printNumbers() {
	int a =0, b=0;
	while(b < 5) {
		a++;
		if (a%25000000 == 0)
		{
			b++;
			puint(b);
		}
	}
	return 1;
}


int printNumbers2() {
	int a =0, b=0;
	while(b < 10000) {
		a++;
		if (a%250000 == 0)
		{
			b++;
			// puint(2);
		}
	}
	return 1;
}

int printNumbers1() {
	int a =0, b=0;
	while(b < 10000) {
		a++;
		if (a%250000 == 0)
		{
			b++;
			// puint(1);
		}
	}
	return 1;
}