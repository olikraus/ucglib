/*

  ucg_dev_tft_320x480_ili9486.c
  
  ILI9486 with 4-Wire SPI (SCK, SDI, CS, D/C and optional reset)

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

#include "ucg.h"

static const ucg_pgm_uint8_t ucg_tft_320x480_ili9486_init_seq[] = {
    UCG_CFG_CD(0, 1), /* DC=0 for command mode, DC=1 for data and args */
    UCG_RST(1),
    UCG_CS(1), /* disable chip */
    UCG_DLY_MS(1),
    UCG_RST(0),
    UCG_DLY_MS(50),
    UCG_RST(1),
    UCG_DLY_MS(100),
    UCG_CS(0), /* enable chip */

    UCG_C19(0XF2, 0x18, 0xA3, 0x12, 0x02, 0XB2, 0x12, 0xFF, 0x10, 0x00),
    UCG_C12(0XF8, 0x21, 0x04),
    UCG_C10(0x13),             // Normal Display Mode ON
    UCG_C11(0x36, 0x08),       // Memory Access Control, BGR Order
    UCG_C11(0xB4, 0x02),       // Display Inversion Control, 2-dot inversion
    UCG_C12(0xB6, 0x02, 0x22), // Display Function Control, AGND, Normal scan
    UCG_C11(0xC1, 0x41),       // Power Control 2
    UCG_C12(0xC5, 0x00, 0x18), // VCOM Control 1
    UCG_C11(0x3a, 0x66),       // Interface Pixel Format, 18bit
    UCG_DLY_MS(50),

    // PGAMCTRL (Positive Gamma Control)
    UCG_C1F(0xE0, 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00),
    // NGAMCTRL (Negative Gamma Control)
    UCG_C1F(0xE1, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00),
    UCG_C10(0x11), // Sleep OUT
    UCG_DLY_MS(120),
    UCG_C10(0x29), // Display ON
    UCG_C10(0x2C), // Memory Write

    UCG_CS(1), /* disable chip */
    UCG_END(), /* end of sequence */
};

ucg_int_t ucg_dev_ili9486_18x320x480(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch (msg)
  {
  case UCG_MSG_DEV_POWER_UP:
    /* 1. Call to the controller procedures to setup the com interface */
    if (ucg_dev_ic_ili9486_18(ucg, msg, data) == 0)
      return 0;

    /* 2. Send specific init sequence for this display module */
    ucg_com_SendCmdSeq(ucg, ucg_tft_320x480_ili9486_init_seq);

    return 1;

  case UCG_MSG_DEV_POWER_DOWN:
    /* let do power down by the conroller procedures */
    return ucg_dev_ic_ili9486_18(ucg, msg, data);

  case UCG_MSG_GET_DIMENSION:
    ((ucg_wh_t *)data)->w = 320;
    ((ucg_wh_t *)data)->h = 480;
    return 1;
  }

  /* all other messages are handled by the controller procedures */
  return ucg_dev_ic_ili9486_18(ucg, msg, data);
}
