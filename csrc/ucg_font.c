/*

  ucg_font.c
  
  UCG Font High Level Interface; mostly taken over from U8glib

  Universal uC Color Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
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

#include "ucg.h"

/* font api */

/* pointer to the start adress of the glyph, points to progmem area on avr uC */
typedef void * ucg_glyph_t;

/*=================================================*/
/* OLD FONT FORMAT */

/* size of the font data structure, there is no struct or class... */
/* this is the size for the new font format */
#define UCG_FONT_DATA_STRUCT_SIZE 21

/*
  OLD Font Data Struct 
  ... instead the fields of the font data structure are accessed directly by offset 
  font information 
  offset
  0             font format
  1             FONTBOUNDINGBOX width           unsigned
  2             FONTBOUNDINGBOX height          unsigned
  3             FONTBOUNDINGBOX x-offset         signed
  4             FONTBOUNDINGBOX y-offset        signed
  5             capital A height                                unsigned
  6             start 'A'
  8             start 'a'
  10            encoding start
  11            encoding end
  12            descent 'g'                     negative: below baseline
  13            font max ascent
  14            font min decent             negative: below baseline 
  15            font xascent
  16            font xdecent             negative: below baseline 

  new font data:

  offset	bytes	description
  0		1		glyph_cnt		number of glyphs
  1		1		bbx_mode	0: proportional, 1: common height, 2: monospace, 3: multiple of 8
  2		1		bits_per_0	glyph rle parameter
  3		1		bits_per_1	glyph rle parameter

  4		1		bits_per_char_width		glyph rle parameter
  5		1		bits_per_char_height	glyph rle parameter
  6		1		bits_per_char_x		glyph rle parameter
  7		1		bits_per_char_y		glyph rle parameter
  8		1		bits_per_delta_x		glyph rle parameter

  9		1		max_char_width
  10		1		max_char_height
  11		1		x offset
  12		1		y offset (descent)
  
  13		1		ascent (capital A)
  14		1		descent (lower g)
  15		1		ascent '('
  16		1		descent ')'
  
  17		1		start pos 'A' high byte
  18		1		start pos 'A' low byte

  19		1		start pos 'a' high byte
  20		1		start pos 'a' low byte


*/

/* use case: What is the width and the height of the minimal box into which string s fints? */
void ucg_font_GetStrSize(const void *font, const char *s, ucg_int_t *width, ucg_int_t *height);
void ucg_font_GetStrSizeP(const void *font, const char *s, ucg_int_t *width, ucg_int_t *height);

/* use case: lower left edge of a minimal box is known, what is the correct x, y position for the string draw procedure */
void ucg_font_AdjustXYToDraw(const void *font, const char *s, ucg_int_t *x, ucg_int_t *y);
void ucg_font_AdjustXYToDrawP(const void *font, const char *s, ucg_int_t *x, ucg_int_t *y);

/* use case: Baseline origin known, return minimal box */
void ucg_font_GetStrMinBox(ucg_t *ucg, const void *font, const char *s, ucg_int_t *x, ucg_int_t *y, ucg_int_t *width, ucg_int_t *height);

/* procedures */

/*========================================================================*/
/* low level byte and word access */

/* removed NOINLINE, because it leads to smaller code, might also be faster */
//static uint8_t ucg_font_get_byte(const ucg_fntpgm_uint8_t *font, uint8_t offset) UCG_NOINLINE;
static uint8_t ucg_font_get_byte(const ucg_fntpgm_uint8_t *font, uint8_t offset)
{
  font += offset;
  return ucg_pgm_read( (ucg_pgm_uint8_t *)font );  
}

static uint16_t ucg_font_get_word(const ucg_fntpgm_uint8_t *font, uint8_t offset) UCG_NOINLINE; 
static uint16_t ucg_font_get_word(const ucg_fntpgm_uint8_t *font, uint8_t offset)
{
    uint16_t pos;
    font += offset;
    pos = ucg_pgm_read( (ucg_pgm_uint8_t *)font );
    font++;
    pos <<= 8;
    pos += ucg_pgm_read( (ucg_pgm_uint8_t *)font);
    return pos;
}

