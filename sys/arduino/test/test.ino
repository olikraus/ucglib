
#include <SPI.h>
#include "ucg.h"

ucg_t ucg;

uint8_t ucg_cs_pin = 8;	/* more flexible: Ucglib uses independet chip select */
uint8_t ucg_cd_pin = 7;	/* command / data line */
uint8_t ucg_reset_pin = 6;

int16_t ucg_com_arduino_spi(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* 
      pinMode(ucg_reset_pin, OUTPUT);
      pinMode(ucg_dc_pin, OUTPUT);
      pinMode(ucg_cs_pin, OUTPUT);
      
      /* setup Arduino SPI */
      SPI.begin();
      break;
    case UCG_COM_MSG_POWER_DOWN:
      SPI.end(); 
      break;
    case UCG_COM_MSG_DELAY:
      
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      digitalWrite(ucg_reset_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      digitalWrite(ucg_cs_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      digitalWrite(ucg_cd_pin, arg);
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


void setup(void)
{
  ucg_Init(&ucg, u8g_dev_ssd1351_128x128_oled_ilsoft, ucg_com_arduino_spi);
}

void loop(void)
{
}
