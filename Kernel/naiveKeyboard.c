#include "include/drivers/naiveKeyboard.h"
#include "include/naiveLegacy/naiveConsole.h"
#include "include/pure/getKey.h"
#include "include/drivers/keyMap.h"
#include "include/memoryManager/memoryManager.h"
#include "include/ipc/ipc.h"
#include "include/drivers/vesaDriver.h"
#include "include/scheduler/PCB.h"
#include "include/scheduler/scheduler.h"
#include "include/interrupts.h"
#include "include/utils.h"

//150 was chosen at random
#define BUFFER_SIZE 200

//Because C has no booleans
#define TRUE 1
#define FALSE !TRUE

//We are going to use a cyclic buffer, hopefully we never run out of space
static char buffer[BUFFER_SIZE] = {1};
static char letter[3] = {1,0,0};

static int readIndex = 0;			//To know where in the buffer to start reading from
static int size = 0;				//To know how many chars are currently stored in buffer (beware of its cyclic nature)

//Flags to know if any of the combination keys are pressed, or if CAPS is locked
static int LSHIFT_LOCKED = FALSE;
static int RSHIFT_LOCKED = FALSE;
static int CAPS_LOCKED = FALSE;
static int CTRL_LOCKED = FALSE;

void keyboard_handler() {
	char c;
	//We get the key (Its going to get to us as scan code, we have to later use a map to get the ascii)
	unsigned int code = getKey();

	//Down Scan Codes go up to 0x79 and Up Scan Codes start on 0x81
	if(code < 0x80) {
		//We activate our flags accordingly
		switch(code) {
			case CTRL:
				CTRL_LOCKED = TRUE;	
				break;
			case CAPS:
				CAPS_LOCKED = !CAPS_LOCKED;
				break;
			case LSHIFT:
				LSHIFT_LOCKED = TRUE;
				break;
			case RSHIFT:
				RSHIFT_LOCKED = TRUE;
				break;
		}
		//Now we get Ascii from map to load on key, but what function of keyMap we call depends on our flags
		if(LSHIFT_LOCKED || RSHIFT_LOCKED) {
			c = getShiftAscii(code);
			if(c) {
				if(CAPS_LOCKED) {
					addChar(toLowerCase(c));
				} else {
					addChar(c);
				}
			}
		} else if (CTRL_LOCKED) {
			handleCtrl(code);
		} else if (CAPS_LOCKED) {
			c = getAscii(code);
			if(c) {
				addChar(toUpperCase(c));
			}
		} else {
			c = getAscii(code);
			if(c) {
				addChar(c);
			}
		}
	} else {
		//This means a key was released, we only care if the key is Shift or Ctrl
		switch(code) {
			case CTRL_UP:
				CTRL_LOCKED = FALSE;	
				break;
			case LSHIFT_UP:
				LSHIFT_LOCKED = FALSE;
				break;
			case RSHIFT_UP:
				RSHIFT_LOCKED = FALSE;
				break;
		}
	}

	if(pid() == -1) {
		halt();
	} else {
		return;
	}
	pl("After Keyboard Halt (If you are seeing this message. There is a bug");
}

//Handles the Ctrl + key, wich should not add a char to buffer, but execute an action (Try to do Ctrl + Shift + Alt)
void handleCtrl(unsigned int code) {
	//Do ctrl + c or z to exit and stuff like that
	switch(code) {
		case LETTER_C:
			addChar(-1);
			break;
	}
}

//It adds the char to the buffer
void addChar(char c) {
	letter[0] = c;
	ipc_write(DEFAULT_FDIN,letter,1);
}

//It returns the next char in buffer or 0 if buffer is empty
char getChar() {
	if (size <= 0) {
		return 0;
	}
	//We read the char, decrease size and increase index
	char c = buffer[readIndex];
	size--;
	readIndex = (readIndex + 1)%BUFFER_SIZE;

	return c;
}


void initializeKeyboardDriver() {
	//ipc_create(DEFAULT_FDIN,MAXFDSIZE);
}