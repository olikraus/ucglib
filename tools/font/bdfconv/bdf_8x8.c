/*

  bdf_8x8.c
  
  unencoded font format for 8x8 pixel font
  
  offset 	bytes	desc
  0		1		first char
  1		2		last char
  2		n		font data, n = (last char - first char + 1)*8
  
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bdf_font.h"


int bg_8x8_convert(bg_t *bg)
{
  int x;
  int y;
  int d;
  
  bg_ClearTargetData(bg);
  
  if ( bg->bitmap_width != 8 )
    return 0;
  if ( bg->bitmap_height != 8 )
    return 0;
  
  for( y = 0; y < 8; y++)
  {
    d = 0;
    for( x = 0; x < 8; x++)
    {
      /*
	Instead of bg_GetBBXPixel() we will call bg_GetBBXPixel for
	the unmodified bitmap data.
      */
      if ( bg_GetBitmapPixel(bg, x, y) != 0 )
      {
	d++;
      }
      d <<= 1;
    }
    if ( bg_AddTargetData(bg, d) < 0 )
      return 0;
 }
  return 1;
}


void bf_Generate8x8Font(bf_t *bf)
{
  int i, j, k;
  bg_t *bg;
  int first, last;

  /* Step 1: Generate 8x8 bitmap data */
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      if ( bg->bitmap_width != 8 )
      {
	bf_Log(bf, "Generate8x8Font: Error, glyph width is not 8, width=%d, encoding=%d", bg->bitmap_width, bg->encoding);
      }
      else
      {
	if ( bg->bitmap_height != 8 )
	{
	  bf_Log(bf, "Generate8x8Font: Error, glyph height is not 8, height=%d, encoding=%d", bg->bitmap_height, bg->encoding);
	}
	else
	{
	  if ( bg_8x8_convert(bg) == 0 )
	  {
	    bf_Log(bf, "Generate8x8Font: Error, 8x8 conversion, encoding=%d", bg->target_cnt, bg->encoding);
	  }
	}
      }
    }
  }

  /* Step 2: Calculate first and last char */
  
  first = -1;
  last = -1;
  
  for( j = 0; j < 256; j++ )
  {
    for( i = 0; i < bf->glyph_cnt; i++ )
    {
      bg = bf->glyph_list[i];
      if ( bg->map_to == j )
      {
	if ( bg->target_data != NULL )
	{
	  
	  if ( bg->target_cnt != 8)
	  {
	    bf_Log(bf, "Generate8x8Font: Error, glyph size is not 8, size=%d, encoding=%d", bg->target_cnt, bg->encoding);
	  }
	  else
	  {
	    if ( first < 0 )
	      first = j;
	    last = j;
	  }
	}
      }
    }
  }
  
  /* Step 3: Write font data */
  
  for( j = first; j <= last; j++ )
  {
    for( i = 0; i < bf->glyph_cnt; i++ )
    {
      bg = bf->glyph_list[i];
      if ( bg->map_to == j )
      {
	if ( bg->target_data != NULL )
	{
	  
	  if ( bg->target_cnt == 8)
	  {
	    for( k = 0; k < bg->target_cnt; k++ )
	    {
	      bf_AddTargetData(bf, bg->target_data[k]);
	    }
	  }
	}
      }
    }
  }

  bf_Log(bf, "Generate8x8Font: Font size %d", bf->target_cnt);
}