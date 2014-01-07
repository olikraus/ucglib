/*

  ucg_rotate.c
  
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

static void ucg_rotate_90_xy(ucg_xy_t *xy, ucg_int_t display_width)
{
    ucg_int_t x, y;
    y = xy->x;
    x = display_width;
    x -= xy->y; 
    x--;
    xy->x = x;
    xy->y = y;  
}

void ucg_UndoRotate(ucg_t *ucg)
{
  if ( ucg->rotate_chain_device_cb != NULL )
  {
    ucg->device_cb = ucg->rotate_chain_device_cb;
    ucg->rotate_chain_device_cb = NULL;
  }
}

ucg_int_t u8g_dev_rotate90(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch(msg)
  {
    case UCG_MSG_GET_DIMENSION:
      ucg->rotate_chain_device_cb(ucg, msg, data); 
      {
	ucg_int_t tmp;
	tmp = ((ucg_wh_t *)data)->w;
	((ucg_wh_t *)data)->h = ((ucg_wh_t *)data)->w;
	((ucg_wh_t *)data)->w = tmp;
      }
      return 1;
    case UCG_MSG_DRAW_PIXEL:
    case UCG_MSG_DRAW_L90FX:
    case UCG_MSG_DRAW_L90TC:
    case UCG_MSG_DRAW_L90SE:
    case UCG_MSG_DRAW_L90RL:
      ucg->arg.dir+=1;
      ucg->arg.dir&=3;
      ucg_rotate_90_xy(&(ucg->arg.pixel.pos), ucg->dimension.h); /* use h, because it has been swapped and contains w */
      break;
  }
  return ucg->rotate_chain_device_cb(ucg, msg, data);  
}

void ucg_SetRotate90(ucg_t *ucg)
{
  ucg_UndoRotate(ucg);
  ucg->rotate_chain_device_cb = ucg->device_cb;
  ucg->device_cb = u8g_dev_rotate90;
  ucg_GetDimension(ucg);
}

