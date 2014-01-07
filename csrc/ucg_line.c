/*

  ucg_line.c
  
  Universal uC Color Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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

void ucg_DrawHLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len)
{
  ucg->arg.pixel.rgb.color[0] = ucg->arg.rgb[0].color[0];
  ucg->arg.pixel.rgb.color[1] = ucg->arg.rgb[0].color[1];
  ucg->arg.pixel.rgb.color[2] = ucg->arg.rgb[0].color[2];
  ucg->arg.pixel.pos.x = x;
  ucg->arg.pixel.pos.y = y;
  ucg->arg.len = len;
  ucg->arg.dir = 0;
  ucg_DrawL90FXWithArg(ucg);
}

void ucg_DrawVLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len)
{
  ucg->arg.pixel.rgb.color[0] = ucg->arg.rgb[0].color[0];
  ucg->arg.pixel.rgb.color[1] = ucg->arg.rgb[0].color[1];
  ucg->arg.pixel.rgb.color[2] = ucg->arg.rgb[0].color[2];
  ucg->arg.pixel.pos.x = x;
  ucg->arg.pixel.pos.y = y;
  ucg->arg.len = len;
  ucg->arg.dir = 1;
  ucg_DrawL90FXWithArg(ucg);
}

void ucg_DrawHRLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len)
{
  ucg->arg.pixel.rgb.color[0] = ucg->arg.rgb[0].color[0];
  ucg->arg.pixel.rgb.color[1] = ucg->arg.rgb[0].color[1];
  ucg->arg.pixel.rgb.color[2] = ucg->arg.rgb[0].color[2];
  ucg->arg.pixel.pos.x = x;
  ucg->arg.pixel.pos.y = y;
  ucg->arg.len = len;
  ucg->arg.dir = 2;
  ucg_DrawL90FXWithArg(ucg);
}

void ucg_DrawGradientLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len, ucg_int_t dir)
{
  ucg->arg.pixel.pos.x = x;
  ucg->arg.pixel.pos.y = y;
  ucg->arg.len = len;
  ucg->arg.dir = dir;
  ucg_DrawL90SEWithArg(ucg);
}
