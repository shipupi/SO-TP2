#ifndef NAIVEKEYBOARD_H
#define NAIVEKEYBOARD_H

void keyboard_handler();
char getChar();
void addChar(char c);		//I would like to make this one private, see if i can put it inside .c file or something
void handleCtrl(unsigned int code); //same as above
void initializeKeyboardDriver();

#define KEYBOARD_IPC_NAME "KEYBOARD_IPC"
#define KEYBOARD_IPC_SIZE 255
#endif