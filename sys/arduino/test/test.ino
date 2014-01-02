
#include <SPI.h>
#include "ucg.h"

ucg_t ucg;


int16_t ucg_com_Arduino_SPI_cb(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      break;
    case UCG_COM_MSG_POWER_DOWN:
      break;
    case UCG_COM_MSG_DELAY:
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      break;
    case UCG_COM_MSG_SEND_BYTE:
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      break;
    case UCG_COM_MSG_SEND_STR:
      break;
  }
  return 1;
}


void setup(void)
{
  ucg_Init(&ucg, ucg_dev_default_cb, ucg_com_Arduino_SPI_cb);
}

void loop(void)
{
}
