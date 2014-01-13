/*

  Ucglib.cpp

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

#include <SPI.h>

#include "Ucglib.h"

static void ucg_com_arduino_port_d_send(uint8_t data, volatile uint8_t *port, uint8_t and_mask, uint8_t or_mask)
{
    PORTD = data;
    *port &= and_mask;
    *port |= or_mask;
}

#ifdef SLOW
static void ucg_com_arduino_port_d_send(ucg_t *ucg, uint8_t data)
{
    PORTD = data;
    *ucg->data_port[UCG_PIN_WR] &= ~ucg->data_mask[UCG_PIN_WR];
    *ucg->data_port[UCG_PIN_WR] |= ucg->data_mask[UCG_PIN_WR];

    /*
  digitalWrite(ucg->pin_list[UCG_PIN_WR], 0);
  digitalWrite(ucg->pin_list[UCG_PIN_WR], 1);
  */
}
#endif


static int16_t ucg_com_arduino_port_d(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      pinMode(ucg->pin_list[UCG_PIN_CD], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_WR], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CS], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_RST], OUTPUT);

      pinMode(0, OUTPUT);
      pinMode(1, OUTPUT);
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(7, OUTPUT);

      digitalWrite(ucg->pin_list[UCG_PIN_CD], 1);
      digitalWrite(ucg->pin_list[UCG_PIN_WR], 1);
      digitalWrite(ucg->pin_list[UCG_PIN_CS], 1);
      digitalWrite(ucg->pin_list[UCG_PIN_RST], 1);

      break;
    case UCG_COM_MSG_POWER_DOWN:
      break;
    case UCG_COM_MSG_DELAY:
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      if ( ucg->pin_list[UCG_PIN_RST] != UCG_PIN_VAL_NONE )
	digitalWrite(ucg->pin_list[UCG_PIN_RST], arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      if ( ucg->pin_list[UCG_PIN_CS] != UCG_PIN_VAL_NONE )
	digitalWrite(ucg->pin_list[UCG_PIN_CS], arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      if ( arg == 0 )
	*ucg->data_port[UCG_PIN_CD] &= ~ucg->data_mask[UCG_PIN_CD];
      else
	*ucg->data_port[UCG_PIN_CD] |= ucg->data_mask[UCG_PIN_CD];
      //digitalWrite(ucg->pin_list[UCG_PIN_CD], arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      //ucg_com_arduino_port_d_send(ucg, arg);
      ucg_com_arduino_port_d_send(arg, ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);

      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	//ucg_com_arduino_port_d_send(ucg, data[0]);
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	//ucg_com_arduino_port_d_send(ucg, data[0]);
	//ucg_com_arduino_port_d_send(ucg, data[1]);
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[1], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	//ucg_com_arduino_port_d_send(ucg, data[0]);
	//ucg_com_arduino_port_d_send(ucg, data[1]);
	//ucg_com_arduino_port_d_send(ucg, data[2]);
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[1], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[2], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	//ucg_com_arduino_port_d_send(ucg, *data++);
	ucg_com_arduino_port_d_send(*data++, ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
      while(arg > 0)
      {
	if ( *data != 0 )
	{
	  if ( *data == 1 )
	  {
	    *ucg->data_port[UCG_PIN_CD] &= ~ucg->data_mask[UCG_PIN_CD];
	  }
	  else
	  {
	    *ucg->data_port[UCG_PIN_CD] |= ucg->data_mask[UCG_PIN_CD];
	  }
	}
	data++;
	ucg_com_arduino_port_d_send(*data, ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);	
	data++;
	arg--;
      }
      break;
  }
  return 1;
}

static int16_t ucg_com_arduino_4wire_SPI(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      //pinMode(13, OUTPUT);
      //pinMode(11, OUTPUT);
    
      pinMode(ucg->pin_list[UCG_PIN_RST], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CD], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CS], OUTPUT);
      
      /* setup Arduino SPI */
      SPI.begin();
      //SPI.setClockDivider( SPI_CLOCK_DIV2 );
      SPI.setDataMode(SPI_MODE0);
      SPI.setBitOrder(MSBFIRST);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      SPI.end(); 
      break;
    case UCG_COM_MSG_DELAY:
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      if ( ucg->pin_list[UCG_PIN_RST] != UCG_PIN_VAL_NONE )
	digitalWrite(ucg->pin_list[UCG_PIN_RST], arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      if ( ucg->pin_list[UCG_PIN_CS] != UCG_PIN_VAL_NONE )
	digitalWrite(ucg->pin_list[UCG_PIN_CS], arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      digitalWrite(ucg->pin_list[UCG_PIN_CD], arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      SPI.transfer(arg); 
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	SPI.transfer(data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	SPI.transfer(data[1]);
	SPI.transfer(data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	SPI.transfer(*data++);
	arg--;
      }
      break;
  }
  return 1;
}

void Ucglib::init(void) {
  uint8_t i;
  
  // do a dummy init so that something usefull is part of the ucg structure
  ucg_Init(&ucg, ucg_dev_default_cb, ucg_ext_none, (ucg_com_fnptr)0);

  // reset cursor position
  tx = 0;
  ty = 0;
  tdir = 0;	// default direction for Arduino print() 
  
  for( i = 0; i < UCG_PIN_COUNT; i++ )
    ucg.pin_list[i] = UCG_PIN_VAL_NONE;
  
}

size_t Ucglib::write(uint8_t c) { 
  ucg_int_t delta;
  delta = ucg_DrawGlyph(&ucg, tx, ty, tdir, c); 
  switch(tdir) {
    case 0: tx += delta; break;
    case 1: ty += delta; break;
    case 2: tx -= delta; break;
    default: case 3: ty -= delta; break;
  }
  return 1;
}


void Ucglib4WireSPI::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_4wire_SPI); 
}

void Ucglib8Bit::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_port_d); 
}

