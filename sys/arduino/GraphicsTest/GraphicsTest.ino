/*

  GraphicsTest.ino
  
  Generate some example graphics

  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <SPI.h>
#include "Ucglib.h"

/*
  Available constructors:
    Ucglib8BitPortD		- Output via 8 Bit parallel port D and four control ports. Only available for Atmel AVR
    Ucglib8Bit			- Generic 8 Bit parallel interface, any combination of 12 ports can be used.
    Ucglib4WireHWSPI	- Serial output with Arduino SPI library, three extra ports reqired.
    Ucglib4WireSWSPI	- Software SPI emulation, any combination of 5 ports can be used.

  Supported Devices [and extension procedures]:
    ucg_dev_ssd1351_18x128x128_ilsoft	[ucg_ext_none, ucg_ext_ssd1351_18]
    ucg_dev_ili9325_18x240x320_itdb02	[ucg_ext_none, ucg_ext_ili9325_18]
    ucg_dev_ili9341_18x240x320		[ucg_ext_none, ucg_ext_ili9341_18]


  >>> Please uncomment (and update) one of the following constructors. <<<
  
*/
Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib4WireHWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);			/* Display connected to HW SPI, use SPI Library */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Uno, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 76, /*sda=*/ 75, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Due, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 52, /*sda=*/ 51, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Mega, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, /*scl=*/ 7, /*sda=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);

#define T 4000
#define DLY() delay(2000)

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
uint8_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return z;
}


void ucglib_graphics_test(void)
{
  ucg.setColor(0, 0, 40, 80);
  ucg.setColor(1, 80, 0, 40);
  ucg.setColor(2, 255, 0, 255);
  ucg.setColor(3, 0, 255, 255);
  
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());

  ucg.setColor(255, 168, 0);
  ucg.setPrintPos(2,18);
  ucg.print("Ucglib");
  ucg.setPrintPos(2,18+20);
  ucg.print("GraphicsTest");

  DLY();
}

void gradient(void)
{  
  ucg.setColor(0, 0, 255, 0);
  ucg.setColor(1, 255, 0, 0);
  ucg.setColor(2, 255, 0, 255);
  ucg.setColor(3, 0, 255, 255);

  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());
  
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,18);
  ucg.print("GradientBox");

  ucg.setColor(0, 0, 255, 0);
  ucg.drawBox(2, 25, 8, 8);

  ucg.setColor(0, 255, 0, 0);
  ucg.drawBox(2+10, 25, 8, 8);

  ucg.setColor(0, 255, 0, 255);
  ucg.drawBox(2, 25+10, 8, 8);

  ucg.setColor(0, 0, 255, 255);
  ucg.drawBox(2+10, 25+10, 8, 8);

  DLY();
}

void box(void)
{
  ucg_int_t x, y, w, h;
  unsigned long m;
  
  ucg.setColor(0, 0, 40, 80);
  ucg.setColor(1, 60, 0, 40);
  ucg.setColor(2, 128, 0, 140);
  ucg.setColor(3, 0, 128, 140);  
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,18);
  ucg.print("Box");

  m = millis() + T;

  while( millis() < m )
  {
    ucg.setColor((lcg_rnd()&127)+127, (lcg_rnd()&127)+64, lcg_rnd() & 31);
    w = lcg_rnd() & 31;
    h = lcg_rnd() & 31;
    w += 10;
    h += 10;
    x = ((uint32_t)lcg_rnd()*(ucg.getWidth()-w))>>8;
    y = ((uint32_t)lcg_rnd()*(ucg.getHeight()-h-20))>>8;
    
    ucg.drawBox(x, y+20, w, h);
  }

}

void triangle(void)
{
  unsigned long m;
  
  ucg.setColor(0, 0, 80, 20);
  ucg.setColor(1, 60, 80, 20);
  ucg.setColor(2, 60, 120, 0);
  ucg.setColor(3, 0, 140, 30);  
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,18);
  ucg.print("Triangle");

  m = millis() + T;

  while( millis() < m )
  {
    ucg.setColor((lcg_rnd()&127)+127, lcg_rnd() & 31, (lcg_rnd()&127)+64);
    
    ucg.drawTriangle(
      ((uint32_t)lcg_rnd()*(ucg.getWidth()))>>8,
      (((uint32_t)lcg_rnd()*(ucg.getHeight()-20))>>8)+20,
      
      ((uint32_t)lcg_rnd()*(ucg.getWidth()))>>8,
      (((uint32_t)lcg_rnd()*(ucg.getHeight()-20))>>8)+20,
      
      ((uint32_t)lcg_rnd()*(ucg.getWidth()))>>8,
      (((uint32_t)lcg_rnd()*(ucg.getHeight()-20))>>8)+20
    );
    
  }

}

void text(void)
{
  ucg_int_t x, y, w, h, i;
  unsigned long m;
  
  ucg.setColor(0, 80, 40, 0);
  ucg.setColor(1, 60, 0, 40);
  ucg.setColor(2, 20, 0, 20);
  ucg.setColor(3, 60, 0, 0);  
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,18);
  ucg.print("Text");

  m = millis() + T;
  i = 0;
  while( millis() < m )
  {
    ucg.setColor(lcg_rnd() & 31, (lcg_rnd()&127)+127, (lcg_rnd()&127)+64);
    w = 40;
    h = 22;
    x = ((uint32_t)lcg_rnd()*(ucg.getWidth()-w))>>8;
    y = ((uint32_t)lcg_rnd()*(ucg.getHeight()-h))>>8;
    
    ucg.setPrintPos(x,y+h);
    ucg.setPrintDir((i>>2)&3);
    i++;
    ucg.print("Ucglib");
  }
  ucg.setPrintDir(0);

}

void fonts(void)
{
  ucg_int_t d = 5;
  ucg.setColor(0, 0, 40, 80);
  ucg.setColor(1, 150, 0, 200);
  ucg.setColor(2, 60, 0, 40);
  ucg.setColor(3, 0, 160, 160);
  
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());

  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,18);
  ucg.print("Fonts");
  
  ucg.setColor(255, 200, 170);
  ucg.setFont(ucg_font_helvB08r);
  ucg.setPrintPos(2,30+d);
  ucg.print("ABC abc 123");
  ucg.setFont(ucg_font_helvB10r);
  ucg.setPrintPos(2,45+d);
  ucg.print("ABC abc 123");
  ucg.setFont(ucg_font_helvB12r);
  ucg.setPrintPos(2,62+d);
  ucg.print("ABC abc 123");
  ucg.setFont(ucg_font_helvB14r);
  ucg.setPrintPos(2,79+d);
  ucg.print("ABC abc 123");
  ucg.setFont(ucg_font_helvB18r);
  ucg.setPrintPos(2,79+22+d);
  ucg.print("ABC abc 123");
  
  

  ucg.setFont(ucg_font_ncenR14r);
  DLY();
}


void setup(void)
{
  delay(1000);
  ucg.begin();
  ucg.setFont(ucg_font_ncenR14r);
  ucg.clearScreen();
}

void set_clip_range(void)
{
  ucg_int_t x, y, w, h;
  w = lcg_rnd() & 31;
  h = lcg_rnd() & 31;
  w += 25;
  h += 25;
  x = ((uint32_t)lcg_rnd()*(ucg.getWidth()-w-1))>>8;
  y = ((uint32_t)lcg_rnd()*(ucg.getHeight()-h-1))>>8;
  
  ucg.setClipRange(x, y, w, h);
}


uint8_t r = 4;
void loop(void)
{
  switch(r&3)
  {
    case 0: ucg.undoRotate(); break;
    case 1: ucg.setRotate90(); break;
    case 2: ucg.setRotate180(); break;
    default: ucg.setRotate270(); break;
  }
  
  if ( r > 3 )
  {
    ucg.clearScreen();
    set_clip_range();
  }
  
  r++;
  ucglib_graphics_test();
  triangle();
  fonts();  
  text();
  box();
  gradient();
  //ucg.clearScreen();
  DLY();
  ucg.setMaxClipRange();
}
