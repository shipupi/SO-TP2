#include <stdint.h>
#include <string.h>
#include "lib.h"
#include "include/drivers/vesaDriver.h"

typedef struct ModeInfoBlock {
  uint16_t attributes;
  uint8_t winA,winB;
  uint16_t granularity;
  uint16_t winsize;
  uint16_t segmentA, segmentB;
  uint32_t realFctPtr;
  uint16_t pitch; // bytes per scanline
  uint16_t Xres, Yres;
  uint8_t Wchar, Ychar, planes, bpp, banks;
  uint8_t memory_model, bank_size, image_pages;
  uint8_t reserved0;

  uint8_t red_mask, red_position;
  uint8_t green_mask, green_position;
  uint8_t blue_mask, blue_position;
  uint8_t rsv_mask, rsv_position;
  uint8_t directcolor_attributes;

  uint32_t physbase;  // your LFB (Linear Framebuffer) address ;)
  uint32_t reserved1;
  uint16_t reserved2;



} ModeInfoBlock;


const char fontWidth = 8;
static ModeInfoBlock *infoBlock = (ModeInfoBlock*)0x0000000000005C00;



// int maxLines = 38;
// static int cursorXStart = 10;
static int cursorX = 10;
static int cursorY = 10;
static int cursorX2 = 10;
static int cursorY2 = 10;
static int splits = 1;

static int cursorX2Start;
// static int maxY = cursorYStart + 20 * maxLines;
// const int cursorYStart = 10;

