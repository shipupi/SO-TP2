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

int pow(int base,int n){
	int i , p;
	p=1;
	for(i=1;i<=n;++i){
		p = p*base;
	}
	return p;
}

int to_num(char * s , int dim){
	int n;
	for(int i = 0 ; s[i]!='\0';i++){
		n += pow(10,dim - i - 1)*(s[i]-'0');
	}
	return n;
}

void numberToString(uint64_t number , char * string){
	int i = 1;
	while(number > 10){
		string[i] = (number % 10) + '0';
		number = number / 10;
		i++;
	}
	string[0] = (number % 10) + '0';
}
