#ifndef PONG_H
#define PONG_H
#include "vidio.h"
#include "stdio.h"
#include "syscalls.h"
#include "extra.h"


//window borders
#define TOP 0
#define BOT 768
#define LEFT 0
#define RIGHT 1024

#define VERTICALPADDING 32

#define SEPARATORWIDTH 8
#define SEPARATORSPACING 24
#define SEPARATORBARS 12

//racket dimensions
#define RHEIGHT 128
#define RWIDTH 32
#define SPEED 48

//ball size
#define RADIUS 16
#define XBSPEED 64

void setup();

void eraseComponents();
void drawComponents();
void resetPositions();
void addGame();
void addEdges();
void addSeparatorBar();
void addPlayersLabels();
void goal();

int capturedR();
int capturedL();

void randomize();
void bounce();
void moveBall();
int pong();
void endGame();

#endif
