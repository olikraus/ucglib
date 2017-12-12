/*

  ucg_dev_tft_240x400_hx8352c.c
  
  HX8352C with 4-Wire SPI (SCK, SDI, CS, D/C and optional reset)

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

static const ucg_pgm_uint8_t ucg_tft_240x400_hx8352c_init_seq[] = {
    UCG_CFG_CD(0, 1), /* DC=0 for command mode, DC=1 for data and args */
    UCG_RST(1),
    UCG_CS(1), /* disable chip */
    UCG_DLY_MS(1),
    UCG_RST(0),
    UCG_DLY_MS(50),
    UCG_RST(1),
    UCG_DLY_MS(100),
    UCG_CS(0), /* enable chip */

    // Power Voltage Setting
    UCG_C11(0x1A, 0x02), // BT
    UCG_C11(0x1B, 0x8B), // VRH
    // VCOM offset
    UCG_C11(0x23, 0x00), // SEL_VCM
    UCG_C11(0x24, 0x5D), // VCM
    UCG_C11(0x25, 0x15), // VDV
    UCG_C11(0x2D, 0x01), // NOW[2:0]=001

    // OPON
    UCG_C11(0xE8, 0x60),

    // Power on Setting
    UCG_C11(0x18, 0x04), // Frame rate 72Hz
    UCG_C11(0x19, 0x01), // OSC_EN='1', start Osc
    UCG_C11(0x01, 0x00), // DP_STB='0', out deep sleep
    UCG_C11(0x1F, 0x88), // STB=0
    UCG_DLY_MS(5),
    UCG_C11(0x1F, 0x80), // DK=0
    UCG_DLY_MS(5),
    UCG_C11(0x1F, 0x90), // PON=1
    UCG_DLY_MS(5),
    UCG_C11(0x1F, 0xD0), // VCOMG=1
    UCG_DLY_MS(5),

    // 262k/65k color selection
    UCG_C11(0x17, 0x06), // default 0x06 262k color // 0x05 65k color
    // SET PANEL
    // Horizontal(0x17) R36H:SM=0,GS=1,SS=1 (for details,See the datasheet of HX8352C-T)
    // Vertical(0x13)   R36H:SM=0,GS=0,SS=1 (for details,See the datasheet of HX8352C-T)
    UCG_C11(0x036, 0x013),
    UCG_C11(0x29, 0x31), // 400 lines
    UCG_C11(0x71, 0x1A), // RTN

    // Gamma 2.2 Setting
    UCG_C11(0x40, 0x00),
    UCG_C11(0x41, 0x77),
    UCG_C11(0x42, 0x77),
    UCG_C11(0x43, 0x00),
    UCG_C11(0x44, 0x04),
    UCG_C11(0x45, 0x00),
    UCG_C11(0x46, 0x00),
    UCG_C11(0x47, 0x00),
    UCG_C11(0x48, 0x77),
    UCG_C11(0x49, 0x00),
    UCG_C11(0x4A, 0x00),
    UCG_C11(0x4B, 0x08),
    UCG_C11(0x4C, 0x00),
    UCG_C11(0x4D, 0x00),
    UCG_C11(0x4E, 0x00),

    // Set DGC
    UCG_C11(0xFF, 0x01), // Page1
    UCG_C11(0x00, 0x01), // DGC_EN
    UCG_C11(0x01, 0x00),
    UCG_C11(0x02, 0x06),
    UCG_C11(0x03, 0x0C),
    UCG_C11(0x04, 0x12),
    UCG_C11(0x05, 0x16),
    UCG_C11(0x06, 0x1C),
    UCG_C11(0x07, 0x23),
    UCG_C11(0x08, 0x2E),
    UCG_C11(0x09, 0x36),
    UCG_C11(0x0A, 0x3F),
    UCG_C11(0x0B, 0x47),
    UCG_C11(0x0C, 0x50),
    UCG_C11(0x0D, 0x57),
    UCG_C11(0x0E, 0x5F),
    UCG_C11(0x0F, 0x67),
    UCG_C11(0x10, 0x6F),
    UCG_C11(0x11, 0x76),
    UCG_C11(0x12, 0x7F),
    UCG_C11(0x13, 0x87),
    UCG_C11(0x14, 0x90),
    UCG_C11(0x15, 0x99),
    UCG_C11(0x16, 0xA3),
    UCG_C11(0x17, 0xAD),
    UCG_C11(0x18, 0xB4),
    UCG_C11(0x19, 0xBB),
    UCG_C11(0x1A, 0xC4),
    UCG_C11(0x1B, 0xCE),
    UCG_C11(0x1C, 0xD9),
    UCG_C11(0x1D, 0xE3),
    UCG_C11(0x1E, 0xEC),
    UCG_C11(0x1F, 0xF3),
    UCG_C11(0x20, 0xF7),
    UCG_C11(0x21, 0xFC),
    UCG_C11(0x22, 0x00),
    UCG_C11(0x23, 0x06),
    UCG_C11(0x24, 0x0C),
    UCG_C11(0x25, 0x12),
    UCG_C11(0x26, 0x16),
    UCG_C11(0x27, 0x1C),
    UCG_C11(0x28, 0x23),
    UCG_C11(0x29, 0x2E),
    UCG_C11(0x2A, 0x36),
    UCG_C11(0x2B, 0x3F),
    UCG_C11(0x2C, 0x47),
    UCG_C11(0x2D, 0x50),
    UCG_C11(0x2E, 0x57),
    UCG_C11(0x2F, 0x5F),
    UCG_C11(0x30, 0x67),
    UCG_C11(0x31, 0x6F),
    UCG_C11(0x32, 0x76),
    UCG_C11(0x33, 0x7F),
    UCG_C11(0x34, 0x87),
    UCG_C11(0x35, 0x90),
    UCG_C11(0x36, 0x99),
    UCG_C11(0x37, 0xA3),
    UCG_C11(0x38, 0xAD),
    UCG_C11(0x39, 0xB4),
    UCG_C11(0x3A, 0xBB),
    UCG_C11(0x3B, 0xC4),
    UCG_C11(0x3C, 0xCE),
    UCG_C11(0x3D, 0xD9),
    UCG_C11(0x3E, 0xE3),
    UCG_C11(0x3F, 0xEC),
    UCG_C11(0x40, 0xF3),
    UCG_C11(0x41, 0xF7),
    UCG_C11(0x42, 0xFC),
    UCG_C11(0x43, 0x00),
    UCG_C11(0x44, 0x06),
    UCG_C11(0x45, 0x0C),
    UCG_C11(0x46, 0x12),
    UCG_C11(0x47, 0x16),
    UCG_C11(0x48, 0x1C),
    UCG_C11(0x49, 0x23),
    UCG_C11(0x4A, 0x2E),
    UCG_C11(0x4B, 0x36),
    UCG_C11(0x4C, 0x3F),
    UCG_C11(0x4D, 0x47),
    UCG_C11(0x4E, 0x50),
    UCG_C11(0x4F, 0x57),
    UCG_C11(0x50, 0x5F),
    UCG_C11(0x51, 0x67),
    UCG_C11(0x52, 0x6F),
    UCG_C11(0x53, 0x76),
    UCG_C11(0x54, 0x7F),
    UCG_C11(0x55, 0x87),
    UCG_C11(0x56, 0x90),
    UCG_C11(0x57, 0x99),
    UCG_C11(0x58, 0xA3),
    UCG_C11(0x59, 0xAD),
    UCG_C11(0x5A, 0xB4),
    UCG_C11(0x5B, 0xBB),
    UCG_C11(0x5C, 0xC4),
    UCG_C11(0x5D, 0xCE),
    UCG_C11(0x5E, 0xD9),
    UCG_C11(0x5F, 0xE3),
    UCG_C11(0x60, 0xEC),
    UCG_C11(0x61, 0xF3),
    UCG_C11(0x62, 0xF7),
    UCG_C11(0x63, 0xFC),
    UCG_C11(0xFF, 0x00), // Page0

    // Set GRAM Area
    UCG_C11(0x02, 0x00),
    UCG_C11(0x03, 0x00), // Column Start
    UCG_C11(0x04, 0x00),
    UCG_C11(0x05, 0xEF), // Column End
    UCG_C11(0x06, 0x00),
    UCG_C11(0x07, 0x00), // Row Start
    UCG_C11(0x08, 0x01),
    UCG_C11(0x09, 0x8F), // Row End

    // Display ON Setting
    UCG_C11(0x28, 0x38), //GON=1, DTE=1, D=10
    UCG_DLY_MS(40),
    UCG_C11(0x28, 0x3C), //GON=1, DTE=1, D=11
    UCG_C10(0x22),       //Start GRAM write

    UCG_CS(1), /* disable chip */
    UCG_END(), /* end of sequence */
};

ucg_int_t ucg_dev_hx8352c_18x240x400(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch (msg)
  {
  case UCG_MSG_DEV_POWER_UP:
    /* 1. Call to the controller procedures to setup the com interface */
    if (ucg_dev_ic_hx8352c_18(ucg, msg, data) == 0)
      return 0;

    /* 2. Send specific init sequence for this display module */
    ucg_com_SendCmdSeq(ucg, ucg_tft_240x400_hx8352c_init_seq);

    return 1;

  case UCG_MSG_DEV_POWER_DOWN:
    /* let do power down by the conroller procedures */
    return ucg_dev_ic_hx8352c_18(ucg, msg, data);

  case UCG_MSG_GET_DIMENSION:
    ((ucg_wh_t *)data)->w = 240;
    ((ucg_wh_t *)data)->h = 400;
    return 1;
  }

  /* all other messages are handled by the controller procedures */
  return ucg_dev_ic_hx8352c_18(ucg, msg, data);
}