/*========================================================================*/
/* new font format */
void ucg_read_font_info(ucg_font_info_t *font_info, const ucg_fntpgm_uint8_t *font)
{
  /* offset 0 */
  font_info->glyph_cnt = ucg_font_get_byte(font, 0);
  font_info->bbx_mode = ucg_font_get_byte(font, 1);
  font_info->bits_per_0 = ucg_font_get_byte(font, 2);
  font_info->bits_per_1 = ucg_font_get_byte(font, 3);
  
  /* offset 4 */
  font_info->bits_per_char_width = ucg_font_get_byte(font, 4);
  font_info->bits_per_char_height = ucg_font_get_byte(font, 5);
  font_info->bits_per_char_x = ucg_font_get_byte(font, 6);
  font_info->bits_per_char_y = ucg_font_get_byte(font, 7);
  font_info->bits_per_delta_x = ucg_font_get_byte(font, 8);
  
  /* offset 9 */
  font_info->max_char_width = ucg_font_get_byte(font, 9);
  font_info->max_char_height = ucg_font_get_byte(font, 10);
  font_info->x_offset = ucg_font_get_byte(font, 11);
  font_info->y_offset = ucg_font_get_byte(font, 12);
  
  /* offset 13 */
  font_info->ascent_A = ucg_font_get_byte(font, 13);
  font_info->descent_g = ucg_font_get_byte(font, 14);
  font_info->ascent_para = ucg_font_get_byte(font, 15);
  font_info->descent_para = ucg_font_get_byte(font, 16);
  
  /* offset 17 */
  font_info->start_pos_upper_A = ucg_font_get_word(font, 17);
  font_info->start_pos_lower_a = ucg_font_get_word(font, 19);  
}

/*========================================================================*/
/* direct access on the font */

// OBSOLETE
// static uint8_t ucg_font_GetFormat(const ucg_fntpgm_uint8_t *font) UCG_NOINLINE;
// static uint8_t ucg_font_GetFormat(const ucg_fntpgm_uint8_t *font)
// {
//   return ucg_font_get_byte(font, 0);
// }

// OBSOLETE
// static uint8_t ucg_font_GetFontGlyphStructureSize(const ucg_fntpgm_uint8_t *font) UCG_NOINLINE;
// static uint8_t ucg_font_GetFontGlyphStructureSize(const ucg_fntpgm_uint8_t *font)
// {
//   switch(ucg_font_GetFormat(font))
//   {
//     case 0: return 6;
//     case 1: return 3;
//     case 2: return 6;
//   }
//   return 3;
// }

// static uint8_t ucg_font_GetBBXWidth(const void *font)
// {
//   return ucg_font_get_byte(font, 1);
// }

// static uint8_t ucg_font_GetBBXHeight(const void *font)
// {
//   return ucg_font_get_byte(font, 2);
// }

// static int8_t ucg_font_GetBBXOffX(const void *font)
// {
//   return ucg_font_get_byte(font, 3);
// }

// static int8_t ucg_font_GetBBXOffY(const void *font)
// {
//   return ucg_font_get_byte(font, 4);
// }

uint8_t ucg_font_GetCapitalAHeight(const void *font)
{
  return ucg_font_get_byte(font, 5);
}

uint16_t ucg_font_GetEncoding65Pos(const void *font) UCG_NOINLINE;
uint16_t ucg_font_GetEncoding65Pos(const void *font)
{
    return ucg_font_get_word(font, 6);
}

uint16_t ucg_font_GetEncoding97Pos(const void *font) UCG_NOINLINE;
uint16_t ucg_font_GetEncoding97Pos(const void *font)
{
    return ucg_font_get_word(font, 8);
}

uint8_t ucg_font_GetFontStartEncoding(const void *font)
{
  return ucg_font_get_byte(font, 10);
}

uint8_t ucg_font_GetFontEndEncoding(const void *font)
{
  return ucg_font_get_byte(font, 11);
}

int8_t ucg_font_GetLowerGDescent(const void *font)
{
  return ucg_font_get_byte(font, 12);
}

int8_t ucg_font_GetFontAscent(const void *font)
{
  return ucg_font_get_byte(font, 13);
}

int8_t ucg_font_GetFontDescent(const void *font)
{
  return ucg_font_get_byte(font, 14);
}

int8_t ucg_font_GetFontXAscent(const void *font)
{
  return ucg_font_get_byte(font, 15);
}

int8_t ucg_font_GetFontXDescent(const void *font)
{
  return ucg_font_get_byte(font, 16);
}


/* return the data start for a font and the glyph pointer */
// static uint8_t *ucg_font_GetGlyphDataStart(const void *font, ucg_glyph_t g)
// {
//   return ((ucg_fntpgm_uint8_t *)g) + ucg_font_GetFontGlyphStructureSize(font);
// }