char fonts[130][8] = {
    
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0000 (nul)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0001
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0002
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0003
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0004
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0005
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0006
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0007
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0008
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0009
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0010
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0011
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0012
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0013
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0014
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0015
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0016
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0017
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0018
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0019
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001A
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001B
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001C
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001D
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001E
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001F
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0020 (space)
    { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // U+0021 (!)
    { 0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0022 (")
    { 0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, // U+0023 (#)
    { 0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, // U+0024 ($)
    { 0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, // U+0025 (%)
    { 0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, // U+0026 (&)
    { 0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0027 (')
    { 0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, // U+0028 (()
    { 0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, // U+0029 ())
    { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // U+002A (*)
    { 0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, // U+002B (+)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+002C (,)
    { 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // U+002D (-)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+002E (.)
    { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, // U+002F (/)
    { 0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, // U+0030 (0)
    { 0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, // U+0031 (1)
    { 0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, // U+0032 (2)
    { 0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, // U+0033 (3)
    { 0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, // U+0034 (4)
    { 0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, // U+0035 (5)
    { 0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, // U+0036 (6)
    { 0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, // U+0037 (7)
    { 0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, // U+0038 (8)
    { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, // U+0039 (9)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+003A (:)
    { 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+003B (//)
    { 0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, // U+003C (<)
    { 0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00}, // U+003D (=)
    { 0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // U+003E (>)
    { 0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, // U+003F (?)
    { 0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, // U+0040 (@)
    { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, // U+0041 (A)
    { 0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, // U+0042 (B)
    { 0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, // U+0043 (C)
    { 0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, // U+0044 (D)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, // U+0045 (E)
    { 0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, // U+0046 (F)
    { 0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, // U+0047 (G)
    { 0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, // U+0048 (H)
    { 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0049 (I)
    { 0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, // U+004A (J)
    { 0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, // U+004B (K)
    { 0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, // U+004C (L)
    { 0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, // U+004D (M)
    { 0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, // U+004E (N)
    { 0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, // U+004F (O)
    { 0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00}, // U+0050 (P)
    { 0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, // U+0051 (Q)
    { 0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00}, // U+0052 (R)
    { 0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, // U+0053 (S)
    { 0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0054 (T)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, // U+0055 (U)
    { 0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0056 (V)
    { 0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, // U+0057 (W)
    { 0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, // U+0058 (X)
    { 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, // U+0059 (Y)
    { 0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, // U+005A (Z)
    { 0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, // U+005B ([)
    { 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // U+005C (\)
    { 0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, // U+005D (])
    { 0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, // U+005E (^)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // U+005F (_)
    { 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0060 (`)
    { 0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, // U+0061 (a)
    { 0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, // U+0062 (b)
    { 0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, // U+0063 (c)
    { 0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00}, // U+0064 (d)
    { 0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00}, // U+0065 (e)
    { 0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00}, // U+0066 (f)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0067 (g)
    { 0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, // U+0068 (h)
    { 0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0069 (i)
    { 0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E}, // U+006A (j)
    { 0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, // U+006B (k)
    { 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+006C (l)
    { 0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, // U+006D (m)
    { 0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00}, // U+006E (n)
    { 0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, // U+006F (o)
    { 0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, // U+0070 (p)
    { 0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, // U+0071 (q)
    { 0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, // U+0072 (r)
    { 0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, // U+0073 (s)
    { 0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, // U+0074 (t)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, // U+0075 (u)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0076 (v)
    { 0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, // U+0077 (w)
    { 0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, // U+0078 (x)
    { 0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0079 (y)
    { 0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, // U+007A (z)
    { 0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, // U+007B ({)
    { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, // U+007C (|)
    { 0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, // U+007D (})
    { 0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+007E (~)
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+007F
    { 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18, 0x00}, // U+0080
    { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} // U+0080
};


// Local functions headers
int strlength(const char * str) {
    int i = 0;
    while(*(str+i)) {
        i++;
    }
    return i;
}



void putPixel(uint64_t x,uint64_t y, unsigned char r, unsigned char g, unsigned char b) {

  char* screen = (char *)(uintptr_t) infoBlock->physbase + x*infoBlock->bpp / 8 + y*infoBlock->pitch;
  screen[0] = b;              // BLUE
  screen[1] = g;              // GREEN
  screen[2] = r;              // RED
}


// Hacer for i for j de putpixel para rectangulo no rinde, porque tiene que recalcular screen muchas veces
// Esta forma es mas eficiente
void fillRect(uint64_t x, unsigned char y, uint16_t width, uint16_t height, unsigned char r, unsigned char g, unsigned char b) {
  unsigned char pixelWidth = infoBlock->bpp / 8;

  char* pos = (char *)(uintptr_t) infoBlock->physbase + x*pixelWidth + y*infoBlock->pitch;
  int i, j;

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      pos[j*pixelWidth] = b;
      pos[j*pixelWidth + 1] = g;
      pos[j*pixelWidth + 2] = r;
    }
    pos+= infoBlock->pitch;
  }
}





// Esta funcion difiere de drawchar en tanto a que no hace el calculo de pos*, el drawstring lo calcula y ya cambia automaticamente la posicion
// y se la pasa a esta funcion con la posicion ya calculada
void drawCharForString(char* pos, unsigned char myChar, unsigned char pixelWidth, int pitch, unsigned char r, unsigned char g, unsigned char b) {


  int i,j;
  for (i = 0; i < 8; i++)
  {
//  i es la fila
    for (j = 0; j < 8; j++)
// j es la columna
    {
      if (fonts[myChar][i] & (1 << j))
      {
        pos[j*pixelWidth]  = b;
        pos[j*pixelWidth+1]  = g;
        pos[j*pixelWidth+2] = r; 
      }
    }
    pos += pitch;
  }
}

void drawChar(int  x, int  y, unsigned char myChar, unsigned char r, unsigned char g, unsigned char b) {
  unsigned char pixelWidth = infoBlock->bpp / 8;
  int pitch = infoBlock->pitch;
  char* pos = (char *)(uintptr_t) infoBlock->physbase + x*pixelWidth + y*pitch;
  // char a[8] = { 0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00};
//  Las fonts son arrays de 8 bytes, si cada bit es una posicion que vale 0 o 1, son 64 pixels descriptos
// Vamos a pintar los pixels que tienen un 1 con el color que viene por parametro, y de negro los que no vienen por parametro
// Alternativamente puedo dejar los que no tienen 1 como estaba, esto me permitiria dejar el color de fondo que este de antes
// El problema con esto es que si habia otra letra escrita en el mismo lugar, se van a overlapear y na va a pisar bien
// Mas adelante veo si surjen problemas con esto y veo como resolverlos
  int i,j;
  for (i = 0; i < 8; i++)
  {
//  i es la fila
    for (j = 0; j < 8; j++)
// j es la columna
    {
      if (fonts[myChar][i] & (1<<j))
      {
        pos[j*pixelWidth]  = b;
        pos[j*pixelWidth+1]  = g;
        pos[j*pixelWidth+2] = r; 
      }
    }
    pos+= pitch;
  }
}


void drawString(unsigned char  x, unsigned char  y, char* string, unsigned char r, unsigned char g, unsigned char b) {
  unsigned char pixelWidth = infoBlock->bpp / 8;
  int pitch = infoBlock->pitch;
  char* pos = (char *)(uintptr_t)  infoBlock->physbase + x*pixelWidth + y*pitch;
  int len = strlength(string);
  for (int i = 0; i < len; i++)
  {
    drawCharForString(pos, string[i],pixelWidth,pitch,r,g,b);
    pos += fontWidth * pixelWidth;
    /* code */
  }
}

void deleteChar(int section) {
  int* cx;
  int* cy;
  int cxs;
  if(section == 2 && splits == 2) {
    cx = &cursorX2;
    cy = &cursorY2;
    cxs = cursorXStart + infoBlock->Xres / 2;
  } else {
    cx = &cursorX;
    cy = &cursorY;
    cxs = cursorXStart;
  }


  if (*cx == cxs)
  {
    prevLine(section);
  }
  if (*cx > cxs)
  {
    *cx -= 8;
    drawChar(*cx, *cy, 129, 0,0,0);
  }
}


void prevLine(int section) {
  if(section == 2 && splits == 2) {
    cursorY2 -= 20;
    cursorX2 = infoBlock->Xres - 14;
  } else if (section == 1 && splits == 2) {
    cursorY -= 20;
    cursorX = (infoBlock->Xres / 2) - 14; 
  } else if( splits == 1) {
    cursorY -= 20;
    cursorX = infoBlock->Xres - 14;
  }
 } 

void nextLine(int section) {

  if(section == 2 && splits == 2) {
    cursorX2 = cursorX2Start;
    cursorY2 += 20; 
    if (cursorY2 == maxY)
    {
      shiftUp(section);
    }
  } else if (section == 1 && splits == 2) {
  
    cursorX = cursorXStart;
    cursorY += 20; 
    if (cursorY == maxY)
    {
      shiftUp(section);
    }

  } else if( splits == 1) {
    cursorX = cursorXStart;
    cursorY += 20; 
    if (cursorY == maxY)
    {
      shiftUp(section);
    }
  }    

}

int maxX(int section) {
  if(section == 1 && splits == 2) {
   return (infoBlock->Xres / 2) - 5 - cursorXStart;
  } else {
   return infoBlock->Xres - 5 - cursorXStart;
  }
}

void printChar(unsigned char myChar, unsigned char r, unsigned char g, unsigned char b, int section) {
  // TODO - Implementar secciones a este 
  if (myChar == '\n') {
      nextLine(section);
  } else if (myChar == '\b') {
      deleteChar(section);
  } else {
    drawChar(cursorX, cursorY, myChar, r,g,b);
    cursorX += 8;
    if (cursorX >= maxX(section))
    {
      nextLine(section);
    }
  }
}

void printWhiteString(char * str){
  printString(str, 255, 255, 255, 1);
}

void printString(char *str, unsigned char r, unsigned char g, unsigned char b, int section) {
  unsigned char pixelWidth = infoBlock->bpp / 8;
  int pitch = infoBlock->pitch;
  char* pos;
  int* cx;
  int* cy;

  if (splits == 1)  section = 1;
  if (section == 2) {
    cx = &cursorX2;
    cy = &cursorY2;
  } else {
    cx = &cursorX;
    cy = &cursorY;
  }
  pos = (char *)(uintptr_t) infoBlock->physbase + (*cx)*pixelWidth + (*cy)*pitch;
  int len = strlength(str);
  char c;
  for (int i = 0; i < len; i++)
  {
    c = str[i];
    if ( c == 0 ) {
      return;
    } else if (c == '\n') {
      nextLine(section);
    } else if (c == '\b') {
      deleteChar(section);
    } else {
      drawCharForString(pos, str[i],pixelWidth,pitch,r,g,b);
      (*cx) += 8;
      if ((*cx) >= maxX(section))
      {
        nextLine(section);
        pos = (char *)(uintptr_t) infoBlock->physbase + (*cx)*pixelWidth + (*cy)*pitch;
      } else {
        pos += fontWidth * pixelWidth;
      }
    }
  }

}

void shiftUp(int section) {
    
  // FALTA ARREGLAR ESTA FUNCION ( SI LA PANTALLA ESTA PARTIDA NO PUEDO COPIAR UN BLOQUE ENTERO, TENGO QUE 
  // COPIAR VARIOS BLOQUES A LA VEZ) 
  int pitch = infoBlock->pitch;
  int srcY = cursorYStart + 20;
  int destY = cursorYStart;
  char* dest;
  char* src;
  int size;
  if(splits == 2 && section == 2) {
    dest = (char *)(uintptr_t) infoBlock->physbase + destY*pitch + cursorX2Start * infoBlock->bpp / 8;
    src = (char *)(uintptr_t) infoBlock->physbase + srcY*pitch + cursorX2Start * infoBlock->bpp / 8;
    cursorY2 -= 20;
    // src[0] = 0;
    // src[1] = 0;
    // src[2] = 255;
  } else if (splits == 2 && section == 1) {
    dest = (char *)(uintptr_t) infoBlock->physbase + destY*pitch;
    src = (char *)(uintptr_t) infoBlock->physbase + srcY*pitch;
    cursorY -= 20;
  } else {
    // Hay solo 1 split, puedo mover todo el bloque junto
    dest = (char *)(uintptr_t) infoBlock->physbase + destY*pitch;
    src = (char *)(uintptr_t) infoBlock->physbase + srcY*pitch;
    size = infoBlock->Xres * pitch;
    memcpy(dest, src, size);
    cursorY -= 20;
    return;
  }

  // Hay 2 splits, tengo que ir copiando linea por linea para arriba

  // Checkeo de que los puntos esten
  
  size = (infoBlock->Xres / 2) * infoBlock->bpp / 8;
  int i;
  for (i = 0; i < infoBlock->Yres * 2; ++i) {
    memcpy(dest, src, size);
    dest += pitch;
    src += pitch;
  }

}

void copyLine() {
   int pitch = infoBlock->pitch;
   int destY = cursorYStart;
   char* dest = (char *)(uintptr_t) infoBlock->physbase + destY*pitch;
   int srcY = cursorYStart + 20;
   char* src = (char *)(uintptr_t) infoBlock->physbase + srcY*pitch;
   int size = infoBlock->Xres * pitch * 20;
   memcpy(src,dest, size);
}


void clearFrom(int x, int y) {
  fillRect(x,y, (infoBlock->Xres - x), (infoBlock->Yres - y), 0,0,0);
}

void clearAll() {
  clearFrom(0,0);
  cursorX = cursorXStart;
  cursorY = cursorYStart;
  
  if(splits > 1) {
    drawSplitSeparator();
    cursorX2 = cursorX2Start;
    cursorY2 = cursorYStart;
  }
}

void printInt(int num) {
  char string[10];
  int remainder;
  int index = 0;
  int reverseIndex = 0;
  int i;
  char aux;
  int length;
  int negative = 0;

  if (num < 0) {
    negative = 1;
    num = num * -1;
  }
  if (num == 0){
    string[0] = '0';
    printWhiteString(string);
    return;
  }
  else {
    while (num > 0){
      remainder = num % 10;
      string[index++] = remainder + '0';
      num /= 10;
    }
  }
  string[index] = 0;
  length = index;
  while (reverseIndex < length / 2){
    aux = string[--index];
    string[index] = string[reverseIndex];
    string[reverseIndex++] = aux;
  }

  if(negative) {
    for (i = length; i> 0; i--) {
      string[i] = string[i-1];
    }
    string[0] = '-';
  }
  printWhiteString(string);
}

void pl(char * string) {
  nextLine(1);
  printWhiteString(string);
}

void initializeVideoDriver() {
   cursorX2Start = cursorXStart + infoBlock->Xres / 2;
}

void drawSplitSeparator() {  fillRect(512, 0, 4, infoBlock->Yres, 255, 0, 0);
}

void clearSplitSeparator() {

}

void vesa_addSplit() {
  splits = 2;
  clearAll();
}

void vesa_removeSplit() {
  printWhiteString("remoing split?");
  splits = 1;
  clearSplitSeparator();

}