
#include "Ucglib.h"

int16_t ucg_com_arduino_portd(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  return 1;
}

int16_t ucg_com_arduino_SPI(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  return 1;
}

void Ucglib::init(void)
{
  // do a dummy init so that something usefull is part of the ucg structure
  ucg_Init(ucg, ucg_dev_default_cb, ucg_ext_none, (ucg_com_fnptr)0);

  // reset cursor position
  tx = 0;
  ty = 0;
}



Ucglib::beginSerial(uint8_t cd, uint8_t cs, uint8_t reset)
{
  ucg.pin_list[UCG_PIN_RST] = reset;
  ucg.pin_list[UCG_PIN_CD] = cd;
  ucg.pin_list[UCG_PIN_CS] = cs;
  //ucg.pin_list[UCG_PIN_SCL] = scl
  //ucg.pin_list[UCG_PIN_SDA] = sda;
  ucg_Init(ucg, dev_cb, ext_cb, ucg_com_arduino_SPI);
}

Ucglib::beginParallel(uint8_t wr, uint8_t cd, uint8_t cs, uint8_t reset)
{
  ucg.pin_list[UCG_PIN_RST] = reset;
  ucg.pin_list[UCG_PIN_CD] = cd;
  ucg.pin_list[UCG_PIN_CS] = cs;
  ucg.pin_list[UCG_PIN_WR] = wr
  ucg_Init(ucg, dev_cb, ext_cb, ucg_com_arduino_portd);
}