/* calculate the overall length of the font, only used to create the picture for the google wiki */
size_t ucg_font_GetSize(const void *font_arg)
{
  const uint8_t *font = font_arg;
  font += UCG_FONT_DATA_STRUCT_SIZE;
  
  for(;;)
  {
    if ( ucg_pgm_read( ((ucg_pgm_uint8_t *)font) + 1 ) == 0 )
      break;
    font += ucg_pgm_read( ((ucg_pgm_uint8_t *)font) + 1 );
  }
  
  return font - (const uint8_t *)font_arg;
  
#ifdef OLD_CODE
  
  uint8_t *p = (uint8_t *)(font);
  uint8_t font_format = ucg_font_GetFormat(font);
  uint8_t data_structure_size = ucg_font_GetFontGlyphStructureSize(font);
  uint8_t start, end;
  uint8_t i;
  uint8_t mask = 255;
  
  start = ucg_font_GetFontStartEncoding(font);
  end = ucg_font_GetFontEndEncoding(font);

  if ( font_format == 1 )
    mask = 15;

  p += UCG_FONT_DATA_STRUCT_SIZE;       /* skip font general information */  

  i = start;  
  for(;;)
  {
    if ( ucg_pgm_read((ucg_pgm_uint8_t *)(p)) == 255 )
    {
      p += 1;
    }
    else
    {
      p += ucg_pgm_read( ((ucg_pgm_uint8_t *)(p)) + 2 ) & mask;
      p += data_structure_size;
    }
    if ( i == end )
      break;
    i++;
  }
    
  return p - (uint8_t *)font;
#endif
}

/*========================================================================*/
/* u8g interface, font access */

uint8_t ucg_GetFontBBXWidth(ucg_t *ucg)
{
  // OBSOLETE return ucg_font_GetBBXWidth(ucg->font);
  return ucg->font_info.max_char_width;		/* new font info structure */
}

uint8_t ucg_GetFontBBXHeight(ucg_t *ucg)
{
  // OBSOLETE return ucg_font_GetBBXHeight(ucg->font);
  return ucg->font_info.max_char_height;		/* new font info structure */
}

int8_t u8g_GetFontBBXOffX(ucg_t *ucg) UCG_NOINLINE;
int8_t u8g_GetFontBBXOffX(ucg_t *ucg)
{
  // OBSOLETE return ucg_font_GetBBXOffX(ucg->font);
  return ucg->font_info.x_offset;		/* new font info structure */
}

int8_t ucg_GetFontBBXOffY(ucg_t *ucg) UCG_NOINLINE;
int8_t ucg_GetFontBBXOffY(ucg_t *ucg)
{
  // OBSOLETE return ucg_font_GetBBXOffY(ucg->font);
  return ucg->font_info.y_offset;		/* new font info structure */
}

uint8_t ucg_GetFontCapitalAHeight(ucg_t *ucg) UCG_NOINLINE; 
uint8_t ucg_GetFontCapitalAHeight(ucg_t *ucg)
{
  // OBSOLETE return ucg_font_GetCapitalAHeight(ucg->font);
  return ucg->font_info.ascent_A;		/* new font info structure */
}

/*========================================================================*/
/* glyph handling */

uint8_t ucg_font_decode_get_unsigned_bits(ucg_font_decode_t *f, uint8_t cnt)
{
  uint8_t val;
  uint8_t bit_pos = f->decode_bit_pos;
  
  //val = *(f->decode_ptr);
  val = ucg_pgm_read( (ucg_pgm_uint8_t *)(f->decode_ptr) );  
  
  val >>= bit_pos;
  if ( bit_pos + cnt >= 8 )
  {
    f->decode_ptr++;
    //val |= *(f->decode_ptr) << (8-bit_pos);
    val |= ucg_pgm_read( (ucg_pgm_uint8_t *)(f->decode_ptr) ) << (8-bit_pos);
    bit_pos -= 8;
  }
  val &= (1U<<cnt)-1;
  bit_pos += cnt;
  
  f->decode_bit_pos = bit_pos;
  return val;
}


/*
    2 bit --> cnt = 2
      -2,-1,0. 1

    3 bit --> cnt = 3
      -2,-1,0. 1
      -4,-3,-2,-1,0,1,2,3

      if ( x < 0 )
	r = bits(x-1)+1;
    else
	r = bits(x)+1;

*/
int8_t ucg_font_decode_get_signed_bits(ucg_font_decode_t *f, uint8_t cnt)
{
  return (int8_t)ucg_font_decode_get_unsigned_bits(f, cnt) - ((1<<cnt)>>1);
}

