/*

  ucg_dev_memory.c
  
  Memory buffer device.

  Universal uC Color Graphics Library
  
  Copyright (c) 2015, olikraus@gmail.com
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

ucg_int_t ucg_dev_buffer(ucg_t *ucg, ucg_int_t msg, void *data)
{
  ucg_wh_t dimension;
  
  switch(msg) {
    case UCG_MSG_DEV_POWER_UP:
      break;
    case UCG_MSG_DEV_POWER_DOWN:
      break;
    case UCG_MSG_GET_DIMENSION:
      break;
    case UCG_MSG_DRAW_PIXEL:
      if ( ucg_clip_is_pixel_visible(ucg) !=0 ) {
        unsigned char *pixel;
        ucg->device_cb_real(ucg, UCG_MSG_GET_DIMENSION, &dimension);

        pixel = &(ucg->frame_buffer)[
          (dimension.w * ucg->arg.pixel.pos.y * 3) + (ucg->arg.pixel.pos.x * 3)
        ];
        *pixel = ucg->arg.pixel.rgb.color[0];
        *(pixel + 1) = ucg->arg.pixel.rgb.color[1];
        *(pixel + 2) = ucg->arg.pixel.rgb.color[2];
      }
      return 1;
    case UCG_MSG_SEND_BUFFER:
      break;
    case UCG_MSG_DRAW_L90FX:
      ucg_handle_l90fx(ucg, ucg_dev_buffer);
      return 1;
    #ifdef UCG_MSG_DRAW_L90TC
    case UCG_MSG_DRAW_L90TC:
      ucg_handle_l90tc(ucg, ucg_dev_buffer);
      return 1;
    #endif
    case UCG_MSG_DRAW_L90SE:
      ucg_handle_l90se(ucg, ucg_dev_buffer);
      return 1;
    #ifdef UCG_MSG_DRAW_L90BF
      case UCG_MSG_DRAW_L90BF:
      ucg_handle_l90bf(ucg, ucg_dev_buffer);
      return 1;
    #endif
  }
  return ucg->device_cb_real(ucg, msg, data);
}