#include "include/stdio.h"
#include "include/extra.h"
#include "include/vidio.h"
#include "include/syscalls.h"
#include "include/pong.h"

static int ticks = 0;


//PONG
static int bPosX;
static int bPosY;
static int bVecX;
static int bVecY;
static int bRandom;

static int scoreR;
static int rPosX;
static int rPosY;

static int scoreL;
static int lPosX;
static int lPosY;

static int ticksTillRefresh;
static int running;

void addPlayersLabels();
void addEdges();


//draws the limits on-screen
void setup(){

  ticksTillRefresh = ticksPerSecond()/6;
// Clear the screen
  os_clear();
  addEdges();
  //addSeparatorBar();
  addPlayersLabels();
  //both the ceiling and the floor.

  //fixme print score here
}

void eraseComponents(){
  drawRectangle(bPosX,bPosY,RADIUS,RADIUS,0,0,0);
  drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
  drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
}

void drawComponents(){

    drawRectangle(bPosX,bPosY,RADIUS,RADIUS,255,255,255);
    drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
    drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
}

void resetPositions(){

  bPosX = (RIGHT-LEFT)/2;
  bPosY = (BOT-TOP)/2;
  bVecX *= -1;
  bVecY = 0;

  lPosY = (BOT-TOP)/2;
  lPosX = LEFT + (RWIDTH);

  rPosY = (BOT-TOP)/2;
  rPosX = RIGHT - (RWIDTH);

  drawComponents();

}

//fixme me falla durisimo el codigo
void addGame(){

  resetPositions();
  bRandom = 100;
  bVecX =XBSPEED;
  scoreL = 0;
  scoreR = 0;

}

void addEdges() {
  drawWhiteRectangleFromCorner(0, 0, RIGHT, VERTICALPADDING);
  drawWhiteRectangleFromCorner(0, BOT - VERTICALPADDING, RIGHT, VERTICALPADDING);
  //drawWhiteRectangleFromCorner((RIGHT-LEFT)/2,BOT+RWIDTH/2,(RIGHT-LEFT)/2,(BOT-TOP)/2);
}

void addSeparatorBar() {
  uint64_t availableSpaceY = BOT - 2 * VERTICALPADDING;
  uint64_t separatorHeight = (availableSpaceY - (SEPARATORSPACING * (SEPARATORBARS)))/ SEPARATORBARS;
  uint64_t separatorX = (RIGHT - SEPARATORWIDTH) / 2;
  uint64_t currY = VERTICALPADDING + (SEPARATORSPACING / 2);
  for (uint64_t i = 0; i < SEPARATORBARS; i++)
  {
    drawWhiteRectangleFromCorner(separatorX, currY, SEPARATORWIDTH, separatorHeight);
    currY += separatorHeight + SEPARATORSPACING;
  }
}

void addPlayersLabels() {
  char p1[] ={ scoreL + '0',0 };
  char p2[] = { scoreR + '0',0 };
  drawStringInScreen((RIGHT-LEFT)/2-200,100, p1, 255,255,255, 3);
  drawStringInScreen((RIGHT-LEFT)/2+200,100, p2, 255,255,255, 3);
}
void erasePlayersLabels() {
  char p1[] ={ scoreL + '0',0 };
  char p2[] = { scoreR + '0',0 };
  drawStringInScreen((RIGHT-LEFT)/2-200,100, p1, 0,0,0, 3);
  drawStringInScreen((RIGHT-LEFT)/2+200,100, p2, 0,0,0, 3);
}

//resets ball movement, increases score, plays sound
void goal(){
  os_beep();
  int startP = os_ticks();
  while(os_ticks()-startP < 5){};
  os_unbeep();
  eraseComponents();
  addPlayersLabels();
  resetPositions();
  while(os_ticks()-startP < 10){};
}
void goalL(){
  erasePlayersLabels();
  if(++scoreR < 5){
    goal();
  } else{
    endGame();
  }
}
void goalR(){
  erasePlayersLabels();
  if(++scoreL < 5){
    goal();
  } else{
    endGame();
  }
}

