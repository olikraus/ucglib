/*

  ucg_com_msg_api.c
  
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


void ucg_com_PowerDown(ucg_t *ucg)
{
  if ( (ucg->com_status & UCG_COM_STATUS_MASK_POWER) != 0 )
    ucg->com_cb(ucg, UCG_COM_MSG_POWER_DOWN, 0, NULL);
  ucg->com_status &= ~UCG_COM_STATUS_MASK_POWER;
}

int16_t ucg_com_PowerUp(ucg_t *ucg)
{
  int16_t r;
  ucg_com_PowerDown(ucg);  
  ucg->com_initial_change_sent = 0;
  r = ucg->com_cb(ucg, UCG_COM_MSG_POWER_UP, 0, NULL);
  if ( r != 0 )
  {
    ucg->com_status |= UCG_COM_STATUS_MASK_POWER;
  }
  return r;
}

void ucg_com_SetLineStatus(ucg_t *ucg, uint8_t level, uint8_t mask, uint8_t msg)
{
  if ( level == 0 )
  {
    if ( (ucg->com_initial_change_sent & mask) == 0 || (ucg->com_status & mask) == mask )
    {
      ucg->com_cb(ucg, msg, level, NULL);
      ucg->status &= ~mask;
      ucg->com_initial_change_sent |= mask;
    }
  }
  else
  {
    if ( (ucg->com_initial_change_sent & mask) == 0 || (ucg->com_status & mask) == 0 )
    {
      ucg->com_cb(ucg, msg, level, NULL);
      ucg->status |= mask;
      ucg->com_initial_change_sent |= mask;
    }
  }
}

int16_t ucg_com_SendByte(ucg_t *ucg, )
{
}
