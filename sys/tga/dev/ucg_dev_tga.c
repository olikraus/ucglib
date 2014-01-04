

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static uint16_t tga_width;
static uint16_t tga_height;
static uint8_t *tga_data = NULL;

int tga_init(uint16_t w, uint16_t h)
{
  tga_width = 0;
  tga_height = 0;
  if ( tga_data != NULL )
    free(tga_data);
  tga_data = (uint8_t *)malloc(w*h*3);
  if ( tga_data == NULL )
    return 0;
  tga_width = w;
  tga_height = h;
  memset(tga_data, 255, w*h*3);
  return 1;
}

void tga_set_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t *p;
  p = tga_data + (tga_height-y-1)*tga_width*3 + x*3;
  *p++ = b;
  *p++ = g;
  *p++ = r;
}

void tga_write_byte(FILE *fp, uint8_t byte)
{
  fputc(byte, fp);
}

void tga_write_word(FILE *fp, uint16_t word)
{
  tga_write_byte(fp, word&255);
  tga_write_byte(fp, word>>8);
}

void tga_save(const char *name)
{
  FILE *fp;
  fp = fopen(name, "wb");
  if ( fp != NULL )
  {
    tga_write_byte(fp, 0);		/* no ID */
    tga_write_byte(fp, 0);		/* no color map */
    tga_write_byte(fp, 2);		/* uncompressed true color */
    tga_write_word(fp, 0);		
    tga_write_word(fp, 0);		
    tga_write_byte(fp, 0);		
    tga_write_word(fp, 0);		/* x origin */
    tga_write_word(fp, 0);		/* y origin */
    tga_write_word(fp, tga_width);		/* width */
    tga_write_word(fp, tga_height);		/* height */
    tga_write_byte(fp, 24);		/* color depth */
    tga_write_byte(fp, 0);		
    fwrite(tga_data, tga_width*tga_height*3, 1, fp);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    fwrite("TRUEVISION-XFILE.", 18, 1, fp);
    fclose(fp);
  }
}

int main(void)
{
  tga_init(10, 20);
  tga_set_pixel(1,1, 255,0,0);
  tga_set_pixel(2,2, 0,255,0);
  tga_save("ucg.tga");
}