/*
  Description:
    Draw a line with "cnt" pixel as fore- or background color.
  Args:
    cnt: 					Length of the line
    is_foreground			foreground/background?
    ucg->font_decode.target_x		X position
    ucg->font_decode.target_y		Y position
    ucg->font_decode.is_transparent	Transparent mode
  Return:
    -
  Calls:
    ucg_font_decode_draw_pixel()
  Called by:
    ucg_font_decode_len()
*/
void ucg_font_decode_draw_pixel(ucg_t *ucg, uint8_t cnt, uint8_t is_foreground)
{
  if ( is_foreground )
  {
    // TODO
    //tga_fd_draw_fg_pixel(f, cnt);
    ucg_Draw90Line(ucg, 
      ucg->font_decode.target_x + ucg->font_decode.x, 
      ucg->font_decode.target_y + ucg->font_decode.y, 
      cnt, 
      /* dir */ 0, 
      /* col_idx */ 0);   
  }
  else
  {
    // TODO
    //tga_fd_draw_bg_pixel(f, cnt);
  }
}

/*
  Description:
    Draw a run-length area of the glyph. "len" can have any size and the line
    length has to be wrapped at the glyph border.
  Args:
    len: 					Length of the line
    is_foreground			foreground/background?
    ucg->font_decode.target_x		X position
    ucg->font_decode.target_y		Y position
    ucg->font_decode.is_transparent	Transparent mode
  Return:
    -
  Calls:
    ucg_font_decode_draw_pixel()
  Called by:
    ucg_font_decode_glyph()
*/
void ucg_font_decode_len(ucg_t *ucg, uint8_t len, uint8_t is_foreground)
{
  uint8_t cnt, rem;
  cnt = len;
  for(;;)
  {
    rem = ucg->font_decode.glyph_width;
    rem -= ucg->font_decode.x;
    if ( cnt < rem )
      break;
    ucg_font_decode_draw_pixel(ucg,rem, is_foreground);
    cnt -= rem;
    ucg->font_decode.x = 0;
    ucg->font_decode.y++;
  }
  ucg_font_decode_draw_pixel(ucg, cnt, is_foreground);
  ucg->font_decode.x += cnt;
}

static void ucg_font_setup_decode(ucg_t *ucg, const uint8_t *glyph_data)
{
  ucg->font_decode.decode_ptr = glyph_data;
  ucg->font_decode.decode_bit_pos = 0;
  
  ucg->font_decode.decode_ptr += 1;
  ucg->font_decode.decode_ptr += 1;
  
  ucg->font_decode.glyph_width = ucg_font_decode_get_unsigned_bits(&(ucg->font_decode), ucg->font_info.bits_per_char_width);
  ucg->font_decode.glyph_height = ucg_font_decode_get_unsigned_bits(&(ucg->font_decode),ucg->font_info. bits_per_char_height);
}


/*
  Description:
    Decode and draw a glyph.
  Args:
    glyph_data: 					Pointer to the compressed glyph data of the font
    ucg->font_decode.target_x		X position
    ucg->font_decode.target_y		Y position
    ucg->font_decode.is_transparent	Transparent mode
  Return:
    Width (delta x advance) of the glyph.
  Calls:
    ucg_font_decode_len()
*/
unsigned ucg_font_decode_glyph(ucg_t *ucg, const uint8_t *glyph_data)
{
  ucg_int_t a, b;
  //unsigned cnt, rem;
  ucg_int_t x, y;
  ucg_int_t d = 0;
    
  ucg_font_setup_decode(ucg, glyph_data);
  
  x = ucg_font_decode_get_signed_bits(&(ucg->font_decode), ucg->font_info.bits_per_char_x);
  y = ucg_font_decode_get_signed_bits(&(ucg->font_decode), ucg->font_info.bits_per_char_y);
  d = ucg_font_decode_get_signed_bits(&(ucg->font_decode), ucg->font_info.bits_per_delta_x);
  
  if ( ucg->font_decode.glyph_width > 0 )
  {
    
    ucg->font_decode.target_x += x;
    ucg->font_decode.target_y -= ucg->font_decode.glyph_height ;
    ucg->font_decode.target_y -=y ;
        
    /* reset local x/y position */
    ucg->font_decode.x = 0;
    ucg->font_decode.y = 0;
    
    /* decode glyph */
    for(;;)
    {
      a = ucg_font_decode_get_unsigned_bits(&(ucg->font_decode), ucg->font_info.bits_per_0);
      b = ucg_font_decode_get_unsigned_bits(&(ucg->font_decode), ucg->font_info.bits_per_1);
      do
      {
	ucg_font_decode_len(ucg, a, 0);
	ucg_font_decode_len(ucg, b, 1);
      } while( ucg_font_decode_get_unsigned_bits(&(ucg->font_decode), 1) != 0 );

      if ( ucg->font_decode.y >= ucg->font_decode.glyph_height )
	break;
    }
  }
  return d;
}

