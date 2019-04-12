#include "stdio.h"
#include "syscalls.h"

char getChar() {
	char c = 0;
	while(1) {
		read(0, &c, 1);	//Get 1 char from STDIN and save it in c
		if (c == -1 || (c > 0 && c < 128)) {
			return c;
		}
	}
}

char getCharWithZero() {
	char c = 0;
	while(1) {
		read(0, &c, 1);	//Get 1 char from STDIN and save it in c
		if (c >= -1 && c < 128) {
			return c;
		}
	}
}

void putChar(char c) {
	write(1, &c, 1); 	//Write 1 char from &c in STDOUT
}

//Poorman's printf
void printf(char * str) {
	while(*str != '\0') {
		putChar(*str);
		str++;
	}
}

void printInt(int num) {
	char string[10];
	int remainder;
	int index = 0;
	int reverseIndex = 0;
	char aux;
	if (num == 0){
		string[0] = '0';
	}
	else {
		while (num > 0){
			remainder = num % 10;
			string[index++] = remainder + '0';
			num /= 10;
		}
	}
	string[index] = 0;
	while (reverseIndex < index/2){
		aux = string[--index];
		string[reverseIndex] = aux;
		string[index] = string[reverseIndex++];
	}
	printf(string);
}

//Poorman's scanf
void scanf(char *str, int bytes) {
	char c;
	int i = 0;
	while ((c = getChar()) != '\n' && i < bytes - 1) {
		if (c == '\b') {
			if (i > 0) {
				putChar(c);
				i--;
			}
		} else {
			putChar(c);
			str[i++] = c;
		}
	}

	str[i] = 0; //To mark the end of the string
}