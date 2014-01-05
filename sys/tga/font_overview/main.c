

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


extern const ucg_fntpgm_uint8_t u8g_font_7x13[2157] UCG_FONT_SECTION("ucg_font_7x13") ;

ucg_t ucg;

/*
void pic_gen_short_desc(const u8g_pgm_uint8_t *font, const char *name, u8g_uint_t width, const char *real_name)
{
  char s[256];
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_pbm);
    u8g_SetFont(&u8g, font);
  
  if ( u8g_IsGlyph(&u8g, 'a') != 0 )
    sprintf(s, "%s: 123 ABC abcdefg", name);
  else
    sprintf(s, "0123456789");
    
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, font);
    u8g_DrawStr(&u8g, 0, 100, s);    
  }while( u8g_NextPage(&u8g) );
  
  {
    char cmd[256];
    u8g_SetFont(&u8g, font);
    sprintf(cmd, "convert u8g.pbm -trim %s_short.png", name );
    system(cmd);
  }
}
*/

void pic_gen_font(const u8g_pgm_uint8_t *font, const char *name, u8g_uint_t width, const char *real_name)
{
  char s[256];
  const u8g_pgm_uint8_t *disp_font;
  uint16_t i;
  u8g_uint_t x,y,w,h, hcnt, disp_line_height, disp_line_indent;
  uint8_t start, end;
  //u8g_uint_t indent;
  u8g_t u8g;
  
  //pic_gen_short_desc(font, name, width, real_name);
  
  
  tga_init(128,64);
  ucg_Init(&ucg, &ucg_dev_tga, (ucg_com_fnptr)0);
  
  disp_font = u8g_font_7x13;
  
  disp_line_height = 14;
  disp_line_indent = 75;
  
  start = ucg_font_GetFontStartEncoding(font);
  end = ucg_font_GetFontEndEncoding(font);
  
  ucg_SetFont(&ucg, font);
  hcnt = ucg_GetWidth(&ucg);
  hcnt /= ucg_GetFontBBXWidth(&ucg);
  hcnt -= 4;
  
  w = ucg_GetFontBBXWidth(&ucg);
  w = width;
  h = ucg_GetFontBBXHeight(&ucg);
  if ( h < disp_line_height )
    h = disp_line_height ;

  sprintf(s, "%s, %s", name,
      real_name);
  
  ucg_SetFont(&ucg, disp_font);
  ucg_DrawStrFontBBX(&ucg, 0, disp_line_height, 0, s);
  
  ucg_SetFont(&ucg, font);
  sprintf(s, "BBX Width %d, Height %d,  Capital A %d", 
      ucg_GetFontBBXWidth(&ucg), 
      ucg_GetFontBBXHeight(&ucg), 
      ucg_GetFontCapitalAHeight(&ucg));
  
  ucg_SetFont(&ucg, disp_font);    
  ucg_DrawStrFontBBX(&ucg, 0, disp_line_height*2, 0, s);

  
  sprintf(s, "Font data size: %d", ucg_font_GetSize(font));
  ucg_DrawStrFontBBX(&ucg, 0, disp_line_height*3, 0, s);

  hcnt = 16;
  i = start - start % hcnt;
  for( y = 0; y < 16; y++ )
  {
    ucg_SetFont(&ucg, disp_font);
    if ( i <= end )
    {
      sprintf(s, "%3d/0x%02x", i, i);
      //ucg_DrawStrFontBBX(&ucg, 0, y*h+disp_line_height*3+h, 0, s);
    }
    
    for( x = 0; x < hcnt; x++ )
    {
      if ( i <= end )
      {
	ucg_SetFont(&ucg, font);
	// ucg_DrawGlyphFontBBX(&ucg, x*w+disp_line_indent, y*h+disp_line_height*3+h, 0, i);
	i++;
      }
    }
  }

/*  
  {
    char cmd[256];
    u8g_SetFont(&u8g, font);
    sprintf(cmd, "convert u8g.pbm -trim %s.png", name );
    system(cmd);
  }
  */
}



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(void)
{
  ucg_int_t i;
  
  tga_init(128,64);
  ucg_Init(&ucg, &ucg_dev_tga, (ucg_com_fnptr)0);
  ucg_SetFont(&ucg, u8g_font_7x13);
  
  ucg_SetColor(&ucg, 0, 0, 0, 0255);
  ucg_DrawPixel(&ucg, 70,20);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  //ucg_SetFontPosBottom(&ucg);
  
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');

  
  ucg_DrawBitmapLine(&ucg, 9,0, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,1, 0,16, bitmap);
  
  ucg_DrawBitmapLine(&ucg, 0,9, 1,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 1,10, 1,16, bitmap);
  
  for( i = 0; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 0; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);
 
  ucg_SetClipRange(&ucg, 10, 10, 25, 25);

  ucg_SetColor(&ucg, 0, 0, 255, 0);
  for( i = 1; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 1; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);

  ucg_SetColor(&ucg, 0, 80, 80, 255);

  
  ucg_DrawHLine(&ucg, 8, 9, 5);
  ucg_DrawHLine(&ucg, 8, 10, 5);
  ucg_DrawHLine(&ucg, 8, 11, 5);
  ucg_DrawHLine(&ucg, 8, 12, 100);

  ucg_DrawHLine(&ucg, 12, 13, 5);
  ucg_DrawHLine(&ucg, 12, 14, 100);

  ucg_DrawHLine(&ucg, 2, 15, 5);
  ucg_DrawHLine(&ucg, 40, 16, 5);

  ucg_DrawHRLine(&ucg, 12, 17, 1);
  ucg_DrawHRLine(&ucg, 12, 18, 2);
  ucg_DrawHRLine(&ucg, 12, 19, 3);
  ucg_DrawHRLine(&ucg, 12, 20, 4);

  ucg_DrawHRLine(&ucg, 36, 17, 1);
  ucg_DrawHRLine(&ucg, 36, 18, 2);
  ucg_DrawHRLine(&ucg, 36, 19, 3);
  ucg_DrawHRLine(&ucg, 36, 20, 4);

  ucg_DrawBitmapLine(&ucg, 9,22, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,23, 0,16, bitmap);

/*
  ucg_SetClipRange(&ucg, 70-9, 20-9, 20, 20);

  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');
*/

  ucg_SetMaxClipRange(&ucg);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  tga_save("test.tga");
    
  
  return 0;
}

