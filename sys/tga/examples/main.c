

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>



ucg_t ucg;



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

ucg_int_t rule_offset = 4;


/*
  pos = 1 above
  pos = 0 
  pos = -1 below
*/
void hrule(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len, int pos)
{
  char s[10];
  ucg_int_t o = rule_offset*pos;
  ucg_int_t w;
  
  ucg_DrawHLine(ucg, x, y-o, len);
  ucg_DrawVLine(ucg, x, y-1-o, 3);
  ucg_DrawVLine(ucg, x+len-1, y-1-o, 3);
  sprintf(s, "%d", len);
  ucg_SetFont(ucg, ucg_font_6x12);
  if ( pos >= 0 )
  {
    ucg_SetFontPosBottom(ucg);
  }
  else
  {
    ucg_SetFontPosTop(ucg);
  }
  w = ucg_GetStrWidth(ucg, s);
  ucg_DrawString(ucg, x + len/2 - w/2, y-o+1, 0, s);
  
}

int main(void)
{
  ucg_int_t i;
  
  tga_init(128,64);
  ucg_Init(&ucg, &ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  ucg_DrawBox(&ucg, 0, 0, 128, 64);
  
  
  
  ucg_SetFont(&ucg, ucg_font_ncenB18);
  
  ucg_SetColor(&ucg, 0, 0, 0, 255);
  ucg_DrawPixel(&ucg, 70,20);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  //ucg_SetFontPosBottom(&ucg);
  
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');

  ucg_SetColor(&ucg, 0, 255, 255, 255);
  hrule(&ucg, 0, 20, 70, 1);
  hrule(&ucg, 0, 20, 70, -1);
  
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  tga_save("test.tga");
    
  
  return 0;
}

