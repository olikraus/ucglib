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

/*=========================================================================*/

#if  defined(__SAM3X8E__)
//#elif defined(__SAM3X8E__)

//#define setbit(pio, mask) PIO_Set( (pio), (mask) )
//#define clrbit(pio, mask) PIO_Clear( (pio), (mask) )

#define setbit(pio, mask) ((pio)->PIO_SODR = (mask))
#define clrbit(pio, mask) ((pio)->PIO_CODR = (mask))

/*
extern void PIO_Set( Pio* pPio, const uint32_t dwMask )
{
    pPio->PIO_SODR = dwMask ;
}

extern void PIO_Clear( Pio* pPio, const uint32_t dwMask )
{
    pPio->PIO_CODR = dwMask ;
}
*/


static void ucg_com_arduino_send_generic_SW_SPI(ucg_t *ucg, uint8_t data)
{
  uint32_t sda_pin = ucg->pin_list[UCG_PIN_SDA];
  uint32_t scl_pin = ucg->pin_list[UCG_PIN_SCL];
  Pio *sda_port = g_APinDescription[sda_pin].pPort;
  Pio *scl_port = g_APinDescription[scl_pin].pPort;
  uint8_t i = 8;
  sda_pin = g_APinDescription[sda_pin].ulPin;
  scl_pin = g_APinDescription[scl_pin].ulPin;

  do
  {
    if ( data & 128 )
    {
      setbit( sda_port, sda_pin) ;
    }
    else
    {
      clrbit( sda_port, sda_pin) ;
    }
    // no delay required, also Arduino Due is slow enough
    //delayMicroseconds(1);
    setbit( scl_port, scl_pin);
    //delayMicroseconds(1);
    i--;
    clrbit( scl_port, scl_pin) ;
    //delayMicroseconds(1);
    data <<= 1;
  } while( i > 0 );
  
}

#else

static void ucg_com_arduino_send_generic_SW_SPI(ucg_t *ucg, uint8_t data)
{
  uint8_t i = 8;
  
  do
  {
    if ( data & 128 )
    {
      digitalWrite(ucg->pin_list[UCG_PIN_SDA], 1 );
    }
    else
    {
      digitalWrite(ucg->pin_list[UCG_PIN_SDA], 0 );
    }
    // no delay required, also Arduino Due is slow enough
    //delayMicroseconds(1);
    digitalWrite(ucg->pin_list[UCG_PIN_SCL], 1 );
    //delayMicroseconds(1);
    i--;
    digitalWrite(ucg->pin_list[UCG_PIN_SCL], 0 );
    //delayMicroseconds(1);
    data <<= 1;
  } while( i > 0 );
  
}

#endif

static int16_t ucg_com_arduino_generic_SW_SPI(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      pinMode(ucg->pin_list[UCG_PIN_CD], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_SDA], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_SCL], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CS], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_RST], OUTPUT);

      digitalWrite(ucg->pin_list[UCG_PIN_CD], 1);
      digitalWrite(ucg->pin_list[UCG_PIN_SDA], 1);
      digitalWrite(ucg->pin_list[UCG_PIN_SCL], 0);
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
      digitalWrite(ucg->pin_list[UCG_PIN_CD], arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      ucg_com_arduino_send_generic_SW_SPI(ucg, arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[0]);
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[0]);
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[1]);
	ucg_com_arduino_send_generic_SW_SPI(ucg, data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_SW_SPI(ucg, *data++);
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
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 0);
	  }
	  else
	  {
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 1);
	  }
	}
	data++;
	ucg_com_arduino_send_generic_SW_SPI(ucg, *data);
	data++;
	arg--;
      }
      break;
  }
  return 1;
}

void Ucglib4WireSWSPI::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_generic_SW_SPI); 
}


/*=========================================================================*/

static void ucg_com_arduino_send_generic_8bit(ucg_t *ucg, uint8_t data)
{
    digitalWrite(ucg->pin_list[UCG_PIN_D0], (data & 1) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D1], (data & 2) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D2], (data & 4) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D3], (data & 8) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D4], (data & 16) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D5], (data & 32) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D6], (data & 64) == 0 ? 0 : 1 );
    digitalWrite(ucg->pin_list[UCG_PIN_D7], (data & 128) == 0 ? 0 : 1 );  
    delayMicroseconds(1);
    digitalWrite(ucg->pin_list[UCG_PIN_WR], 0);
    delayMicroseconds(1);
    digitalWrite(ucg->pin_list[UCG_PIN_WR], 1);
}

static int16_t ucg_com_arduino_generic_8bit(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
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

      pinMode(ucg->pin_list[UCG_PIN_D0], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D1], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D2], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D3], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D4], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D5], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D6], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_D7], OUTPUT);

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
      digitalWrite(ucg->pin_list[UCG_PIN_CD], arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      ucg_com_arduino_send_generic_8bit(ucg, arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_8bit(ucg, data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_8bit(ucg, data[0]);
	ucg_com_arduino_send_generic_8bit(ucg, data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_8bit(ucg, data[0]);
	ucg_com_arduino_send_generic_8bit(ucg, data[1]);
	ucg_com_arduino_send_generic_8bit(ucg, data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	ucg_com_arduino_send_generic_8bit(ucg, *data++);
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
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 0);
	  }
	  else
	  {
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 1);
	  }
	}
	data++;
	ucg_com_arduino_send_generic_8bit(ucg, *data);
	data++;
	arg--;
      }
      break;
  }
  return 1;
}

void Ucglib8Bit::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_generic_8bit); 
}


/*=========================================================================*/

#ifdef __AVR__

static void ucg_com_arduino_port_d_send(uint8_t data, volatile uint8_t *port, uint8_t and_mask, uint8_t or_mask)
{
    PORTD = data;
    *port &= and_mask;
    *port |= or_mask;
}

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
      ucg_com_arduino_port_d_send(arg, ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);

      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[1], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[1], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	ucg_com_arduino_port_d_send(data[2], ucg->data_port[UCG_PIN_WR], ~ucg->data_mask[UCG_PIN_WR], ucg->data_mask[UCG_PIN_WR]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
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

void Ucglib8BitPortD::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_port_d); 
}

#endif /* __AVR__ */

/*=========================================================================*/

static int16_t ucg_com_arduino_4wire_HW_SPI(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
    
      pinMode(ucg->pin_list[UCG_PIN_RST], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CD], OUTPUT);
      pinMode(ucg->pin_list[UCG_PIN_CS], OUTPUT);
      
      /* setup Arduino SPI */
      SPI.begin();
#if defined(__AVR__)
      SPI.setClockDivider( SPI_CLOCK_DIV2 );
#endif
#if defined(__SAM3X8E__)
      SPI.setClockDivider( (((ucg_com_info_t *)data)->serial_clk_speed * 84L + 999)/1000L );
#endif
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
    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
      while(arg > 0)
      {
	if ( *data != 0 )
	{
	  if ( *data == 1 )
	  {
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 0);
	  }
	  else
	  {
	    digitalWrite(ucg->pin_list[UCG_PIN_CD], 1);
	  }
	}
	data++;
	SPI.transfer(*data);
	data++;
	arg--;
      }
      break;
  }
  return 1;
}

void Ucglib4WireHWSPI::begin(void)
{ 
  ucg_Init(&ucg, dev_cb, ext_cb, ucg_com_arduino_4wire_HW_SPI); 
}


/*=========================================================================*/

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

