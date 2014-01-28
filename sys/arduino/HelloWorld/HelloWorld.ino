
#include "Ucglib.h"

Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_dev_ic_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
Ucglib4WireSPI ucg(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*cd=*/ 9 , /*cs=*/ 10, /*cs=*/ 8);

void setup(void)
{
  delay(1000);
  ucg.begin();
}



void loop(void)
{
  ucg.setFont(ucg_font_helvR18r);
  ucg.setPrintPos(0,25);
  ucg.setColor(255, 255, 255);
  //ucg.setColor(255, 0, 0);
  ucg.print("Hello World!");
  delay(500);
  
}