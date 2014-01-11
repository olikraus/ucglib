
#include "Ucglib.h"

Ucglib ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_dev_ic_ili9325_18);

void setup(void)
{
  ucg.beginParallel(18 /* wr */, 19 /* cd */, 17 /* cs */, 16 /* reset */);
}

void loop(void)
{
  ucg.setFont(ucg_font_ncenB18r);
  ucg.setPrintPos(0,20);
  ucg.setColor(255, 255, 255);
  ucg.print("Hello World!");
  delay(500);
  
}