void endGame(){

  os_beep();
  int startP = os_ticks();
  while(os_ticks()-startP < 5){};
  os_unbeep();
  eraseComponents();
  resetPositions();

  char win[] = "YOU WIN :)";
  char lose[] = "YOU LOSE :(";
  char tie[] = "TIE";

  if(scoreL > scoreR){
    drawStringInScreen(LEFT+160,200, win, 255,255,255, 3);
    drawStringInScreen((RIGHT-LEFT)/2+128,200, lose, 255,255,255, 3);
  }else if(scoreR > scoreL){
    drawStringInScreen(LEFT+160,200, lose, 255,255,255, 3);
    drawStringInScreen((RIGHT-LEFT)/2+128,200, win, 255,255,255, 3);
  }else{
    drawStringInScreen(LEFT+160,200, tie, 255,255,255, 3);
    drawStringInScreen((RIGHT-LEFT)/2+160,200, tie, 255,255,255, 3);
  }
  drawRectangle(bPosX,bPosY,RADIUS,RADIUS,0,0,0);

  bVecX = 0;
  bVecY = 0;

}

void moveUpR(){
  if(rPosY - RHEIGHT/2 > TOP + VERTICALPADDING){
    drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
    rPosY -= SPEED;
    drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
  }
}
void moveDownR(){
  if(rPosY + RHEIGHT/2 < BOT - VERTICALPADDING){
    drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
    rPosY += SPEED;
    drawRectangle(rPosX,rPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
  }
}

void moveUpL(){
  if(lPosY - RHEIGHT/2 > TOP + VERTICALPADDING){
    drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
    lPosY -= SPEED;
    drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
  }
}
void moveDownL(){
  if(lPosY + RHEIGHT/2 < BOT - VERTICALPADDING){
    drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,0,0,0);
    lPosY += SPEED;
    drawRectangle(lPosX,lPosY,RWIDTH/2,RHEIGHT/2,255,255,255);
  }
}

int capturedR(){
  if((rPosY - RHEIGHT/2 <= bPosY+RADIUS) && (rPosY + RHEIGHT/2 >= bPosY-RADIUS)){
      return 1;
  }
  return 0;
}

int capturedL(){
  if((lPosY - RHEIGHT/2 <= bPosY+RADIUS) && (lPosY + RHEIGHT/2 >= bPosY-RADIUS)){
      return 1;
  }
  return 0;
}

void bounce(){
  bVecX *= -1;
  randomize();
  bVecY = bRandom - 64;

  if((bVecY+bPosY-RADIUS <= TOP+VERTICALPADDING) || (bVecY+bPosY+RADIUS >= BOT-VERTICALPADDING)){
    bVecY *= -1;
  }
}

void moveBall(){
  //refresh the vector
  //if it hits the ceiling or the floor
  if((bPosY+ bVecY +RADIUS >= BOT-VERTICALPADDING) || (bPosY + bVecY -RADIUS <= TOP+VERTICALPADDING)){
    bVecY *= -1; //same x component with inverted y
  }
  //if it is a racket or goal
  //case: right
  if(bPosX+RADIUS >= RIGHT-2*RWIDTH){
    if(capturedR()){
      bounce();
    }else{
      goalR();
    }
  }else if(bPosX-RADIUS <= LEFT+2*RWIDTH){
    if(capturedL()){
      bounce();
    }else{
      goalL();
    }
  }
  //refresh the position
  //fixme erase ball and draw ball
  drawRectangle(bPosX,bPosY,RADIUS,RADIUS,0,0,0);
  bPosX += bVecX;
  bPosY += bVecY;
  drawRectangle(bPosX,bPosY,RADIUS,RADIUS,255,255,255);
}

void randomize(){
  //returns a number between 8, 1288
  bRandom = ((bRandom*37)%30)*4+8;
  return;
}


int pong(){
  //clear the board
  setup();
  addGame();

  running = 1;

  int auxTicks;
  char c;

  //improve while conditions
  while(running){

    auxTicks = os_ticks();

    if(auxTicks >= (ticks + ticksTillRefresh)) {   //Change to fit the condition we want
      ticks = os_ticks();
        moveBall();
        addPlayersLabels();
        addSeparatorBar();
      //We empty the buffer that was loaded since last time
      while ((c = getCharWithZero())) {

        switch (c) {
          case 'w':
          case 'W':
            //Call move function
            moveUpL();
            break;
          case 's':
          case 'S':
            //Call move function
            moveDownL();
            break;
          case 'i':
          case 'I':
            moveUpR();
            break;
          case 'k':
          case 'K':
            moveDownR();
            break;
          case -1:
            //Exit
            running = 0;
            //sendGame();
            break;
        }
      }

      //Call whatever other function you need
      //refresh();  //Repaint function
    }
  }


  os_clear();
  return 0;

}