/*
  Description:
    Find the starting point of the glyph data.
  Args:
    encoding: Encoding (ASCII code) of the glyph
  Return:
    Address of the glyph data or NULL, if the encoding is not avialable in the font.
*/
const uint8_t *ucg_font_get_glyph_data(ucg_t *ucg, uint8_t encoding)
{
  const uint8_t *font = ucg->font;
  font += UCG_FONT_DATA_STRUCT_SIZE;
  
  for(;;)
  {
    if ( ucg_pgm_read( ((ucg_pgm_uint8_t *)font) + 1 ) == 0 )
      break;
    if ( ucg_pgm_read( (ucg_pgm_uint8_t *)font ) == encoding )
    {
      return font;
    }
    font += ucg_pgm_read( ((ucg_pgm_uint8_t *)font) + 1 );
  }
  return NULL;
}

ucg_int_t ucg_font_draw_glyph(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t encoding, uint8_t is_transparent)
{
  ucg_int_t dx = 0;
  ucg->font_decode.target_x = x;
  ucg->font_decode.target_y = y;
  ucg->font_decode.is_transparent = is_transparent;
  const uint8_t *glyph_data = ucg_font_get_glyph_data(ucg, encoding);
  if ( glyph_data != NULL )
  {
    dx = ucg_font_decode_glyph(ucg, glyph_data);
  }
  return dx;
}


#ifdef OLD_CODE
static void ucg_CopyGlyphDataToCache(ucg_t *ucg, ucg_glyph_t g)
{
  uint8_t tmp;
  switch( ucg_font_GetFormat(ucg->font) )
  {
    case 0:
    case 2:
  /*
    format 0
    glyph information 
    offset
    0             BBX width                                       unsigned
    1             BBX height                                      unsigned
    2             data size                                          unsigned    (BBX width + 7)/8 * BBX height
    3             DWIDTH                                          signed
    4             BBX xoffset                                    signed
    5             BBX yoffset                                    signed
  byte 0 == 255 indicates empty glyph
  */
      ucg->glyph_width =  ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 0 );
      ucg->glyph_height =  ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 1 );
      ucg->glyph_dx =  ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 3 );
      ucg->glyph_x =  ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 4 );
      ucg->glyph_y =  ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 5 );
      break;
    case 1:
    default:
      /*
format 1
  0             BBX xoffset                                    signed   --> upper 4 Bit
  0             BBX yoffset                                    signed --> lower 4 Bit
  1             BBX width                                       unsigned --> upper 4 Bit
  1             BBX height                                      unsigned --> lower 4 Bit
  2             data size                                           unsigned -(BBX width + 7)/8 * BBX height  --> lower 4 Bit
  2             DWIDTH                                          signed --> upper  4 Bit
  byte 0 == 255 indicates empty glyph
      */
    
      tmp = ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 0 );
      ucg->glyph_y =  tmp & 15;
      ucg->glyph_y-=2;
      tmp >>= 4;
      ucg->glyph_x =  tmp;
    
      tmp = ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 1 );
      ucg->glyph_height =  tmp & 15;
      tmp >>= 4;
      ucg->glyph_width =  tmp;
      
      tmp = ucg_pgm_read( ((ucg_pgm_uint8_t *)g) + 2 );
      tmp >>= 4;
      ucg->glyph_dx = tmp;
    
      
      break;
  }
}

//void ucg_FillEmptyGlyphCache(u8g_t *ucg) UCG_NOINLINE;
static void ucg_FillEmptyGlyphCache(ucg_t *ucg)
{
  ucg->glyph_dx = 0;
  ucg->glyph_width = 0;
  ucg->glyph_height = 0;
  ucg->glyph_x = 0;
  ucg->glyph_y = 0;
}

