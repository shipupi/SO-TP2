#ifndef EXTRA_H
#define EXTRA_H

#include "shell.h"

int initializeShortcutsArray(SHORTCUT scArr[]);
void loadShortcut(SHORTCUT scArr[], char * id, uintptr_t ptr);
int testMemoryManager();
int printNumbers();
int printNumbers1();
int printNumbers2();
int ps();
void sleep();
void sleepPID(int pid);
void wakePID(int pid);
void prodCons();
void addProd();
void addCons();
void testIPC();
void testLottery();
void testReadWriteIPC();
void testReadWriteIPC2();
void testReadWriteIPC3();
int ticks();
void test_mutex();
void list_mutex();
void mut1();
void mut2();
void pipe();
#endif

