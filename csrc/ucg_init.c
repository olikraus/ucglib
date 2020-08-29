/*

  ucg_init.c
  
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
#include <string.h> 	/* memset */
#include <stdlib.h>

#ifdef __AVR__
uint8_t global_SREG_backup;		// used by the atomic macros
#endif

static void default_power_up(ucg_t *ucg, ucg_com_info_t *ucg_com_info) {
  ucg->com_cb(ucg, UCG_COM_MSG_POWER_UP, 0, (uint8_t *)ucg_com_info);
}

static void default_power_down(ucg_t *ucg) {
  ucg->com_cb(ucg, UCG_COM_MSG_POWER_DOWN, 0, NULL);
}

static void default_delay(ucg_t *ucg, uint16_t microseconds) {
  ucg->com_cb(ucg, UCG_COM_MSG_DELAY, microseconds, NULL);
}

static void default_change_reset_line(ucg_t *ucg, uint8_t state) {
  ucg->com_cb(ucg, UCG_COM_MSG_CHANGE_RESET_LINE, state, NULL);
}

static void default_change_cd_line(ucg_t *ucg, uint8_t state) {
  ucg->com_cb(ucg, UCG_COM_MSG_CHANGE_CD_LINE, state, NULL);
}

static void default_change_cs_line(ucg_t *ucg, uint8_t state) {
  ucg->com_cb(ucg, UCG_COM_MSG_CHANGE_CS_LINE, state, NULL);
}

static void default_send_byte(ucg_t *ucg, uint8_t byte) {
  ucg->com_cb(ucg, UCG_COM_MSG_SEND_BYTE, byte, NULL);
}

static void default_repeat_1_byte(ucg_t *ucg, uint16_t repeat, uint8_t byte) {
  ucg->com_cb(ucg, UCG_COM_MSG_REPEAT_1_BYTE, repeat, &byte);
}

static void default_repeat_2_bytes(ucg_t *ucg, uint16_t repeat, uint8_t bytes[2]) {
  ucg->com_cb(ucg, UCG_COM_MSG_REPEAT_2_BYTES, repeat, bytes);
}

static void default_repeat_3_bytes(ucg_t *ucg, uint16_t repeat, uint8_t bytes[3]) {
  ucg->com_cb(ucg, UCG_COM_MSG_REPEAT_3_BYTES, repeat, bytes);
}

static void default_send_str(ucg_t *ucg, uint16_t length, uint8_t bytes[]) {
  ucg->com_cb(ucg, UCG_COM_MSG_SEND_STR, length, bytes);
}

static void default_send_cd_data_sequence(ucg_t *ucg, uint16_t count, uint8_t bytes[]) {
  ucg->com_cb(ucg, UCG_COM_MSG_SEND_CD_DATA_SEQUENCE, count, bytes);
}

static void ucg_init_struct(ucg_t *ucg);

static void ucg_init_struct(ucg_t *ucg)
{
  //memset(ucg, 0, sizeof(ucg_t));
  ucg->is_power_up = 0;
  ucg->rotate_chain_device_cb = 0;
  ucg->arg.scale = 1;
  //ucg->display_offset.x = 0;
  //ucg->display_offset.y = 0;
  ucg->font = 0;
  ucg->frame_buffer = NULL;
  ucg->device_cb_real = NULL;
  //ucg->font_mode = UCG_FONT_MODE_NONE;   Old font procedures
  ucg->font_decode.is_transparent = 1;  // new font procedures
  
  ucg->com_initial_change_sent = 0;
  ucg->com_status = 0;
  ucg->com_cfg_cd = 0;

  ucg->com_cb_funcs.power_up = default_power_up;
  ucg->com_cb_funcs.power_down = default_power_down;
  ucg->com_cb_funcs.delay = default_delay;
  ucg->com_cb_funcs.change_reset_line = default_change_reset_line;
  ucg->com_cb_funcs.change_cd_line = default_change_cd_line;
  ucg->com_cb_funcs.change_cs_line = default_change_cs_line;
  ucg->com_cb_funcs.send_byte = default_send_byte;
  ucg->com_cb_funcs.repeat_1_byte = default_repeat_1_byte;
  ucg->com_cb_funcs.repeat_2_bytes = default_repeat_2_bytes;
  ucg->com_cb_funcs.repeat_3_bytes = default_repeat_3_bytes;
  ucg->com_cb_funcs.send_str = default_send_str;
  ucg->com_cb_funcs.send_cd_data_sequence = default_send_cd_data_sequence;
}


ucg_int_t ucg_Init(ucg_t *ucg, ucg_dev_fnptr device_cb, ucg_dev_fnptr ext_cb, ucg_com_fnptr com_cb)
{
  ucg_int_t r;
  ucg_init_struct(ucg);
  if ( ext_cb == (ucg_dev_fnptr)0 )
    ucg->ext_cb = ucg_ext_none;
 else 
    ucg->ext_cb = ext_cb;
  ucg->device_cb = device_cb;
  ucg->com_cb = com_cb;
  ucg_SetFontPosBaseline(ucg);
  r = ucg_PowerUp(ucg);
  ucg_GetDimension(ucg);
  return r;
}

ucg_int_t ucg_InitBuffer(ucg_t *ucg, ucg_dev_fnptr device_cb, ucg_dev_fnptr ext_cb, ucg_com_fnptr com_cb)
{
  ucg_int_t r;

  r = ucg_Init(ucg, device_cb, ext_cb, com_cb);

  ucg->frame_buffer = calloc(1, ucg_GetWidth(ucg) * ucg_GetHeight(ucg) * 3);

  ucg->device_cb_real = ucg->device_cb;
  ucg->device_cb = ucg_dev_buffer;

  return r;
}