/*
  Find (with some speed optimization) and return a pointer to the glyph data structure
  Also uncompress (format 1) and copy the content of the data structure to the u8g structure
*/
ucg_glyph_t ucg_GetGlyph(ucg_t *ucg, uint8_t requested_encoding)
{
  uint8_t *p = (uint8_t *)(ucg->font);
  uint8_t font_format;
  uint8_t data_structure_size;
  uint8_t start, end;
  uint16_t pos;
  uint8_t i;
  uint8_t mask = 255;
  
  if ( p == NULL )
    return NULL;
  
  font_format = ucg_font_GetFormat(ucg->font);
  data_structure_size = ucg_font_GetFontGlyphStructureSize(ucg->font);

  if ( font_format == 1 )
    mask = 15;
  
  start = ucg_font_GetFontStartEncoding(ucg->font);
  end = ucg_font_GetFontEndEncoding(ucg->font);

  pos = ucg_font_GetEncoding97Pos(ucg->font);
  if ( requested_encoding >= 97 && pos > 0 )
  {
    p+= pos;
    start = 97;
  }
  else 
  {
    pos = ucg_font_GetEncoding65Pos(ucg->font);
    if ( requested_encoding >= 65 && pos > 0 )
    {
      p+= pos;
      start = 65;
    }
    else
      p += UCG_FONT_DATA_STRUCT_SIZE;       /* skip font general information */  
  }
  
  if ( requested_encoding > end )
  {
    ucg_FillEmptyGlyphCache(ucg);
    return NULL;                      /* not found */
  }
  
  i = start;
  if ( i <= end )
  {
    for(;;)
    {
      if ( ucg_pgm_read((ucg_pgm_uint8_t *)(p)) == 255 )
      {
        p += 1;
      }
      else
      {
        if ( i == requested_encoding )
        {
          ucg_CopyGlyphDataToCache(ucg, p);
          return p;
        }
        p += ucg_pgm_read( ((ucg_pgm_uint8_t *)(p)) + 2 ) & mask;
        p += data_structure_size;
      }
      if ( i == end )
        break;
      i++;
    }
  }
  
  ucg_FillEmptyGlyphCache(ucg);
    
  return NULL;
}
#endif /* OLD_CODE */

uint8_t ucg_IsGlyph(ucg_t *ucg, uint8_t requested_encoding)
{
  /* updated to new code */
  if ( ucg_font_get_glyph_data(ucg, requested_encoding) != NULL )
    return 1;
  return 0;
}

/*
int8_t ucg_GetGlyphDeltaX(ucg_t *ucg, uint8_t requested_encoding)
{
  if ( ucg_GetGlyph(ucg, requested_encoding) == NULL )
    return 0; 
  return ucg->glyph_dx;
}
*/

int8_t ucg_GetGlyphWidth(ucg_t *ucg, uint8_t requested_encoding)
{
  const uint8_t *glyph_data = ucg_font_get_glyph_data(ucg, requested_encoding);
  if ( glyph_data == NULL )
    return 0; 
  
  ucg_font_setup_decode(ucg, glyph_data);
  return ucg->font_decode.glyph_width;
}

#ifdef OLD_CODE
ucg_int_t ucg_draw_transparent_glyph(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, uint8_t encoding)
{
  const ucg_pgm_uint8_t *data;
  uint8_t j;
  ucg_int_t dx, dy;
  uint8_t bytes_per_line;

  {
    ucg_glyph_t g = ucg_GetGlyph(ucg, encoding);
    if ( g == NULL  )
      return 0;
    data = ucg_font_GetGlyphDataStart(ucg->font, g);
  }
  
  bytes_per_line = ucg->glyph_width;
  bytes_per_line += 7;
  bytes_per_line /= 8;
    
  dx = 0;
  dy = 0;
  switch(dir)
  {
    case 0:
      x += ucg->glyph_x;
      y -= ucg->glyph_y;
      y -= ucg->glyph_height;
      dy = 1;
      break;
    case 1:
      x += ucg->glyph_y;
      y += ucg->glyph_x;
      x += ucg->glyph_height;
      dx = -1;
      break;
    case 2:
      x -= ucg->glyph_x;
      y += ucg->glyph_y;
      y += ucg->glyph_height;
      dy = -1;
      break;
    case 3:
      x -= ucg->glyph_y;
      y -= ucg->glyph_x;
      x -= ucg->glyph_height;
      dx = 1;
      break;
  }

  for( j = 0; j < ucg->glyph_height; j++ )
  {
    //ucg_DrawPixel(ucg, x,y);
    ucg_DrawTransparentBitmapLine(ucg, x, y, dir, ucg->glyph_width, data);
    data += bytes_per_line;
    y+=dy;
    x+=dx;
  }
  
  return ucg->glyph_dx;
}

