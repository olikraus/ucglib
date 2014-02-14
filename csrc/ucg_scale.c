/*

  ucg_scale.c
  
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

void ucg_UndoScale(ucg_t *ucg)
{
  if ( ucg->scale_chain_device_cb != NULL )
  {
    ucg->device_cb = ucg->scale_chain_device_cb;
    ucg->scale_chain_device_cb = NULL;
  }
  ucg_GetDimension(ucg);
  ucg_SetMaxClipRange(ucg);
}

const ucg_fntpgm_uint8_t ucg_scale_2x2[16] UCG_FONT_SECTION("ucg_scale_2x2") =  
{ 0x00, 0x03, 0x0c, 0x0f, 0x30, 0x33, 0x3c, 0x3f, 0xc0, 0xc3, 0xcc, 0xcf, 0xf0, 0xf3, 0xfc, 0xff };

ucg_int_t ucg_dev_scale2x2(ucg_t *ucg, ucg_int_t msg, void *data)
{
  ucg_xy_t xy;
  ucg_int_t len;
  ucg_int_t dir;
  switch(msg)
  {
    case UCG_MSG_GET_DIMENSION:
      ucg->scale_chain_device_cb(ucg, msg, data); 
      ((ucg_wh_t *)data)->h /= 2;
      ((ucg_wh_t *)data)->w /= 2;
    
      //printf("rw=%d rh=%d\n", ucg->rotate_dimension.w, ucg->rotate_dimension.h);
      //printf("aw=%d ah=%d\n",  ((ucg_wh_t volatile * volatile )data)->w, ((ucg_wh_t volatile * volatile )data)->h);
      //printf("dw=%d dh=%d\n", ucg->dimension.w, ucg->dimension.h);
      return 1;
      
    case UCG_MSG_SET_CLIP_BOX:
      ((ucg_box_t * )data)->ul.y *= 2; 
      ((ucg_box_t * )data)->ul.x *= 2; 
      ((ucg_box_t * )data)->size.h *= 2;
      ((ucg_box_t * )data)->size.w *= 2;
      
      //printf("post clipbox x=%d y=%d\n", ((ucg_box_t * )data)->ul.x, ((ucg_box_t * )data)->ul.y);
      break;
    case UCG_MSG_DRAW_PIXEL:
      xy = ucg->arg.pixel.pos;
      ucg->arg.pixel.pos.x *= 2;
      ucg->arg.pixel.pos.y *= 2;
      ucg->scale_chain_device_cb(ucg, msg, data); 
      ucg->arg.pixel.pos.x++;
      ucg->scale_chain_device_cb(ucg, msg, data); 
      ucg->arg.pixel.pos.y++;
      ucg->scale_chain_device_cb(ucg, msg, data); 
      ucg->arg.pixel.pos.x--;
      ucg->scale_chain_device_cb(ucg, msg, data); 
      ucg->arg.pixel.pos = xy;
      return 1;
    case UCG_MSG_DRAW_L90SE:
    case UCG_MSG_DRAW_L90FX:
      xy = ucg->arg.pixel.pos;
      len = ucg->arg.len;
      dir = ucg->arg.dir;
      ucg->arg.pixel.pos.x *= 2;
      ucg->arg.pixel.pos.y *= 2;
      ucg->arg.len *= 2;
      ucg->scale_chain_device_cb(ucg, msg, data);  
      ucg->arg.pixel.pos = xy;
      ucg->arg.pixel.pos.x *= 2;
      ucg->arg.pixel.pos.y *= 2;
      ucg->arg.len = len*2;
      switch(ucg->arg.dir)
      {
	case 0: ucg->arg.pixel.pos.y++; break;
	case 1: ucg->arg.pixel.pos.x++; break;
	case 2: ucg->arg.pixel.pos.y++; break;
	default: case 3: ucg->arg.pixel.pos.x++; break;
      }
      ucg->scale_chain_device_cb(ucg, msg, data);
      ucg->arg.pixel.pos = xy;
      ucg->arg.len = len;
      ucg->arg.dir = dir;
      return 1;
    case UCG_MSG_DRAW_L90TC:
      xy = ucg->arg.pixel.pos;
      len = ucg->arg.len;
      dir = ucg->arg.dir;
      {
	const uint8_t *b = ucg->arg.bitmap;
	uint8_t buf[2];
	ucg_int_t i;
	//ucg->arg.bitmap = buf;
	for( i = 0; i < len; i+=8 )
	{
	  ucg->arg.bitmap = buf;
	  buf[0] = 0;
	  buf[1] = 0;
	  if ( b[i/8] & 16 ) buf[0] |= 3<<0;
	  if ( b[i/8] & 32 ) buf[0] |= 3<<2;
	  if ( b[i/8] & 64 ) buf[0] |= 3<<4;
	  if ( b[i/8] & 128 ) buf[0] |= 3<<6;
	  if ( b[i/8] & 1 ) buf[1] |= 3<<0;
	  if ( b[i/8] & 2 ) buf[1] |= 3<<2;
	  if ( b[i/8] & 4 ) buf[1] |= 3<<4;
	  if ( b[i/8] & 8 ) buf[1] |= 3<<6;

	  switch(ucg->arg.dir)
	  {
	    case 0: 
	      ucg->arg.pixel.pos.x = (xy.x+i)*2;
	      ucg->arg.pixel.pos.y = (xy.y)*2;
	      break;
	    case 1:
	      ucg->arg.pixel.pos.x = (xy.x)*2;
	      ucg->arg.pixel.pos.y = (xy.y+i)*2;
	      break;
	    case 2: 
	      ucg->arg.pixel.pos.x = (xy.x-i)*2;
	      ucg->arg.pixel.pos.y = (xy.y)*2;
	      break;
	    default: case 3: 
	      ucg->arg.pixel.pos.x = (xy.x)*2;
	      ucg->arg.pixel.pos.y = (xy.y-i)*2;
	      break;
	  }
	  if ( len - i >= 8 )
	    ucg->arg.len = 16;
	  else
	    ucg->arg.len = (len-i)*2;
	  ucg->scale_chain_device_cb(ucg, msg, data);  
	  ucg->arg.bitmap = buf;
	  switch(ucg->arg.dir)
	  {
	    case 0: 
	      ucg->arg.pixel.pos.x = (xy.x+i)*2;
	      ucg->arg.pixel.pos.y = (xy.y)*2+1;
	      break;
	    case 1:
	      ucg->arg.pixel.pos.x = (xy.x)*2+1;
	      ucg->arg.pixel.pos.y = (xy.y+i)*2;
	      break;
	    case 2: 
	      ucg->arg.pixel.pos.x = (xy.x-i)*2;
	      ucg->arg.pixel.pos.y = (xy.y)*2+1;
	      break;
	    default: case 3: 
	      ucg->arg.pixel.pos.x = (xy.x)*2+1;
	      ucg->arg.pixel.pos.y = (xy.y-i)*2;
	      break;
	  }
	  if ( len - i >= 8 )
	    ucg->arg.len = 16;
	  else
	    ucg->arg.len = (len-i)*2;
	  ucg->scale_chain_device_cb(ucg, msg, data);  
	  
	}	
      }
      ucg->arg.pixel.pos = xy;
      ucg->arg.len = len;
      ucg->arg.dir = dir;
      return 1;
    case UCG_MSG_DRAW_L90RL:
      break;
  }
  return ucg->scale_chain_device_cb(ucg, msg, data);  
}

/* Side-Effects: Update dimension and reset clip range to max */
void ucg_SetScale2x2(ucg_t *ucg)
{
  ucg_UndoScale(ucg);
  ucg->scale_chain_device_cb = ucg->device_cb;
  ucg->device_cb = ucg_dev_scale2x2;
  ucg_GetDimension(ucg);
  ucg_SetMaxClipRange(ucg);
}
