/*

  UcgLogo.ino
  
  Draw the Ucglib Logo

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
//Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib4WireHWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);			/* Display connected to HW SPI, use SPI Library */
Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Uno, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 76, /*sda=*/ 75, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Due, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 52, /*sda=*/ 51, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Mega, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, /*scl=*/ 7, /*sda=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);


void upper_pin(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 7;
  ucg_int_t h = 6;
  ucg_SetColor(ucg, 0, 212, 212, 212);
  ucg_SetColor(ucg, 1, 200, 200, 200);
  ucg_SetColor(ucg, 2, 200, 200, 200);
  ucg_SetColor(ucg, 3, 188, 188, 188);
  ucg_DrawGradientBox(ucg, x, y, w, h);

  //ucg_DrawVLine(ucg, x+w, y+1, len);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x+w, y, h, 1);
}

void lower_pin(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 7;
  ucg_int_t h = 5;
  ucg_SetColor(ucg, 0, 212, 212, 212);
  ucg_SetColor(ucg, 1, 200, 200, 200);
  ucg_SetColor(ucg, 2, 200, 200, 200);
  ucg_SetColor(ucg, 3, 188, 188, 188);
  ucg_DrawGradientBox(ucg, x, y, w, h);

  //ucg_DrawVLine(ucg, x+w, y+1, len);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x+w, y, h, 1);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x, y+h, w, 0);
  ucg_SetColor(ucg, 0, 240, 240, 240);
  ucg_DrawPixel(ucg, x+w, y+h);
}

void ic_body(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 4*14+4;
  ucg_int_t h = 31;
  ucg_SetColor(ucg, 0, 60, 60, 60);
  ucg_SetColor(ucg, 1, 40, 40, 40);
  ucg_SetColor(ucg, 2, 48, 48, 48);
  ucg_SetColor(ucg, 3, 30, 30, 30);
  ucg_DrawGradientBox(ucg, x, y, w, h);
  
  ucg_SetColor(ucg, 0, 255, 168, 0);
  //ucg_SetColor(ucg, 0, 225, 168, 30);
  ucg_DrawDisc(ucg, x+w-1, y+h/2-1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);

  ucg_SetColor(ucg, 0, 60, 30, 0);
  //ucg_DrawDisc(ucg, x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);

  ucg_SetColor(ucg, 0, 50, 50, 50);
  ucg_SetColor(ucg, 0, 25, 25, 25);
  ucg_DrawDisc(ucg, x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);
  
  
}


void draw_ucg_logo(ucg_t *ucg)
{
  ucg_int_t a,b;
  
  //ucg_Init(ucg, ucg_sdl_dev_cb, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFont(ucg, ucg_font_ncenB24);  
  
  //ucg_SetRotate270(ucg);  
  //ucg_SetClipRange(ucg, 10,5,40,20);


  
  a = 2;
  b = 3;
  
  ucg_SetColor(ucg, 0, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 1, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 2, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 3, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, 0, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 1, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 0, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 3, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 2, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 0, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 1, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 2, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 3, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)*2/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 1, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 0, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 3, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 2, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)*3/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));
  
  
  upper_pin(ucg, 7+0*14, 4);
  upper_pin(ucg, 7+1*14, 4);
  upper_pin(ucg, 7+2*14, 4);
  upper_pin(ucg, 7+3*14, 4);
  
  ic_body(ucg, 2, 10);

  lower_pin(ucg, 7+0*14, 41);
  lower_pin(ucg, 7+1*14, 41);
  lower_pin(ucg, 7+2*14, 41);
  lower_pin(ucg, 7+3*14, 41);

  ucg_SetColor(ucg, 0, 135*a/b, 206*a/b, 250*a/b);
  ucg_DrawString(ucg, 63+1, 33+1, 0, "glib");

  ucg_SetColor(ucg, 0, 255, 168, 0);
  ucg_DrawGlyph(ucg, 26, 38, 0, 'U');
  ucg_DrawString(ucg, 63, 33, 0, "glib");

  ucg_SetColor(ucg, 0, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 1, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 2, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 3, 135*a/b, 206*a/b, 250*a/b);
  ucg_DrawGradientBox(ucg, 84+1, 42+1-6, 42, 4);

  ucg_SetColor(ucg, 0, 255, 180, 40);
  ucg_SetColor(ucg, 1, 235, 148, 0);
  //ucg_DrawGradientLine(ucg, 79, 42, 20, 0);
  ucg_SetColor(ucg, 2, 245, 158, 0);
  ucg_SetColor(ucg, 3, 220, 138, 0);
  ucg_DrawGradientBox(ucg, 84, 42-6, 42, 4);

  ucg_SetColor(ucg, 0, 255, 168, 0);
  ucg_SetFont(ucg, ucg_font_5x8);
  //ucg_SetFont(ucg, ucg_font_courB08);
  ucg_DrawString(ucg, 2, 54, 0, "http://");
  ucg_DrawString(ucg, 1, 61, 0, "code.google.com/p/ucglib/");


}



void setup(void)
{
  delay(1000);
  ucg.begin();
  ucg.clearScreen();
}



void loop(void)
{
  ucg.setRotate90();
  draw_ucg_logo(ucg.getUcg());
  for(;;)
    ;
}

