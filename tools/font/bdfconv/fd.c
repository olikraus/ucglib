/*

  fd.c
  
  font decode
  
*/

#include "fd.h"
#include <stddef.h>


void fd_init(fd_t *fd)
{
  fd->is_transparent = 1;  
}

void fd_set_font(fd_t *fd, uint8_t *font)
{
    fd->glyph_cnt = *font++;
    fd->bits_per_0 = *font++;
    fd->bits_per_1 = *font++;
    fd->bits_per_char_width = *font++;
    fd->bits_per_char_height = *font++;
    fd->bits_per_char_x = *font++;
    fd->bits_per_char_y = *font++;
    fd->bits_per_delta_x = *font++;
    fd->char_width = *font++;
    fd->char_height = *font++;
    font++;	/* x offset */
    fd->char_descent = *(int8_t *)font;
    font++;
  
    font++;
    font++;
    font++;
    font++;
    
    fd->font = font;
}

uint8_t *fd_get_glyph_data(fd_t *fd, uint8_t encoding)
{
  int i;
  uint8_t *font = fd->font;
  for( i = 0; i < fd->glyph_cnt; i++ )
  {
    if ( font[0] == encoding )
    {
      return font;
    }
    font += font[1];
  }
  return NULL;
}

unsigned fd_get_unsigned_bits(fd_t *f, unsigned cnt)
{
  unsigned val;
  unsigned bit_pos = f->decode_bit_pos;
  
  val = *(f->decode_ptr);
  
  val >>= bit_pos;
  if ( bit_pos + cnt >= 8 )
  {
    f->decode_ptr++;
    val |= *(f->decode_ptr) << (8-bit_pos);
    bit_pos -= 8;
  }
  val &= (1U<<cnt)-1;
  bit_pos += cnt;
  
  f->decode_bit_pos = bit_pos;
  return val;
}

int fd_get_signed_bits(fd_t *fd, int cnt)
{
  return (int)fd_get_unsigned_bits(fd, cnt) - ((1<<cnt)>>1);
}

void fd_draw_pixel(fd_t *f, unsigned cnt, unsigned is_foreground)
{
  if ( is_foreground )
  {
    tga_fd_draw_fg_pixel(f, cnt);
  }
  else
  {
    tga_fd_draw_bg_pixel(f, cnt);
  }
}

void fd_decode_len(fd_t *fd, unsigned len, unsigned is_foreground)
{
  unsigned cnt, rem;
  cnt = len;
  for(;;)
  {
    rem = fd->glyph_width;
    rem -= fd->x;
    if ( cnt < rem )
      break;
    fd_draw_pixel(fd,rem, is_foreground);
    cnt -= rem;
    fd->x = 0;
    fd->y++;
  }
  fd_draw_pixel(fd, cnt, is_foreground);
  fd->x += cnt;
}

/*
  expects:
    unsigned target_x;
    unsigned target_y;
    unsigned is_transparent;
    const uint8_t *decode_ptr;
*/
unsigned fd_decode(fd_t *f)
{
  unsigned a, b;
  int x, y;
  unsigned d = 0;
    
  f->decode_bit_pos = 0;
  
  f->decode_ptr += 1;
  f->decode_ptr += 1;
  
  f->glyph_width = fd_get_unsigned_bits(f, f->bits_per_char_width);
  f->glyph_height = fd_get_unsigned_bits(f, f->bits_per_char_height);
  x = fd_get_signed_bits(f, f->bits_per_char_x);
  y = fd_get_signed_bits(f, f->bits_per_char_y);
  d = fd_get_signed_bits(f, f->bits_per_delta_x);
  
  if ( f->glyph_width > 0 )
  {
    
    f->target_x += x;
    f->target_y -= f->glyph_height ;
    f->target_y -=y ;
        
    f->x = 0;
    f->y = 0;
    
    for(;;)
    {
      a = fd_get_unsigned_bits(f, f->bits_per_0);
      b = fd_get_unsigned_bits(f, f->bits_per_1);
      do
      {
	fd_decode_len(f, a, 0);
	fd_decode_len(f, b, 1);
      } while( fd_get_unsigned_bits(f, 1) != 0 );

      if ( f->y >= f->glyph_height )
	break;
    }
  }
  return d;
}

unsigned fd_draw_glyph(fd_t *fd, unsigned x, unsigned y, uint8_t encoding)
{
  unsigned dx = 0;
  fd->target_x = x;
  fd->target_y = y;
  fd->decode_ptr = fd_get_glyph_data(fd, encoding);
  if ( fd->decode_ptr != NULL )
  {
    dx = fd_decode(fd);
  }
  return dx;
}

unsigned fd_draw_string(fd_t *fd, unsigned x, unsigned y, const char *s)
{
  unsigned dx = 0;
  while( *s != '\0' )
  {
    dx += fd_draw_glyph(fd, x+dx,y,*s);
    s++;
  }
  return dx;
}





