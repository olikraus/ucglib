/*

  HelloWorld.ino
  
  A very simple example for Ucglib

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

  18 Feb 2014:
    ROM Size	Font Mode
    9928		NONE
    10942		TRANSPARENT	(1014 Bytes)
    11650		SOLID  (1712 Bytes)
    12214		TRANSPARENT+SOLID
  
  
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
    ucg_dev_st7735_18x128x160		[ucg_ext_none, ucg_ext_st7735_18]
    
  Hardware SPI Pins:
    Arduino Uno		scl=13, sda=11
    Arduino Due		scl=76, sda=75
    Arduino Mega	scl=52, sda=51
    
  >>> Please uncomment (and update) one of the following constructors. <<<
  
*/
/* full interface */
//Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib4WireHWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);			/* Display connected to HW SPI, use SPI Library */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Uno, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 76, /*sda=*/ 75, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Due, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ 52, /*sda=*/ 51, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Mega, SW SPI via HW SPI Pins */
//Ucglib4WireSWSPI ucg(ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, /*scl=*/ 7, /*sda=*/ 6, /*cd=*/ 5, /*cs=*/ 3, /*reset=*/ 4);	/* currently only works with DUE, but why??? */
//Ucglib4WireSWSPI ucg(ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, /*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Uno, SW SPI via HW SPI Pins */
//Ucglib4WireHWSPI ucg(ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* Arduino Uno, HW SPI Pins */

/* simplified interface */
//Ucglib_ST7735_18x128x160_SWSPI ucg(/*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*scl=*/ 7, /*sda=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_SSD1351_18x128x128_SWSPI ucg(/*scl=*/ 13, /*sda=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

Ucglib_PCF8833_16x132x132_SWSPI ucg(/*scl=*/ 13, /*sda=*/ 11, /*cs=*/ 9, /*reset=*/ 8);	/* linksprite board */

void setup(void)
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  //ucg.begin(UCG_FONT_MODE_SOLID);
  ucg.clearScreen();
}

void loop(void)
{
  //ucg.setRotate90();
  ucg.setFont(ucg_font_ncenR14r);
  ucg.setColor(255, 255, 255);
  ucg.setColor(255, 0, 0);
  //ucg.setColor(0, 255, 0);
  ucg.setColor(1, 255, 0,0);
  
  ucg.setPrintPos(0,25);
  ucg.print("Hello World!");

  ucg.setPrintPos(1,50);
  ucg.print("Hello World!");

  delay(500);  
}