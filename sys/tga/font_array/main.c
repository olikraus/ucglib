

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


extern const ucg_fntpgm_uint8_t *ucg_font_array[];
extern char *ucg_font_name[];



void pic_gen_short_desc(const ucg_pgm_uint8_t *font, const char *fname)
{
  char s[256];
  ucg_t ucg;
  ucg_int_t dx;

  tga_init(1024,500);
  ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);

  ucg_SetFont(&ucg, font);
  ucg_SetFontPosTop(&ucg);
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  
  if ( ucg_IsGlyph(&ucg, 'a') != 0 )
    sprintf(s, "123 ABC abcdefg");
  else
    sprintf(s, "0123456789");

  dx = ucg_DrawString(&ucg, 0, 2, 0, s);

  ucg_SetFont(&ucg, ucg_font_7x13);    
  ucg_DrawString(&ucg, dx+7, 2, 0, fname);
  
  
   tga_save("ucg_font.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_font.tga -trim %s_short.png", fname);
    system(cmd);
  }
}

void pic_gen_font(const ucg_pgm_uint8_t *font, const char *name, const char *fname )
{
  //ucg_int_t width;
  char s[256];
  const ucg_pgm_uint8_t *disp_font;
  uint16_t i;
  ucg_int_t x,y,w,h, hcnt, disp_line_height, disp_line_indent;
  uint8_t start, end;
  //ucg_int_t indent;
  ucg_t ucg;
  
  pic_gen_short_desc(font, fname);
  
  
  tga_init(1200,1200);
  ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  
  disp_font = ucg_font_7x13;
  
  disp_line_height = 14;
  disp_line_indent = 75;
  
  start = ucg_font_GetFontStartEncoding(font);
  end = ucg_font_GetFontEndEncoding(font);
  
  ucg_SetFont(&ucg, font);
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  /*
  hcnt = ucg_GetWidth(&ucg);
  hcnt /= ucg_GetFontBBXWidth(&ucg);
  hcnt -= 4;
  */
  
  //w = ucg_GetFontBBXWidth(&ucg)+2;
  w = ucg_GetGlyphWidth(&ucg, 'W') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, '0') + 3 )
    w = ucg_GetGlyphWidth(&ucg, '0') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, ' ') + 3 )
    w = ucg_GetGlyphWidth(&ucg, ' ') + 3;
  
  printf("%s w=%d\n", fname, w);
 
  //w = width;
  h = ucg_GetFontBBXHeight(&ucg);
  if ( h < disp_line_height )
    h = disp_line_height ;

  sprintf(s, "%s", name);
  
  ucg_SetFont(&ucg, disp_font);
  ucg_DrawString(&ucg, 0, disp_line_height, 0, s);
  
  ucg_SetFont(&ucg, font);
  sprintf(s, "BBX Width %d, Height %d,  Capital A %d", 
      ucg_GetFontBBXWidth(&ucg), 
      ucg_GetFontBBXHeight(&ucg), 
      ucg_GetFontCapitalAHeight(&ucg));
  
  
  ucg_SetFont(&ucg, disp_font);    
  ucg_DrawString(&ucg, 0, disp_line_height*2, 0, s);

  
  sprintf(s, "Font data size: %d", ucg_font_GetSize(font));
  ucg_DrawString(&ucg, 0, disp_line_height*3, 0, s);

  hcnt = 16;
  i = start - start % hcnt;
  for( y = 0; y < 16; y++ )
  {
    ucg_SetFont(&ucg, disp_font);
    if ( i <= end )
    {
      sprintf(s, "%3d/0x%02x", i, i);
      ucg_DrawString(&ucg, 0, y*h+disp_line_height*3+h, 0, s);
    }
    
    for( x = 0; x < hcnt; x++ )
    {
      if ( i <= end )
      {
	ucg_SetFont(&ucg, font);
	ucg_DrawGlyph(&ucg, x*w+disp_line_indent, y*h+disp_line_height*3+h, 0, i);
	i++;
      }
    }
  }

  tga_save("ucg_font.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_font.tga -trim %s.png", fname);
    system(cmd);
  }
}



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(int argc, char **argv)
{
  int i, a;
  FILE *wiki;
  i = 0;
  for(;;)
  {
    if ( ucg_font_array[i] == NULL )
    {
      if ( ucg_font_name[i] != NULL )
      {
	fprintf(stderr, "font pointer do not match font name, do_combine wrong?\n");
  
      }
      break;
    }
    
    printf("Processing Font '%s'\n", ucg_font_name[i]);
    pic_gen_font(ucg_font_array[i], ucg_font_name[i], ucg_font_name[i]);
    
    i++;
  }
  
  wiki = fopen("font_array.wiki", "w");
  for( a = 4;  a < 65; a++ )
  {
    ucg_t ucg;
    int cnt;
    tga_init(100, 100);
    ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
    
    i = 0;
    cnt = 0;
    for(;;)
    {
      if ( ucg_font_array[i] == NULL )
      {
	break;
      }
      ucg_SetFont(&ucg, ucg_font_array[i]);
      if ( ucg_GetFontCapitalAHeight(&ucg) == a )
	cnt++;
      i++;
    }
    printf("a=%d cnt=%d\n", a, cnt);

    if ( cnt > 0 )
    {
      i = 0;
      fprintf(wiki, "== %d Pixel Height ==\n",a); 
      for(;;)
      {
	if ( ucg_font_array[i] == NULL )
	{
	  break;
	}
	ucg_SetFont(&ucg, ucg_font_array[i]);
	if ( ucg_GetFontCapitalAHeight(&ucg) == a )
	{
	  fprintf(wiki, "[http://wiki.ucglib.googlecode.com/hg/font/%s_short.png]\n",ucg_font_name[i]); 
	}
	i++;
      }
    }
  }
  fclose(wiki);
  return 0;
}

