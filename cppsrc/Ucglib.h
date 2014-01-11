
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


class Ucglib : public Print
{
  private:
    ucg_t ucg;
    ucg_int_t tx, ty;          // current position for the Print base class procedures
    ucg_dev_fnptr dev_cb;
    ucg_dev_fnptr ext_cb;
    void init(void);
  public:
    Ucglib(void) { init(); }
    Ucglib(ucg_dev_fnptr dev, ucg_dev_fnptr ext = ucg_ext_none) { dev_cb = dev; ext_cb = ext; }
    ucg_t *getUcg(void) { return &ucg; }
    void beginSerial(uint8_t cd, uint8_t cs, uint8_t reset);
    void beginParallel(uint8_t wr, uint8_t cd, uint8_t cs, uint8_t reset);

    // Procedures, which are always available as part of the BASIC drawing procedure set
      
    void setClipRange(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_SetClipRange(&ucg, x,y,w,h); }
    void setMaxClipRange(void) { ucg_SetMaxClipRange(&ucg); }
      
    void drawHLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawHLine(&ucg, x, y, len); }
    void drawVLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawVLine(&ucg, x, y, len); }

    // Procedures, which are only available with the EXTENDED option
    
    void drawGradientLine(ucg_int_t x, ucg_int_t y, ucg_int_t len, ucg_int_t dir) {ucg_DrawGradientLine(&ucg, x, y, len, dir); }
      
};




#endif /* _UCGLIB_HH */