ucg_int_t ucg_draw_solid_glyph(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, uint8_t encoding)
{
  const ucg_pgm_uint8_t *data;
  uint8_t j;
  ucg_int_t dx, dy;
  uint8_t bytes_per_line;
  ucg_int_t above;
  ucg_int_t below;
  ucg_int_t right;
  ucg_int_t left;

  {
    ucg_glyph_t g = ucg_GetGlyph(ucg, encoding);
    if ( g == NULL  )
      return 0;
    data = ucg_font_GetGlyphDataStart(ucg->font, g);
  }
  
  above = ucg->font_ref_ascent;
  above -= ucg->glyph_height;
  above -= ucg->glyph_y;
  if ( above < 0 )
    above = 0;
  
  below = ucg->font_ref_descent; 
  below -= ucg->glyph_y;
  if ( below > 0 )
    below = 0;
  
  right = ucg->glyph_dx;
  right -= ucg->glyph_width;
  right -= ucg->glyph_x;
  if ( right < 0 )
    right = 0;
  
  left = ucg->glyph_x;
  if ( left < 0 )
    left = 0;
  
  bytes_per_line = ucg->glyph_width;
  bytes_per_line += 7;
  bytes_per_line /= 8;
    
  dx = 0;
  dy = 0;
  switch(dir)
  {
    case 0:
      x += ucg->glyph_x;
      y -= ucg->glyph_y;
      y -= ucg->glyph_height;
      y -= above;		/* solid */
      dy = 1;
      break;
    case 1:
      x += ucg->glyph_y;
      y += ucg->glyph_x;
      x += ucg->glyph_height;
      x += above;		/* solid */
      dx = -1;
      break;
    case 2:
      x -= ucg->glyph_x;
      y += ucg->glyph_y;
      y += ucg->glyph_height;
      y += above;		/* solid */
      dy = -1;
      break;
    case 3:
      x -= ucg->glyph_y;
      y -= ucg->glyph_x;
      x -= ucg->glyph_height;
      x -= above;		/* solid */
      dx = 1;
      break;
  }

  while( above > 0 )
  {
    ucg_Draw90Line(ucg, x, y, ucg->glyph_width, dir, 1);
    y+=dy;
    x+=dx;
    above--;
  }
  for( j = 0; j < ucg->glyph_height; j++ )
  {
    ucg_DrawBitmapLine(ucg, x, y, dir, ucg->glyph_width, data);
    data += bytes_per_line;
    y+=dy;
    x+=dx;
  }
  while( below < 0 )
  {
    ucg_Draw90Line(ucg, x, y, ucg->glyph_width, dir, 1);
    y+=dy;
    x+=dx;
    below++;
  }
  y-=dy;
  x-=dx;
  
  for( j = 0; j < left; j++ )
  {
    x-=dy;
    y-=dx;
    ucg_Draw90Line(ucg, x, y, ucg->font_ref_ascent-ucg->font_ref_descent, (dir+3)&3, 1);
  }
  x+=dy*(ucg->glyph_width+left);
  y+=dx*(ucg->glyph_width+left);      
  while( right > 0 )
  {
    ucg_Draw90Line(ucg, x, y, ucg->font_ref_ascent-ucg->font_ref_descent, (dir+3)&3, 1);
    x+=dy;
    y+=dx;
    right--;
  }
  
  return ucg->glyph_dx;
}

#endif /* OLD_CODE */

/*
  set one of:
    UCG_FONT_MODE_TRANSPARENT
    UCG_FONT_MODE_SOLID
    UCG_FONT_MODE_NONE
*/
void ucg_SetFontMode(ucg_t *ucg, ucg_font_mode_fnptr font_mode)
{
  //ucg->font_mode = font_mode;
}

ucg_int_t ucg_DrawGlyph(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, uint8_t encoding)
{
  // OBSOLETE if ( ucg->font_mode == UCG_FONT_MODE_NONE )
  // OBSOLETE   return 0;
  switch(dir)
  {
    case 0:
      y += ucg->font_calc_vref(ucg);
      break;
    case 1:
      x -= ucg->font_calc_vref(ucg);
      break;
    case 2:
      y -= ucg->font_calc_vref(ucg);
      break;
    case 3:
      x += ucg->font_calc_vref(ucg);
      break;
  }
  //return ucg->font_mode(ucg, x, y, dir, encoding);
  return ucg_font_draw_glyph(ucg, x, y, encoding, /* is_transparent */ 1);
}

ucg_int_t ucg_DrawString(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, const char *str)
{
  ucg_int_t delta, sum;
  sum = 0;
  while( *str != '\0' )
  {
    delta = ucg_DrawGlyph(ucg, x, y, dir, (uint8_t)*str);
    
    switch(dir)
    {
      case 0:
	x += delta;
	break;
      case 1:
	y += delta;
	break;
      case 2:
	x -= delta;
	break;
      case 3:
	y -= delta;
	break;
    }
    sum += delta;    
    str++;
  }
  return sum;
}


