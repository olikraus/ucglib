
/* MCG: Memory Color Graphics */

#include <SPI.h>

#define MCG_RESET_PIN 8
#define MCG_CS_PIN 10
#define MCG_DC_PIN 9


uint8_t frame_buffer[128*128*3];


void mcg_reset(void)
{
  delay(100);
  digitalWrite(MCG_RESET_PIN, 1);
  digitalWrite(MCG_CS_PIN, 1);
  delay(100);
  digitalWrite(MCG_RESET_PIN, 0);
  delay(100);
  digitalWrite(MCG_RESET_PIN, 1);
  delay(100);
}

void mcg_send_cmd(uint8_t cmd)
{
  digitalWrite(MCG_DC_PIN, 0);
  SPI.transfer(cmd);  
}

void mcg_send_arg(uint8_t arg)
{
  digitalWrite(MCG_DC_PIN, 1);  
  SPI.transfer(arg);
}

void mcg_c0(uint8_t cmd)
{
  mcg_send_cmd(cmd);
}

void mcg_c1(uint8_t cmd, uint8_t a1)
{
  mcg_send_cmd(cmd);
  mcg_send_arg(a1);
}

void mcg_c2(uint8_t cmd, uint8_t a1, uint8_t a2)
{
  mcg_send_cmd(cmd);
  mcg_send_arg(a1);
  mcg_send_arg(a2);
}

void mcg_c3(uint8_t cmd, uint8_t a1, uint8_t a2, uint8_t a3)
{
  mcg_send_cmd(cmd);
  mcg_send_arg(a1);
  mcg_send_arg(a2);
  mcg_send_arg(a3);
}

void mcg_a3(uint8_t a1, uint8_t a2, uint8_t a3)
{
  mcg_send_arg(a1);
  mcg_send_arg(a2);
  mcg_send_arg(a3);
}


void mcg_init(void)
{
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(MCG_CS_PIN, 0);
  delay(1);
  mcg_c1(0x0fd, 0x0b1),			/* Unlock extra commands, reset default: locked */
  mcg_c0(0x0af),				/* Set Display On */
  mcg_c0(0x0a6),				/* Set Display Mode Reset */
  mcg_c1(0x0a0, 0x0b4),			/* Set Colour Depth */
  mcg_c1(0x0a1, 0x000),			/* Set Display Start Line */
  mcg_c1(0x0a2, 0x000),			/* Set Display Offset */
  mcg_c2(0x015, 0x000, 0x07f),	/* Set Column Address */
  mcg_c2(0x075, 0x000, 0x07f),	/* Set Row Address */

  mcg_c1(0x0b3, 0x0f1),			/* Front Clock Div */
  mcg_c1(0x0b5, 0x000),		/* Set GPIO */
  mcg_c1(0x0b1, 0x032),		/* Set Phase Length, reset default: 0x82 */
  mcg_c3(0x0b4, 0xa0,0xb5,0x55),		/* Set Segment Low Voltage, reset default: 0xa2 0xb5 0x55 */
  mcg_c3(0x0c1, 0xc8, 0x80, 0xc8),	/* Set Contrast */
  mcg_c1(0x0c7, 0x00f),			/* Set Master Contrast (0..15), reset default: 0x05 */
  mcg_c1(0x0b6, 0x001),		/* Set Second Precharge Period */
  
  mcg_c0(0x05c),				/* write RAM */
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  mcg_a3(63, 63, 63);
  delay(1);
  digitalWrite(MCG_CS_PIN, 1);
  SPI.endTransaction();
}

void mcg_send_frame_buffer(void)
{
  int32_t cnt;
  cnt = 128*128*3;
  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  digitalWrite(MCG_CS_PIN, 0);
  delay(1);
  mcg_c2(0x015, 0x000, 0x07f),	/* Set Column Address */
  mcg_c2(0x075, 0x000, 0x07f),	/* Set Row Address */
  mcg_c0(0x05c),				/* write RAM */
  
  digitalWrite(MCG_DC_PIN, 1);  
  //SPI.transfer(frame_buffer, 128*128*3);
  do
  {
    cnt--;
    SPI.transfer(frame_buffer[cnt]);
  } while( cnt > 0 );
  delay(1);
  digitalWrite(MCG_CS_PIN, 1);
  SPI.endTransaction();
  
}

void mcd_fb_clear(uint8_t r, uint8_t g, uint8_t b)
{
  int32_t cnt;
  uint8_t *p;
  cnt = 128*128;
  p = frame_buffer;
  do
  {
    *p++ = r;
    *p++ = g;
    *p++ = b;
    cnt--;
  } while( cnt > 0 );
}

void mcd_fb_set_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a )
{
  uint16_t i;
  uint16_t t;
  uint8_t *p;
  uint8_t na = 63 - a;
  
  i = y;
  i *= 128;
  i += x;
  i *= 3;
  p = frame_buffer;
  p += i;
  
  t = a * (*p);
  t += na * r;
  t >>= 6;
  *p++  = t;
  
  t = a * (*p);
  t += na * g;
  t >>= 6;
  *p++  = t;

  t = a * (*p);
  t += na * b;
  t >>= 6;
  *p++  = t;

}


void mcd_fb_set_brush(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t *src)
{
  uint16_t i, j;
  for( i = 0; i < h; i++ )
  {
    for( j = 0; j < w; j++ )
    {
      mcd_fb_set_pixel(x + j, y + i, src[0], src[1], src[2], src[3]);
      src += 4;
    }
  }
}

uint8_t brush_circle[9*4] = 
{
  255, 255, 255,  43,     			255, 255, 255, 20,   255, 255, 255,  43,
  255, 255, 255, 20,     		255, 255, 255, 0,   	255, 255, 255, 20,
  255, 255, 255,  43,     			255, 255, 255, 20,   255, 255, 255,  43,
};



void setup(void)
{
  pinMode(MCG_RESET_PIN, OUTPUT);
  pinMode(MCG_CS_PIN, OUTPUT);
  pinMode(MCG_DC_PIN, OUTPUT);
  SPI.begin();
  delay(10);
  mcg_reset();
  mcg_init();
  mcd_fb_clear(3, 3, 3);
  mcg_send_frame_buffer();
}

uint16_t i = 10;

void loop(void)
{
  mcd_fb_set_brush(i, i, 3, 3, brush_circle);
  //mcd_fb_set_pixel(i, i, 0, 63, 0, 0 );
  i++;
  
  mcg_send_frame_buffer();
  if ( i > 100 )
  {
    mcd_fb_clear(0, 0, 0);
    i = 3;
  }

  /*
  mcd_fb_clear(0, 63, 0);
  mcg_send_frame_buffer();
  delay(1000);
  mcd_fb_clear(0, 0, 63);
  mcg_send_frame_buffer();
  delay(1000);
  mcd_fb_clear(3, 3, 3);
  mcg_send_frame_buffer();
  delay(1000);
  */
  delay(100);
}

