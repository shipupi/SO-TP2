#ifndef KEYMAP_H
#define KEYMAP_H

//Defines to save code (Source: http://www.plantation-productions.com/Webster/www.artofasm.com/DOS/pdf/apndxc.pdf)
#define CTRL		0x1D
#define LSHIFT		0x2A
#define RSHIFT		0x36
#define CAPS		0x3A
#define CTRL_UP		0x9D
#define LSHIFT_UP	0xAA
#define RSHIFT_UP	0xB6
#define LETTER_C	0x2E

//Given a Scan Code it returns the proper ASCII
char getAscii(unsigned int code);

//Given a Scan Code it returns the proper ASCII to the combination with SHIFT (Note to self: CTRL does not give a different ASCII, its just commands)
char getShiftAscii(unsigned int code);

char toLowerCase(char c);
char toUpperCase(char c);

#endif