/*===============================================*/

/* set ascent/descent for reference point calculation */

void ucg_UpdateRefHeight(ucg_t *ucg)
{
  if ( ucg->font == NULL )
    return;
  ucg->font_ref_ascent = ucg->font_info.ascent_A;
  ucg->font_ref_descent = ucg->font_info.descent_g;
  if ( ucg->font_height_mode == UCG_FONT_HEIGHT_MODE_TEXT )
  {
  }
  else if ( ucg->font_height_mode == UCG_FONT_HEIGHT_MODE_XTEXT )
  {
    if ( ucg->font_ref_ascent < ucg->font_info.ascent_para )
      ucg->font_ref_ascent = ucg->font_info.ascent_para;
    if ( ucg->font_ref_descent > ucg->font_info.descent_para )
      ucg->font_ref_descent = ucg->font_info.descent_para;
  }
  else
  {
    if ( ucg->font_ref_ascent < ucg->font_info.max_char_height )
      ucg->font_ref_ascent = ucg->font_info.max_char_height;
    if ( ucg->font_ref_descent > ucg->font_info.y_offset )
      ucg->font_ref_descent = ucg->font_info.y_offset;
  }  
}

void ucg_SetFontRefHeightText(ucg_t *ucg)
{
  ucg->font_height_mode = UCG_FONT_HEIGHT_MODE_TEXT;
  ucg_UpdateRefHeight(ucg);
}

void ucg_SetFontRefHeightExtendedText(ucg_t *ucg)
{
  ucg->font_height_mode = UCG_FONT_HEIGHT_MODE_XTEXT;
  ucg_UpdateRefHeight(ucg);
}

void ucg_SetFontRefHeightAll(ucg_t *ucg)
{
  ucg->font_height_mode = UCG_FONT_HEIGHT_MODE_ALL;
  ucg_UpdateRefHeight(ucg);
}

/*===============================================*/
/* callback procedures to correct the y position */

ucg_int_t ucg_font_calc_vref_font(ucg_t *ucg)
{
  return 0;
}

void ucg_SetFontPosBaseline(ucg_t *ucg)
{
  ucg->font_calc_vref = ucg_font_calc_vref_font;
}


ucg_int_t ucg_font_calc_vref_bottom(ucg_t *ucg)
{
  return (ucg_int_t)(ucg->font_ref_descent);
}

void ucg_SetFontPosBottom(ucg_t *ucg)
{
  ucg->font_calc_vref = ucg_font_calc_vref_bottom;
}

ucg_int_t ucg_font_calc_vref_top(ucg_t *ucg)
{
  ucg_int_t tmp;
  /* reference pos is one pixel above the upper edge of the reference glyph */
  tmp = (ucg_int_t)(ucg->font_ref_ascent);
  tmp++;
  return tmp;
}

void ucg_SetFontPosTop(ucg_t *ucg)
{
  ucg->font_calc_vref = ucg_font_calc_vref_top;
}

ucg_int_t ucg_font_calc_vref_center(ucg_t *ucg)
{
  int8_t tmp;
  tmp = ucg->font_ref_ascent;
  tmp -= ucg->font_ref_descent;
  tmp /= 2;
  tmp += ucg->font_ref_descent;  
  return tmp;
}

void ucg_SetFontPosCenter(ucg_t *ucg)
{
  ucg->font_calc_vref = ucg_font_calc_vref_center;
}

/*===============================================*/

void ucg_SetFont(ucg_t *ucg, const ucg_fntpgm_uint8_t  *font)
{
  if ( ucg->font != font )
  {
    ucg->font = font;
    ucg_read_font_info(&(ucg->font_info), font);
    ucg_UpdateRefHeight(ucg);
    //ucg_SetFontPosBaseline(ucg);
  }
}

/*===============================================*/

ucg_int_t ucg_GetStrWidth(ucg_t *ucg, const char *s)
{
  ucg_int_t  w;
  uint8_t encoding;
  
  /* reset the total width to zero, this will be expanded during calculation */
  w = 0;
  
  for(;;)
  {
    encoding = *s;
    if ( encoding == 0 )
      break;

    /* load glyph information */
    // OBSOLETE ucg_GetGlyph(ucg, encoding);
    // OBSOLETE w += ucg->glyph_dx;    
    
    // replaced by this:
    w += ucg_GetGlyphWidth(ucg, encoding);
    
    /* goto next char */
    s++;
  }
  
  return w;  
}
