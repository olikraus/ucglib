/*

  Ucglib.h

  ucglib = universal color graphics library
  ucglib = micro controller graphics library
  
  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of s_t ource code must retain the above copyright notice, this list 
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

#ifndef _UCGLIB_HH
#define _UCGLIB_HH

#include <Print.h>

#ifndef USE_PIN_LIST
#define USE_PIN_LIST
#endif

#include "ucg.h"

// Do not use Ucglib class directly, use Ucglib8Bit or Ucglib4WireSPI instead
class Ucglib : public Print
{
  protected:
    ucg_t ucg;
    ucg_dev_fnptr dev_cb;
    ucg_dev_fnptr ext_cb;
  private:
    ucg_int_t tx, ty;          // current position for the Print base class procedures
    uint8_t tdir;
  protected:
    void init(void);
  public:
    Ucglib(void) { init(); }
    Ucglib(ucg_dev_fnptr dev, ucg_dev_fnptr ext = ucg_ext_none) { init(); dev_cb = dev; ext_cb = ext; }

    void setPrintPos(ucg_int_t x, ucg_int_t y) { tx = x; ty = y; }
    void setPrintDir(uint8_t dir) { tdir = dir; }
    size_t write(uint8_t c);
    ucg_t *getUcg(void) { return &ucg; }
    
    void setFont(const ucg_fntpgm_uint8_t  *font)
      { ucg_SetFont(&ucg, font); }
    ucg_int_t getFontAscent(void)
      { ucg_GetFontAscent(&ucg); }
    ucg_int_t getFontDescent(void)
      { ucg_GetFontDescent(&ucg); }
    
    void setColor(uint8_t idx, uint8_t r, uint8_t g, uint8_t b)
      { ucg_SetColor(&ucg, idx, r, g, b); }
    void setColor(uint8_t r, uint8_t g, uint8_t b)
      { ucg_SetColor(&ucg, 0, r, g, b); }

    // Procedures, which are always available as part of the BASIC drawing procedure set
      
    void setClipRange(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_SetClipRange(&ucg, x,y,w,h); }
    void setMaxClipRange(void) { ucg_SetMaxClipRange(&ucg); }
    void undoClipRange(void) { ucg_SetMaxClipRange(&ucg); }

    void drawPixel(ucg_int_t x, ucg_int_t y) { ucg_DrawPixel(&ucg, x, y); }    
    void drawHLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawHLine(&ucg, x, y, len); }
    void drawVLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawVLine(&ucg, x, y, len); }

    void drawBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_DrawBox(&ucg, x, y, w, h); }
    void clearScreen(void) { ucg_ClearScreen(&ucg); }

    // Procedures, which are only available with the EXTENDED option
    
    void drawGradientLine(ucg_int_t x, ucg_int_t y, ucg_int_t len, ucg_int_t dir) {ucg_DrawGradientLine(&ucg, x, y, len, dir); }
    void drawGradientBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_DrawGradientBox(&ucg, x, y, w, h); }
      
};

class Ucglib4WireSPI : public Ucglib
{
  public:
    Ucglib4WireSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 
	
	  ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.pin_list[UCG_PIN_RST] = reset; 
	  ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.pin_list[UCG_PIN_CD] = cd;
	  ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
	  ucg.pin_list[UCG_PIN_CS] = cs; }
    void begin(void);
};

class Ucglib8Bit : public Ucglib
{
  public:
    Ucglib8Bit(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t wr, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 
	  ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.pin_list[UCG_PIN_RST] = reset;
	  ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.pin_list[UCG_PIN_CD] = cd;
	  ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
	  ucg.pin_list[UCG_PIN_CS] = cs;
	  ucg.data_port[UCG_PIN_WR] =  portOutputRegister(digitalPinToPort(wr));
	  ucg.data_mask[UCG_PIN_WR] =  digitalPinToBitMask(wr);
	  ucg.pin_list[UCG_PIN_WR] = wr; }
    void begin(void);
};

#endif /* _UCGLIB_HH */
