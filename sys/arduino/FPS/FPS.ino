#include "Ucglib.h"

Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_dev_ic_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );

void setup(void)
{
  delay(1000);
  ucg.begin();
}

/*
  Linear Congruential Generator (LCG)
  z = (a*z + c) % m;  
  m = 256 (8 Bit)
  
  for period:
  a-1: dividable by 2
  a-1: multiple of 4
  c: not dividable by 2
  
    c = 17
    a-1 = 64 --> a = 65

*/


uint8_t z = 127;	// start value
uint8_t lcg_rnd(void)
{
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return z;
}





void draw_text(void) {
  ucg.setFont(ucg_font_ncenR14r);
  //ucg.setColor(255, 255, 255);
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  ucg.setPrintPos(0,20);
  ucg.print("The quick brown");
  ucg.setPrintPos(0,40);
  ucg.print("fox jumps over");
  ucg.setPrintPos(0,60);
  ucg.print("the lazy dog");
}


// returns FPS*10
uint16_t measure(void (*draw_fn)(void)) {
  uint16_t FPS10 = 0;
  uint32_t time;

  ucg.clearScreen();

  time = millis() + 10*1000;
  do {
    draw_fn();
    FPS10++;
  } while( millis() < time );
  
  return FPS10;  
}


static const unsigned char u8d_tab[3]  = { 100, 10, 1 } ;
const char *u8dp(char * dest, uint8_t v)
{
  uint8_t pos;
  uint8_t d;
  uint8_t c;
  for( pos = 0; pos < 3; pos++ )
  {
      d = '0';
      c = *(u8d_tab+pos);
      while( v >= c )
      {
	v -= c;
	d++;
      }
      dest[pos] = d;
  }  
  dest[3] = '\0';
  return dest;
}

/* v = value, d = number of digits */
const char *u8d(uint8_t v, uint8_t d)
{
  static char buf[8];
  d = 3-d;
  return u8dp(buf, v) + d;
}

const char *convert_FPS(uint16_t fps) {
  static char buf[6];
  strcpy(buf, u8d( (uint8_t)(fps/10), 3));
  buf[3] =  '.';
  buf[4] = (fps % 10) + '0';
  buf[5] = '\0';
  return buf;
}

void show_result(const char *s, uint16_t fps)  {
  ucg.clearScreen();
  ucg.setFont(ucg_font_helvR18r);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(0,25);
  ucg.print(s);
  ucg.setPrintPos(0,50);
  ucg.print(convert_FPS(fps));  
  delay(2000);
}

void loop(void)
{
  show_result("Text", measure(draw_text));
  delay(500);
  
}