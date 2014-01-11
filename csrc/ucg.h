/*

  ucg.h

  ucglib = universal color graphics library
  ucglib = micro controller graphics library
  
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
  

  SW layers
  
  High Level Procedures
    [ hline, init message interface ]
  display callback procedure
    [Calls to]
  device dev cb 		
    [calls to COM API]
  com callback

*/

#ifndef _UCG_H
#define _UCG_H

#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef ARDUINO
#ifndef USE_PIN_LIST
#define USE_PIN_LIST
#endif
#endif

#ifdef __GNUC__
#  define UCG_NOINLINE __attribute__((noinline))
#  define UCG_SECTION(name) __attribute__ ((section (name)))
#  if defined(__MSPGCC__)
/* mspgcc does not have .progmem sections. Use -fdata-sections. */
#    define UCG_FONT_SECTION(name)
#  elif defined(__AVR__)
#    define UCG_FONT_SECTION(name) UCG_SECTION(".progmem." name)
#  else
#    define UCG_FONT_SECTION(name)
#  endif
#else
#  define UCG_NOINLINE
#  define UCG_SECTION(name)
#  define UCG_FONT_SECTION(name)
#endif

#if defined(__AVR__)
#include <avr/pgmspace.h>
/* UCG_PROGMEM is used by the XBM example */
#define UCG_PROGMEM UCG_SECTION(".progmem.data")
typedef uint8_t PROGMEM ucg_pgm_uint8_t;
typedef uint8_t ucg_fntpgm_uint8_t;
#define ucg_pgm_read(adr) pgm_read_byte_near(adr)
#define UCG_PSTR(s) ((ucg_pgm_uint8_t *)PSTR(s))
#else
#define UCG_PROGMEM
#define PROGMEM
typedef uint8_t ucg_pgm_uint8_t;
typedef uint8_t ucg_fntpgm_uint8_t;
#define ucg_pgm_read(adr) (*(const ucg_pgm_uint8_t *)(adr)) 
#define UCG_PSTR(s) ((ucg_pgm_uint8_t *)(s))
#endif

/*================================================*/
/* several type and forward definitions */

typedef int16_t ucg_int_t;
typedef struct _ucg_t ucg_t;
typedef struct _ucg_xy_t ucg_xy_t;
typedef struct _ucg_wh_t ucg_wh_t;
typedef struct _ucg_box_t ucg_box_t;
typedef struct _ucg_color_t ucg_color_t;
typedef struct _ucg_ccs_t ucg_ccs_t;
typedef struct _ucg_pixel_t ucg_pixel_t;
typedef struct _ucg_arg_t ucg_arg_t;
typedef struct _ucg_com_info_t ucg_com_info_t;

typedef ucg_int_t (*ucg_dev_fnptr)(ucg_t *ucg, ucg_int_t msg, void *data); 
typedef int16_t (*ucg_com_fnptr)(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data); 
typedef ucg_int_t (*ucg_font_calc_vref_fnptr)(ucg_t *ucg);

/*================================================*/
/* list of supported display modules */

ucg_int_t ucg_dev_ssd1351_128x128_oled_ilsoft(ucg_t *ucg, ucg_int_t msg, void *data);
ucg_int_t ucg_dev_ili9325_240x320_tft_itdb02(ucg_t *ucg, ucg_int_t msg, void *data);


/*================================================*/
/* 
  list of extensions for the controllers 
  
  each module can have the "none" extension (ucg_ext_none) or the specific
  extensions, that matches the controller name.
  
  example: for the module u8g_dev_ssd1351_128x128_oled_ilsoft
  valid extensions are:
  
  extensions are only valid if the controller name matches, for example
    ucg_ext_none
    ucg_ext_ssd1351
*/

ucg_int_t ucg_ext_none(ucg_t *ucg, ucg_int_t msg, void *data);

ucg_int_t ucg_ext_ssd1351(ucg_t *ucg, ucg_int_t msg, void *data);
ucg_int_t ucg_ext_ili9325(ucg_t *ucg, ucg_int_t msg, void *data);


/*================================================*/
/* list of supported display controllers */

ucg_int_t ucg_dev_ic_ssd1351(ucg_t *ucg, ucg_int_t msg, void *data);
ucg_int_t ucg_dev_ic_ili9325(ucg_t *ucg, ucg_int_t msg, void *data);


/*================================================*/
/* struct declarations */

struct _ucg_xy_t
{
  ucg_int_t x;
  ucg_int_t y;
};

struct _ucg_wh_t
{
  ucg_int_t w;  
  ucg_int_t h;
};

struct _ucg_box_t
{
  ucg_xy_t ul;
  ucg_wh_t size;
};

struct _ucg_color_t
{
  uint8_t color[3];		/* 0: Red, 1: Green, 2: Blue */
};

struct _ucg_ccs_t
{
  uint8_t current;	/* contains the current color component */
  uint8_t start;
  ucg_int_t dir;		/* 1 if start < end or -1 if start > end */
  ucg_int_t num;
  ucg_int_t quot;
  
  ucg_int_t den;
  ucg_int_t rem;  
  ucg_int_t frac;
};

struct _ucg_pixel_t
{
  ucg_xy_t pos;
  ucg_color_t rgb;  
};

struct _ucg_arg_t
{
  ucg_pixel_t pixel;
  ucg_int_t len;
  ucg_int_t dir;
  ucg_int_t offset;			/* calculated offset from the inital point to the start of the clip window (ucg_clip_l90fx) */
  const unsigned char *bitmap;
  ucg_int_t pixel_skip;		/* within the "bitmap" skip the specified number of pixel with the bit. pixel_skip is always <= 7 */
  ucg_color_t rgb[4];		/* start and end color for L90SE , two more colors for the gradient box */
  ucg_ccs_t ccs_line[3];	/* color component sliders used by L90SE */
};

#define UCG_FONT_HEIGHT_MODE_TEXT 0
#define UCG_FONT_HEIGHT_MODE_XTEXT 1
#define UCG_FONT_HEIGHT_MODE_ALL 2

struct _ucg_com_info_t
{
  uint16_t serial_clk_speed;
  uint16_t parallel_clk_speed;
};

#ifdef USE_PIN_LIST
#define UCG_PIN_RST 0
#define UCG_PIN_CD 1
#define UCG_PIN_CS 2
#define UCG_PIN_SCL 3
#define UCG_PIN_WR 3
#define UCG_PIN_SDA 4
#define UCG_PIN_COUNT 5

#define UCG_PIN_VAL_NONE 255
#endif

struct _ucg_t
{
  unsigned is_power_up:1;
  /* the dimension of the display */
  ucg_wh_t dimension;
  /* display callback procedure to handle display specific code */
  //ucg_dev_fnptr display_cb;
  /* controller and device specific code, high level procedure will call this */
  ucg_dev_fnptr device_cb;
  /* name of the extension cb. will be called by device_cb if required */
  ucg_dev_fnptr ext_cb;
  /* if rotation is applied, than this cb is called after rotation */
  ucg_dev_fnptr rotate_chain_device_cb;
  ucg_wh_t rotate_dimension;
  
  /* communication interface */
  ucg_com_fnptr com_cb;
  /* data which is passed to the cb procedures */
  /* can be modified by the cb procedures (rotation, clipping, etc) */
  ucg_arg_t arg;
  /* current window to which all drawing is clipped */
  /* should be modified via UCG_MSG_SET_CLIP_BOX by a device callback. */
  /* by default this is done by ucg_dev_default_cb */
  ucg_box_t clip_box;
  

  /* information about the current font */
  const unsigned char *font;             /* current font for all text procedures */
  ucg_font_calc_vref_fnptr font_calc_vref;
  
  int8_t glyph_dx;
  int8_t glyph_x;
  int8_t glyph_y;
  uint8_t glyph_width;
  uint8_t glyph_height;
  
  uint8_t font_height_mode;
  int8_t font_ref_ascent;
  int8_t font_ref_descent;

  /* only for Arduino/C++ Interface */
#ifdef USE_PIN_LIST
  uint8_t pin_list[UCG_PIN_COUNT];
#endif

  /* 
    Small amount of RAM for the com interface (com_cb).
    Might be unused on unix systems, where the com sub system is 
    not required, but should be usefull for all uC projects.
  */
  uint8_t com_initial_change_sent;	/* Bit 0: CD/A0 Line Status, Bit 1: CS Line Status, Bit 2: Reset Line Status */
  uint8_t com_status;		/* Bit 0: CD/A0 Line Status, Bit 1: CS Line Status, Bit 2: Reset Line Status,  Bit 3: 1 for power up */
  uint8_t com_cfg_cd;		/* Bit 0: Argument Level, Bit 1: Command Level */
  
  
};

#define ucg_GetWidth(ucg) ((ucg)->dimension.w)
#define ucg_GetHeight(ucg) ((ucg)->dimension.h)

#define UCG_MSG_DEV_POWER_UP	10
#define UCG_MSG_DEV_POWER_DOWN 11
#define UCG_MSG_SET_CLIP_BOX 12
#define UCG_MSG_GET_DIMENSION 15

#define UCG_MSG_DRAW_PIXEL 20
#define UCG_MSG_DRAW_L90FX 21
#define UCG_MSG_DRAW_L90TC 22	
#define UCG_MSG_DRAW_L90SE 23
#define UCG_MSG_DRAW_L90RL 24

#define UCG_COM_STATUS_MASK_POWER 8
#define UCG_COM_STATUS_MASK_RESET 4
#define UCG_COM_STATUS_MASK_CS 2
#define UCG_COM_STATUS_MASK_CD 1

/*
  arg:	clock speed in ns (0..4095)
  return:	0 for error
  note: 
    - power up is the first command, which is sent
*/
#define UCG_COM_MSG_POWER_UP 10

/*
  note: power down my be followed only by power up command
*/
#define UCG_COM_MSG_POWER_DOWN 11

/*
  arg:	delay in microseconds  (0..4095) 
*/
#define UCG_COM_MSG_DELAY 12

/*
  ucg->com_status	contains previous status of reset line
  arg:			new logic level for reset line
*/
#define UCG_COM_MSG_CHANGE_RESET_LINE 13
/*
  ucg->com_status	contains previous status of cs line
  arg:	new logic level for cs line
*/
#define UCG_COM_MSG_CHANGE_CS_LINE 14

/*
  ucg->com_status	contains previous status of cd line
  arg:	new logic level for cd line
*/
#define UCG_COM_MSG_CHANGE_CD_LINE 15

/*
  ucg->com_status	current status of Reset, CS and CD line (ucg->com_status)
  arg:			byte for display
*/
#define UCG_COM_MSG_SEND_BYTE 16

/*
  ucg->com_status	current status of Reset, CS and CD line (ucg->com_status)
  arg:			how often to repeat the 2/3 byte sequence 	
  data:			pointer to two or three bytes
*/
#define UCG_COM_MSG_REPEAT_1_BYTE 17
#define UCG_COM_MSG_REPEAT_2_BYTES 18
#define UCG_COM_MSG_REPEAT_3_BYTES 19

/*
  ucg->com_status	current status of Reset, CS and CD line (ucg->com_status)
  arg:			length of string 	
  data:			string
*/
#define UCG_COM_MSG_SEND_STR 20



/*================================================*/
/* ucg_dev_msg_api.c */
void ucg_PowerDown(ucg_t *ucg);
ucg_int_t ucg_PowerUp(ucg_t *ucg);
void ucg_SetClipBox(ucg_t *ucg, ucg_box_t *clip_box);
void ucg_SetClipRange(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h);
void ucg_SetMaxClipRange(ucg_t *ucg);
void ucg_GetDimension(ucg_t *ucg);
void ucg_DrawPixelWithArg(ucg_t *ucg);
void ucg_DrawL90FXWithArg(ucg_t *ucg);
void ucg_DrawL90TCWithArg(ucg_t *ucg);
void ucg_DrawL90SEWithArg(ucg_t *ucg);
void ucg_DrawL90RLWithArg(ucg_t *ucg);

/*================================================*/
/* ucg_init.c */
ucg_int_t ucg_Init(ucg_t *ucg, ucg_dev_fnptr device_cb, ucg_dev_fnptr ext_cb, ucg_com_fnptr com_cb);


/*================================================*/
/* ucg_dev_sdl.c */
ucg_int_t ucg_sdl_dev_cb(ucg_t *ucg, ucg_int_t msg, void *data);

/*================================================*/
/* ucg_pixel.c */
void ucg_SetColor(ucg_t *ucg, uint8_t idx, uint8_t r, uint8_t g, uint8_t b);
void ucg_DrawPixel(ucg_t *ucg, ucg_int_t x, ucg_int_t y);

/*================================================*/
/* ucg_line.c */
void ucg_DrawHLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len);
void ucg_DrawVLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len);
void ucg_DrawHRLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len);
/* the following procedure is only available with the extended callback */
void ucg_DrawGradientLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len, ucg_int_t dir);


/*================================================*/
/* ucg_box.c */
void ucg_DrawBox(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h);
void ucg_DrawGradientBox(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h);


/*================================================*/
/* ucg_circle.c */
#define UCG_DRAW_UPPER_RIGHT 0x01
#define UCG_DRAW_UPPER_LEFT  0x02
#define UCG_DRAW_LOWER_LEFT 0x04
#define UCG_DRAW_LOWER_RIGHT  0x08
#define UCG_DRAW_ALL (U8G_DRAW_UPPER_RIGHT|U8G_DRAW_UPPER_LEFT|U8G_DRAW_LOWER_RIGHT|U8G_DRAW_LOWER_LEFT)
void ucg_DrawDisc(ucg_t *ucg, ucg_int_t x0, ucg_int_t y0, ucg_int_t rad, uint8_t option);
void ucg_DrawCircle(ucg_t *ucg, ucg_int_t x0, ucg_int_t y0, ucg_int_t rad, uint8_t option);

/*================================================*/
/* ucg_bitmap.c */
void ucg_DrawBitmapLine(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t dir, ucg_int_t len, const unsigned char *bitmap);
void ucg_DrawRLBitmap(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t dir, const unsigned char *rl_bitmap);


/*================================================*/
/* ucg_rotate.c */
void ucg_UndoRotate(ucg_t *ucg);
void ucg_SetRotate90(ucg_t *ucg);
void ucg_SetRotate180(ucg_t *ucg);
void ucg_SetRotate270(ucg_t *ucg);

/*================================================*/
/* ucg_font.c */

/* Information on a specific given font */
uint8_t ucg_font_GetFontStartEncoding(const void *font);
uint8_t ucg_font_GetFontEndEncoding(const void *font);

uint8_t ucg_font_GetCapitalAHeight(const void *font);

int8_t ucg_font_GetFontAscent(const void *font);
int8_t ucg_font_GetFontDescent(const void *font);

int8_t ucg_font_GetFontXAscent(const void *font);
int8_t ucg_font_GetFontXDescent(const void *font);

size_t ucg_font_GetSize(const void *font);

/* Information on the current font */

uint8_t ucg_GetFontBBXWidth(ucg_t *ucg);
uint8_t ucg_GetFontBBXHeight(ucg_t *ucg);
uint8_t ucg_GetFontCapitalAHeight(ucg_t *ucg) UCG_NOINLINE; 
uint8_t ucg_IsGlyph(ucg_t *ucg, uint8_t requested_encoding);
int8_t ucg_GetGlyphWidth(ucg_t *ucg, uint8_t requested_encoding);

#define ucg_GetFontAscent(ucg)	((ucg)->font_ref_ascent)
#define ucg_GetFontDescent(ucg)	((ucg)->font_ref_descent)

/* Drawing procedures */

ucg_int_t ucg_DrawGlyph(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, uint8_t encoding);
ucg_int_t ucg_DrawString(ucg_t *ucg, ucg_int_t x, ucg_int_t y, uint8_t dir, const char *str);

/* Mode selection/Font assignment */

void ucg_SetFontRefHeightText(ucg_t *ucg);
void ucg_SetFontRefHeightExtendedText(ucg_t *ucg);
void ucg_SetFontRefHeightAll(ucg_t *ucg);

void ucg_SetFontPosBaseline(ucg_t *ucg) UCG_NOINLINE;
void ucg_SetFontPosBottom(ucg_t *ucg);
void ucg_SetFontPosTop(ucg_t *ucg);
void ucg_SetFontPosCenter(ucg_t *ucg);

void ucg_SetFont(ucg_t *ucg, const ucg_fntpgm_uint8_t  *font);


/*================================================*/
/* LOW LEVEL PROCEDRUES, ONLY CALLED BY DEV CB */

/*================================================*/
/* ucg_clip.c */
ucg_int_t ucg_clip_is_pixel_visible(ucg_t *ucg);
ucg_int_t ucg_clip_l90fx(ucg_t *ucg);
ucg_int_t ucg_clip_l90tc(ucg_t *ucg);
ucg_int_t ucg_clip_l90se(ucg_t *ucg);


/*================================================*/
/* ucg_ccs.c */
void ucg_ccs_init(ucg_ccs_t *ccs, uint8_t start, uint8_t end, ucg_int_t steps);
void ucg_ccs_step(ucg_ccs_t *ccs);
void ucg_ccs_seek(ucg_ccs_t *ccs, ucg_int_t pos);


/*================================================*/
/* ucg_dev_default_cb.c */
ucg_int_t ucg_dev_default_cb(ucg_t *ucg, ucg_int_t msg, void *data);
ucg_int_t ucg_handle_l90fx(ucg_t *ucg, ucg_dev_fnptr dev_cb);
ucg_int_t ucg_handle_l90tc(ucg_t *ucg, ucg_dev_fnptr dev_cb);
ucg_int_t ucg_handle_l90se(ucg_t *ucg, ucg_dev_fnptr dev_cb);
void ucg_handle_l90rl(ucg_t *ucg, ucg_dev_fnptr dev_cb);


/*================================================*/
/* ucg_com_msg_api.c */

/* send command bytes and optional arguments */
#define UCG_C10(c0)				0x010, (c0)
#define UCG_C20(c0,c1)				0x020, (c0),(c1)
#define UCG_C11(c0,a0)				0x011, (c0),(a0)
#define UCG_C21(c0,c1,a0)			0x021, (c0),(c1),(a0)
#define UCG_C12(c0,a0,a1)			0x012, (c0),(a0),(a1)
#define UCG_C22(c0,c1,a0,a1)		0x022, (c0),(c1),(a0),(a1)
#define UCG_C13(c0,a0,a1,a2)		0x013, (c0),(a0),(a1),(a2)
#define UCG_C23(c0,c1,a0,a1,a2)		0x023, (c0),(c1),(a0),(a1),(a2)
#define UCG_C14(c0,a0,a1,a2,a3)		0x014, (c0),(a0),(a1),(a2),(a3)
#define UCG_C24(c0,c1,a0,a1,a2,a3)	0x024, (c0),(c1),(a0),(a1),(a2),(a3)

/* send one or more argument bytes */
#define UCG_A1(d0)					0x061, (d0)
#define UCG_A2(d0,d1)					0x062, (d0),(d1)
#define UCG_A3(d0,d1,d2)				0x063, (d0),(d1),(d2)
#define UCG_A4(d0,d1,d2,d3)				0x064, (d0),(d1),(d2),(d3)
#define UCG_A5(d0,d1,d2,d3,d4)			0x065, (d0),(d1),(d2),(d3),(d4)
#define UCG_A6(d0,d1,d2,d3,d4,d5)		0x066, (d0),(d1),(d2),(d3),(d4),(d5)
#define UCG_A7(d0,d1,d2,d3,d4,d5,d6)		0x067, (d0),(d1),(d2),(d3),(d4),(d5),(d6)
#define UCG_A8(d0,d1,d2,d3,d4,d5,d6,d7)	0x068, (d0),(d1),(d2),(d3),(d4),(d5),(d6),(d7)

/* force data mode on CD line */
#define UCG_DATA()					0x070
/* send one or more data bytes */
#define UCG_D1(d0)				0x071, (d0)
#define UCG_D2(d0,d1)				0x072, (d0),(d1)
#define UCG_D3(d0,d1,d2)			0x073, (d0),(d1),(d2)
#define UCG_D4(d0,d1,d2,d3)			0x074, (d0),(d1),(d2),(d3)
#define UCG_D5(d0,d1,d2,d3,d4)		0x075, (d0),(d1),(d2),(d3),(d4)
#define UCG_D6(d0,d1,d2,d3,d4,d5)	0x076, (d0),(d1),(d2),(d3),(d4),(d5)

/* delay by specified value. t = [0..4095] */
#define UCG_DLY_MS(t)				0x080 | (((t)>>8)&15), (t)&255
#define UCG_DLY_US(t)				0x090 | (((t)>>8)&15), (t)&255

/* access procedures to ucg->arg.pixel.pos.x und ucg->arg.pixel.pos.y */
#define UCG_VARX(s,a,o)				0x0a0 | ((s)&15), (a), (o)
#define UCG_VARY(s,a,o)				0x0b0 | ((s)&15), (a), (o)

/* force specific level on RST und CS */
#define UCG_RST(level)				0x0f0 | ((level)&1)
#define UCG_CS(level)				0x0f4 | ((level)&1)

/* Configure CD line for command, arguments and data */
#define UCG_CFG_CD(c,a)			0x0fc | (((c)&1)<<1) | ((a)&1)

/* Termination byte */
#define UCG_END()					0x00

void ucg_com_PowerDown(ucg_t *ucg);
int16_t ucg_com_PowerUp(ucg_t *ucg, uint16_t serial_clk_speed, uint16_t parallel_clk_speed);
void ucg_com_SetLineStatus(ucg_t *ucg, uint8_t level, uint8_t mask, uint8_t msg) UCG_NOINLINE;
void ucg_com_SetResetLineStatus(ucg_t *ucg, uint8_t level);
void ucg_com_SetCSLineStatus(ucg_t *ucg, uint8_t level);
void ucg_com_SetCDLineStatus(ucg_t *ucg, uint8_t level);
void ucg_com_DelayMicroseconds(ucg_t *ucg, uint16_t delay) UCG_NOINLINE;
void ucg_com_DelayMilliseconds(ucg_t *ucg, uint16_t delay) UCG_NOINLINE;
void ucg_com_SendByte(ucg_t *ucg, uint8_t byte);
void ucg_com_SendRepeatByte(ucg_t *ucg, uint32_t cnt, uint8_t byte);
void ucg_com_SendRepeat2Bytes(ucg_t *ucg, uint32_t cnt, uint8_t *byte_ptr);
void ucg_com_SendRepeat3Bytes(ucg_t *ucg, uint32_t cnt, uint8_t *byte_ptr);
void ucg_com_SendString(ucg_t *ucg, uint32_t cnt, const uint8_t *byte_ptr);
void ucg_com_SendCmdSeq(ucg_t *ucg, const uint8_t *data);


/*================================================*/
/* ucg_dev_tga.c */
int tga_init(uint16_t w, uint16_t h);
void tga_save(const char *name);

ucg_int_t ucg_dev_tga(ucg_t *ucg, ucg_int_t msg, void *data);




/*================================================*/

extern const ucg_fntpgm_uint8_t ucg_font_04b_03b[] UCG_FONT_SECTION("ucg_font_04b_03b");
extern const ucg_fntpgm_uint8_t ucg_font_04b_03bn[] UCG_FONT_SECTION("ucg_font_04b_03bn");
extern const ucg_fntpgm_uint8_t ucg_font_04b_03br[] UCG_FONT_SECTION("ucg_font_04b_03br");
extern const ucg_fntpgm_uint8_t ucg_font_04b_03[] UCG_FONT_SECTION("ucg_font_04b_03");
extern const ucg_fntpgm_uint8_t ucg_font_04b_03n[] UCG_FONT_SECTION("ucg_font_04b_03n");
extern const ucg_fntpgm_uint8_t ucg_font_04b_03r[] UCG_FONT_SECTION("ucg_font_04b_03r");
extern const ucg_fntpgm_uint8_t ucg_font_04b_24[] UCG_FONT_SECTION("ucg_font_04b_24");
extern const ucg_fntpgm_uint8_t ucg_font_04b_24n[] UCG_FONT_SECTION("ucg_font_04b_24n");
extern const ucg_fntpgm_uint8_t ucg_font_04b_24r[] UCG_FONT_SECTION("ucg_font_04b_24r");
extern const ucg_fntpgm_uint8_t ucg_font_10x20_67_75[] UCG_FONT_SECTION("ucg_font_10x20_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_10x20_75r[] UCG_FONT_SECTION("ucg_font_10x20_75r");
extern const ucg_fntpgm_uint8_t ucg_font_10x20_78_79[] UCG_FONT_SECTION("ucg_font_10x20_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_10x20[] UCG_FONT_SECTION("ucg_font_10x20");
extern const ucg_fntpgm_uint8_t ucg_font_10x20r[] UCG_FONT_SECTION("ucg_font_10x20r");
extern const ucg_fntpgm_uint8_t ucg_font_4x6[] UCG_FONT_SECTION("ucg_font_4x6");
extern const ucg_fntpgm_uint8_t ucg_font_4x6r[] UCG_FONT_SECTION("ucg_font_4x6r");
extern const ucg_fntpgm_uint8_t ucg_font_5x7[] UCG_FONT_SECTION("ucg_font_5x7");
extern const ucg_fntpgm_uint8_t ucg_font_5x7r[] UCG_FONT_SECTION("ucg_font_5x7r");
extern const ucg_fntpgm_uint8_t ucg_font_5x8[] UCG_FONT_SECTION("ucg_font_5x8");
extern const ucg_fntpgm_uint8_t ucg_font_5x8r[] UCG_FONT_SECTION("ucg_font_5x8r");
extern const ucg_fntpgm_uint8_t ucg_font_6x10[] UCG_FONT_SECTION("ucg_font_6x10");
extern const ucg_fntpgm_uint8_t ucg_font_6x10r[] UCG_FONT_SECTION("ucg_font_6x10r");
extern const ucg_fntpgm_uint8_t ucg_font_6x12_67_75[] UCG_FONT_SECTION("ucg_font_6x12_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_6x12_75r[] UCG_FONT_SECTION("ucg_font_6x12_75r");
extern const ucg_fntpgm_uint8_t ucg_font_6x12_78_79[] UCG_FONT_SECTION("ucg_font_6x12_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_6x12[] UCG_FONT_SECTION("ucg_font_6x12");
extern const ucg_fntpgm_uint8_t ucg_font_6x12r[] UCG_FONT_SECTION("ucg_font_6x12r");
extern const ucg_fntpgm_uint8_t ucg_font_6x13_67_75[] UCG_FONT_SECTION("ucg_font_6x13_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_6x13_75r[] UCG_FONT_SECTION("ucg_font_6x13_75r");
extern const ucg_fntpgm_uint8_t ucg_font_6x13_78_79[] UCG_FONT_SECTION("ucg_font_6x13_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_6x13B[] UCG_FONT_SECTION("ucg_font_6x13B");
extern const ucg_fntpgm_uint8_t ucg_font_6x13Br[] UCG_FONT_SECTION("ucg_font_6x13Br");
extern const ucg_fntpgm_uint8_t ucg_font_6x13[] UCG_FONT_SECTION("ucg_font_6x13");
extern const ucg_fntpgm_uint8_t ucg_font_6x13O[] UCG_FONT_SECTION("ucg_font_6x13O");
extern const ucg_fntpgm_uint8_t ucg_font_6x13Or[] UCG_FONT_SECTION("ucg_font_6x13Or");
extern const ucg_fntpgm_uint8_t ucg_font_6x13r[] UCG_FONT_SECTION("ucg_font_6x13r");
extern const ucg_fntpgm_uint8_t ucg_font_7x13_67_75[] UCG_FONT_SECTION("ucg_font_7x13_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_7x13_75r[] UCG_FONT_SECTION("ucg_font_7x13_75r");
extern const ucg_fntpgm_uint8_t ucg_font_7x13B[] UCG_FONT_SECTION("ucg_font_7x13B");
extern const ucg_fntpgm_uint8_t ucg_font_7x13Br[] UCG_FONT_SECTION("ucg_font_7x13Br");
extern const ucg_fntpgm_uint8_t ucg_font_7x13[] UCG_FONT_SECTION("ucg_font_7x13");
extern const ucg_fntpgm_uint8_t ucg_font_7x13O[] UCG_FONT_SECTION("ucg_font_7x13O");
extern const ucg_fntpgm_uint8_t ucg_font_7x13Or[] UCG_FONT_SECTION("ucg_font_7x13Or");
extern const ucg_fntpgm_uint8_t ucg_font_7x13r[] UCG_FONT_SECTION("ucg_font_7x13r");
extern const ucg_fntpgm_uint8_t ucg_font_7x14B[] UCG_FONT_SECTION("ucg_font_7x14B");
extern const ucg_fntpgm_uint8_t ucg_font_7x14Br[] UCG_FONT_SECTION("ucg_font_7x14Br");
extern const ucg_fntpgm_uint8_t ucg_font_7x14[] UCG_FONT_SECTION("ucg_font_7x14");
extern const ucg_fntpgm_uint8_t ucg_font_7x14r[] UCG_FONT_SECTION("ucg_font_7x14r");
extern const ucg_fntpgm_uint8_t ucg_font_8x13_67_75[] UCG_FONT_SECTION("ucg_font_8x13_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_8x13_75r[] UCG_FONT_SECTION("ucg_font_8x13_75r");
extern const ucg_fntpgm_uint8_t ucg_font_8x13B[] UCG_FONT_SECTION("ucg_font_8x13B");
extern const ucg_fntpgm_uint8_t ucg_font_8x13Br[] UCG_FONT_SECTION("ucg_font_8x13Br");
extern const ucg_fntpgm_uint8_t ucg_font_8x13[] UCG_FONT_SECTION("ucg_font_8x13");
extern const ucg_fntpgm_uint8_t ucg_font_8x13O[] UCG_FONT_SECTION("ucg_font_8x13O");
extern const ucg_fntpgm_uint8_t ucg_font_8x13Or[] UCG_FONT_SECTION("ucg_font_8x13Or");
extern const ucg_fntpgm_uint8_t ucg_font_8x13r[] UCG_FONT_SECTION("ucg_font_8x13r");
extern const ucg_fntpgm_uint8_t ucg_font_9x15_67_75[] UCG_FONT_SECTION("ucg_font_9x15_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_9x15_75r[] UCG_FONT_SECTION("ucg_font_9x15_75r");
extern const ucg_fntpgm_uint8_t ucg_font_9x15_78_79[] UCG_FONT_SECTION("ucg_font_9x15_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_9x15B[] UCG_FONT_SECTION("ucg_font_9x15B");
extern const ucg_fntpgm_uint8_t ucg_font_9x15Br[] UCG_FONT_SECTION("ucg_font_9x15Br");
extern const ucg_fntpgm_uint8_t ucg_font_9x15[] UCG_FONT_SECTION("ucg_font_9x15");
extern const ucg_fntpgm_uint8_t ucg_font_9x15r[] UCG_FONT_SECTION("ucg_font_9x15r");
extern const ucg_fntpgm_uint8_t ucg_font_9x18_67_75[] UCG_FONT_SECTION("ucg_font_9x18_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_9x18_75r[] UCG_FONT_SECTION("ucg_font_9x18_75r");
extern const ucg_fntpgm_uint8_t ucg_font_9x18_78_79[] UCG_FONT_SECTION("ucg_font_9x18_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_9x18B[] UCG_FONT_SECTION("ucg_font_9x18B");
extern const ucg_fntpgm_uint8_t ucg_font_9x18Br[] UCG_FONT_SECTION("ucg_font_9x18Br");
extern const ucg_fntpgm_uint8_t ucg_font_9x18[] UCG_FONT_SECTION("ucg_font_9x18");
extern const ucg_fntpgm_uint8_t ucg_font_9x18r[] UCG_FONT_SECTION("ucg_font_9x18r");
extern const ucg_fntpgm_uint8_t ucg_font_baby[] UCG_FONT_SECTION("ucg_font_baby");
extern const ucg_fntpgm_uint8_t ucg_font_babyn[] UCG_FONT_SECTION("ucg_font_babyn");
extern const ucg_fntpgm_uint8_t ucg_font_babyr[] UCG_FONT_SECTION("ucg_font_babyr");
extern const ucg_fntpgm_uint8_t ucg_font_blipfest_07[] UCG_FONT_SECTION("ucg_font_blipfest_07");
extern const ucg_fntpgm_uint8_t ucg_font_blipfest_07n[] UCG_FONT_SECTION("ucg_font_blipfest_07n");
extern const ucg_fntpgm_uint8_t ucg_font_blipfest_07r[] UCG_FONT_SECTION("ucg_font_blipfest_07r");
extern const ucg_fntpgm_uint8_t ucg_font_chikita[] UCG_FONT_SECTION("ucg_font_chikita");
extern const ucg_fntpgm_uint8_t ucg_font_chikitan[] UCG_FONT_SECTION("ucg_font_chikitan");
extern const ucg_fntpgm_uint8_t ucg_font_chikitar[] UCG_FONT_SECTION("ucg_font_chikitar");
extern const ucg_fntpgm_uint8_t ucg_font_courB08[] UCG_FONT_SECTION("ucg_font_courB08");
extern const ucg_fntpgm_uint8_t ucg_font_courB08r[] UCG_FONT_SECTION("ucg_font_courB08r");
extern const ucg_fntpgm_uint8_t ucg_font_courB10[] UCG_FONT_SECTION("ucg_font_courB10");
extern const ucg_fntpgm_uint8_t ucg_font_courB10r[] UCG_FONT_SECTION("ucg_font_courB10r");
extern const ucg_fntpgm_uint8_t ucg_font_courB12[] UCG_FONT_SECTION("ucg_font_courB12");
extern const ucg_fntpgm_uint8_t ucg_font_courB12r[] UCG_FONT_SECTION("ucg_font_courB12r");
extern const ucg_fntpgm_uint8_t ucg_font_courB14[] UCG_FONT_SECTION("ucg_font_courB14");
extern const ucg_fntpgm_uint8_t ucg_font_courB14r[] UCG_FONT_SECTION("ucg_font_courB14r");
extern const ucg_fntpgm_uint8_t ucg_font_courB18[] UCG_FONT_SECTION("ucg_font_courB18");
extern const ucg_fntpgm_uint8_t ucg_font_courB18r[] UCG_FONT_SECTION("ucg_font_courB18r");
extern const ucg_fntpgm_uint8_t ucg_font_courB24[] UCG_FONT_SECTION("ucg_font_courB24");
extern const ucg_fntpgm_uint8_t ucg_font_courB24r[] UCG_FONT_SECTION("ucg_font_courB24r");
extern const ucg_fntpgm_uint8_t ucg_font_courB24n[] UCG_FONT_SECTION("ucg_font_courB24n");
extern const ucg_fntpgm_uint8_t ucg_font_courR08[] UCG_FONT_SECTION("ucg_font_courR08");
extern const ucg_fntpgm_uint8_t ucg_font_courR08r[] UCG_FONT_SECTION("ucg_font_courR08r");
extern const ucg_fntpgm_uint8_t ucg_font_courR10[] UCG_FONT_SECTION("ucg_font_courR10");
extern const ucg_fntpgm_uint8_t ucg_font_courR10r[] UCG_FONT_SECTION("ucg_font_courR10r");
extern const ucg_fntpgm_uint8_t ucg_font_courR12[] UCG_FONT_SECTION("ucg_font_courR12");
extern const ucg_fntpgm_uint8_t ucg_font_courR12r[] UCG_FONT_SECTION("ucg_font_courR12r");
extern const ucg_fntpgm_uint8_t ucg_font_courR14[] UCG_FONT_SECTION("ucg_font_courR14");
extern const ucg_fntpgm_uint8_t ucg_font_courR14r[] UCG_FONT_SECTION("ucg_font_courR14r");
extern const ucg_fntpgm_uint8_t ucg_font_courR18[] UCG_FONT_SECTION("ucg_font_courR18");
extern const ucg_fntpgm_uint8_t ucg_font_courR18r[] UCG_FONT_SECTION("ucg_font_courR18r");
extern const ucg_fntpgm_uint8_t ucg_font_courR24[] UCG_FONT_SECTION("ucg_font_courR24");
extern const ucg_fntpgm_uint8_t ucg_font_courR24n[] UCG_FONT_SECTION("ucg_font_courR24n");
extern const ucg_fntpgm_uint8_t ucg_font_courR24r[] UCG_FONT_SECTION("ucg_font_courR24r");
extern const ucg_fntpgm_uint8_t ucg_font_cu12_67_75[] UCG_FONT_SECTION("ucg_font_cu12_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_cu12_75r[] UCG_FONT_SECTION("ucg_font_cu12_75r");
extern const ucg_fntpgm_uint8_t ucg_font_cu12[] UCG_FONT_SECTION("ucg_font_cu12");
extern const ucg_fntpgm_uint8_t ucg_font_cursor[] UCG_FONT_SECTION("ucg_font_cursor");
extern const ucg_fntpgm_uint8_t ucg_font_cursorr[] UCG_FONT_SECTION("ucg_font_cursorr");
extern const ucg_fntpgm_uint8_t ucg_font_fixed_v0[] UCG_FONT_SECTION("ucg_font_fixed_v0");
extern const ucg_fntpgm_uint8_t ucg_font_fixed_v0n[] UCG_FONT_SECTION("ucg_font_fixed_v0n");
extern const ucg_fntpgm_uint8_t ucg_font_fixed_v0r[] UCG_FONT_SECTION("ucg_font_fixed_v0r");
extern const ucg_fntpgm_uint8_t ucg_font_freedoomr10r[] UCG_FONT_SECTION("ucg_font_freedoomr10r");
extern const ucg_fntpgm_uint8_t ucg_font_freedoomr25n[] UCG_FONT_SECTION("ucg_font_freedoomr25n");
extern const ucg_fntpgm_uint8_t ucg_font_helvB08[] UCG_FONT_SECTION("ucg_font_helvB08");
extern const ucg_fntpgm_uint8_t ucg_font_helvB08r[] UCG_FONT_SECTION("ucg_font_helvB08r");
extern const ucg_fntpgm_uint8_t ucg_font_helvB10[] UCG_FONT_SECTION("ucg_font_helvB10");
extern const ucg_fntpgm_uint8_t ucg_font_helvB10r[] UCG_FONT_SECTION("ucg_font_helvB10r");
extern const ucg_fntpgm_uint8_t ucg_font_helvB12[] UCG_FONT_SECTION("ucg_font_helvB12");
extern const ucg_fntpgm_uint8_t ucg_font_helvB12r[] UCG_FONT_SECTION("ucg_font_helvB12r");
extern const ucg_fntpgm_uint8_t ucg_font_helvB14[] UCG_FONT_SECTION("ucg_font_helvB14");
extern const ucg_fntpgm_uint8_t ucg_font_helvB14r[] UCG_FONT_SECTION("ucg_font_helvB14r");
extern const ucg_fntpgm_uint8_t ucg_font_helvB18[] UCG_FONT_SECTION("ucg_font_helvB18");
extern const ucg_fntpgm_uint8_t ucg_font_helvB18r[] UCG_FONT_SECTION("ucg_font_helvB18r");
extern const ucg_fntpgm_uint8_t ucg_font_helvB24[] UCG_FONT_SECTION("ucg_font_helvB24");
extern const ucg_fntpgm_uint8_t ucg_font_helvB24n[] UCG_FONT_SECTION("ucg_font_helvB24n");
extern const ucg_fntpgm_uint8_t ucg_font_helvB24r[] UCG_FONT_SECTION("ucg_font_helvB24r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR08[] UCG_FONT_SECTION("ucg_font_helvR08");
extern const ucg_fntpgm_uint8_t ucg_font_helvR08r[] UCG_FONT_SECTION("ucg_font_helvR08r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR10[] UCG_FONT_SECTION("ucg_font_helvR10");
extern const ucg_fntpgm_uint8_t ucg_font_helvR10r[] UCG_FONT_SECTION("ucg_font_helvR10r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR12[] UCG_FONT_SECTION("ucg_font_helvR12");
extern const ucg_fntpgm_uint8_t ucg_font_helvR12r[] UCG_FONT_SECTION("ucg_font_helvR12r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR14[] UCG_FONT_SECTION("ucg_font_helvR14");
extern const ucg_fntpgm_uint8_t ucg_font_helvR14r[] UCG_FONT_SECTION("ucg_font_helvR14r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR18[] UCG_FONT_SECTION("ucg_font_helvR18");
extern const ucg_fntpgm_uint8_t ucg_font_helvR18r[] UCG_FONT_SECTION("ucg_font_helvR18r");
extern const ucg_fntpgm_uint8_t ucg_font_helvR24[] UCG_FONT_SECTION("ucg_font_helvR24");
extern const ucg_fntpgm_uint8_t ucg_font_helvR24n[] UCG_FONT_SECTION("ucg_font_helvR24n");
extern const ucg_fntpgm_uint8_t ucg_font_helvR24r[] UCG_FONT_SECTION("ucg_font_helvR24r");
extern const ucg_fntpgm_uint8_t ucg_font_lucasfont_alternate[] UCG_FONT_SECTION("ucg_font_lucasfont_alternate");
extern const ucg_fntpgm_uint8_t ucg_font_lucasfont_alternaten[] UCG_FONT_SECTION("ucg_font_lucasfont_alternaten");
extern const ucg_fntpgm_uint8_t ucg_font_lucasfont_alternater[] UCG_FONT_SECTION("ucg_font_lucasfont_alternater");
extern const ucg_fntpgm_uint8_t ucg_font_m2icon_5[] UCG_FONT_SECTION("ucg_font_m2icon_5");
extern const ucg_fntpgm_uint8_t ucg_font_m2icon_7[] UCG_FONT_SECTION("ucg_font_m2icon_7");
extern const ucg_fntpgm_uint8_t ucg_font_m2icon_9[] UCG_FONT_SECTION("ucg_font_m2icon_9");
extern const ucg_fntpgm_uint8_t ucg_font_micro[] UCG_FONT_SECTION("ucg_font_micro");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB08[] UCG_FONT_SECTION("ucg_font_ncenB08");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB08r[] UCG_FONT_SECTION("ucg_font_ncenB08r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB10[] UCG_FONT_SECTION("ucg_font_ncenB10");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB10r[] UCG_FONT_SECTION("ucg_font_ncenB10r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB12[] UCG_FONT_SECTION("ucg_font_ncenB12");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB12r[] UCG_FONT_SECTION("ucg_font_ncenB12r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB14[] UCG_FONT_SECTION("ucg_font_ncenB14");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB14r[] UCG_FONT_SECTION("ucg_font_ncenB14r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB18[] UCG_FONT_SECTION("ucg_font_ncenB18");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB18r[] UCG_FONT_SECTION("ucg_font_ncenB18r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB24[] UCG_FONT_SECTION("ucg_font_ncenB24");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB24n[] UCG_FONT_SECTION("ucg_font_ncenB24n");
extern const ucg_fntpgm_uint8_t ucg_font_ncenB24r[] UCG_FONT_SECTION("ucg_font_ncenB24r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR08[] UCG_FONT_SECTION("ucg_font_ncenR08");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR08r[] UCG_FONT_SECTION("ucg_font_ncenR08r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR10[] UCG_FONT_SECTION("ucg_font_ncenR10");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR10r[] UCG_FONT_SECTION("ucg_font_ncenR10r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR12[] UCG_FONT_SECTION("ucg_font_ncenR12");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR12r[] UCG_FONT_SECTION("ucg_font_ncenR12r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR14[] UCG_FONT_SECTION("ucg_font_ncenR14");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR14r[] UCG_FONT_SECTION("ucg_font_ncenR14r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR18[] UCG_FONT_SECTION("ucg_font_ncenR18");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR18r[] UCG_FONT_SECTION("ucg_font_ncenR18r");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR24[] UCG_FONT_SECTION("ucg_font_ncenR24");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR24n[] UCG_FONT_SECTION("ucg_font_ncenR24n");
extern const ucg_fntpgm_uint8_t ucg_font_ncenR24r[] UCG_FONT_SECTION("ucg_font_ncenR24r");
extern const ucg_fntpgm_uint8_t ucg_font_orgv01[] UCG_FONT_SECTION("ucg_font_orgv01");
extern const ucg_fntpgm_uint8_t ucg_font_orgv01n[] UCG_FONT_SECTION("ucg_font_orgv01n");
extern const ucg_fntpgm_uint8_t ucg_font_orgv01r[] UCG_FONT_SECTION("ucg_font_orgv01r");
extern const ucg_fntpgm_uint8_t ucg_font_p01type[] UCG_FONT_SECTION("ucg_font_p01type");
extern const ucg_fntpgm_uint8_t ucg_font_p01typen[] UCG_FONT_SECTION("ucg_font_p01typen");
extern const ucg_fntpgm_uint8_t ucg_font_p01typer[] UCG_FONT_SECTION("ucg_font_p01typer");
extern const ucg_fntpgm_uint8_t ucg_font_pixelle_micro[] UCG_FONT_SECTION("ucg_font_pixelle_micro");
extern const ucg_fntpgm_uint8_t ucg_font_pixelle_micron[] UCG_FONT_SECTION("ucg_font_pixelle_micron");
extern const ucg_fntpgm_uint8_t ucg_font_pixelle_micror[] UCG_FONT_SECTION("ucg_font_pixelle_micror");
extern const ucg_fntpgm_uint8_t ucg_font_robot_de_niro[] UCG_FONT_SECTION("ucg_font_robot_de_niro");
extern const ucg_fntpgm_uint8_t ucg_font_robot_de_niron[] UCG_FONT_SECTION("ucg_font_robot_de_niron");
extern const ucg_fntpgm_uint8_t ucg_font_robot_de_niror[] UCG_FONT_SECTION("ucg_font_robot_de_niror");
extern const ucg_fntpgm_uint8_t ucg_font_symb08[] UCG_FONT_SECTION("ucg_font_symb08");
extern const ucg_fntpgm_uint8_t ucg_font_symb08r[] UCG_FONT_SECTION("ucg_font_symb08r");
extern const ucg_fntpgm_uint8_t ucg_font_symb10[] UCG_FONT_SECTION("ucg_font_symb10");
extern const ucg_fntpgm_uint8_t ucg_font_symb10r[] UCG_FONT_SECTION("ucg_font_symb10r");
extern const ucg_fntpgm_uint8_t ucg_font_symb12[] UCG_FONT_SECTION("ucg_font_symb12");
extern const ucg_fntpgm_uint8_t ucg_font_symb12r[] UCG_FONT_SECTION("ucg_font_symb12r");
extern const ucg_fntpgm_uint8_t ucg_font_symb14[] UCG_FONT_SECTION("ucg_font_symb14");
extern const ucg_fntpgm_uint8_t ucg_font_symb14r[] UCG_FONT_SECTION("ucg_font_symb14r");
extern const ucg_fntpgm_uint8_t ucg_font_symb18[] UCG_FONT_SECTION("ucg_font_symb18");
extern const ucg_fntpgm_uint8_t ucg_font_symb18r[] UCG_FONT_SECTION("ucg_font_symb18r");
extern const ucg_fntpgm_uint8_t ucg_font_symb24[] UCG_FONT_SECTION("ucg_font_symb24");
extern const ucg_fntpgm_uint8_t ucg_font_symb24r[] UCG_FONT_SECTION("ucg_font_symb24r");
extern const ucg_fntpgm_uint8_t ucg_font_timB08[] UCG_FONT_SECTION("ucg_font_timB08");
extern const ucg_fntpgm_uint8_t ucg_font_timB08r[] UCG_FONT_SECTION("ucg_font_timB08r");
extern const ucg_fntpgm_uint8_t ucg_font_timB10[] UCG_FONT_SECTION("ucg_font_timB10");
extern const ucg_fntpgm_uint8_t ucg_font_timB10r[] UCG_FONT_SECTION("ucg_font_timB10r");
extern const ucg_fntpgm_uint8_t ucg_font_timB12[] UCG_FONT_SECTION("ucg_font_timB12");
extern const ucg_fntpgm_uint8_t ucg_font_timB12r[] UCG_FONT_SECTION("ucg_font_timB12r");
extern const ucg_fntpgm_uint8_t ucg_font_timB14[] UCG_FONT_SECTION("ucg_font_timB14");
extern const ucg_fntpgm_uint8_t ucg_font_timB14r[] UCG_FONT_SECTION("ucg_font_timB14r");
extern const ucg_fntpgm_uint8_t ucg_font_timB18[] UCG_FONT_SECTION("ucg_font_timB18");
extern const ucg_fntpgm_uint8_t ucg_font_timB18r[] UCG_FONT_SECTION("ucg_font_timB18r");
extern const ucg_fntpgm_uint8_t ucg_font_timB24[] UCG_FONT_SECTION("ucg_font_timB24");
extern const ucg_fntpgm_uint8_t ucg_font_timB24n[] UCG_FONT_SECTION("ucg_font_timB24n");
extern const ucg_fntpgm_uint8_t ucg_font_timB24r[] UCG_FONT_SECTION("ucg_font_timB24r");
extern const ucg_fntpgm_uint8_t ucg_font_timR08[] UCG_FONT_SECTION("ucg_font_timR08");
extern const ucg_fntpgm_uint8_t ucg_font_timR08r[] UCG_FONT_SECTION("ucg_font_timR08r");
extern const ucg_fntpgm_uint8_t ucg_font_timR10[] UCG_FONT_SECTION("ucg_font_timR10");
extern const ucg_fntpgm_uint8_t ucg_font_timR10r[] UCG_FONT_SECTION("ucg_font_timR10r");
extern const ucg_fntpgm_uint8_t ucg_font_timR12[] UCG_FONT_SECTION("ucg_font_timR12");
extern const ucg_fntpgm_uint8_t ucg_font_timR12r[] UCG_FONT_SECTION("ucg_font_timR12r");
extern const ucg_fntpgm_uint8_t ucg_font_timR14[] UCG_FONT_SECTION("ucg_font_timR14");
extern const ucg_fntpgm_uint8_t ucg_font_timR14r[] UCG_FONT_SECTION("ucg_font_timR14r");
extern const ucg_fntpgm_uint8_t ucg_font_timR18[] UCG_FONT_SECTION("ucg_font_timR18");
extern const ucg_fntpgm_uint8_t ucg_font_timR18r[] UCG_FONT_SECTION("ucg_font_timR18r");
extern const ucg_fntpgm_uint8_t ucg_font_timR24[] UCG_FONT_SECTION("ucg_font_timR24");
extern const ucg_fntpgm_uint8_t ucg_font_timR24n[] UCG_FONT_SECTION("ucg_font_timR24n");
extern const ucg_fntpgm_uint8_t ucg_font_timR24r[] UCG_FONT_SECTION("ucg_font_timR24r");
extern const ucg_fntpgm_uint8_t ucg_font_tpssb[] UCG_FONT_SECTION("ucg_font_tpssb");
extern const ucg_fntpgm_uint8_t ucg_font_tpssbn[] UCG_FONT_SECTION("ucg_font_tpssbn");
extern const ucg_fntpgm_uint8_t ucg_font_tpssbr[] UCG_FONT_SECTION("ucg_font_tpssbr");
extern const ucg_fntpgm_uint8_t ucg_font_tpss[] UCG_FONT_SECTION("ucg_font_tpss");
extern const ucg_fntpgm_uint8_t ucg_font_tpssn[] UCG_FONT_SECTION("ucg_font_tpssn");
extern const ucg_fntpgm_uint8_t ucg_font_tpssr[] UCG_FONT_SECTION("ucg_font_tpssr");
extern const ucg_fntpgm_uint8_t ucg_font_trixel_square[] UCG_FONT_SECTION("ucg_font_trixel_square");
extern const ucg_fntpgm_uint8_t ucg_font_trixel_squaren[] UCG_FONT_SECTION("ucg_font_trixel_squaren");
extern const ucg_fntpgm_uint8_t ucg_font_trixel_squarer[] UCG_FONT_SECTION("ucg_font_trixel_squarer");
extern const ucg_fntpgm_uint8_t ucg_font_u8glib_4[] UCG_FONT_SECTION("ucg_font_u8glib_4");
extern const ucg_fntpgm_uint8_t ucg_font_u8glib_4r[] UCG_FONT_SECTION("ucg_font_u8glib_4r");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_0_8[] UCG_FONT_SECTION("ucg_font_unifont_0_8");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_12_13[] UCG_FONT_SECTION("ucg_font_unifont_12_13");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_18_19[] UCG_FONT_SECTION("ucg_font_unifont_18_19");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_2_3[] UCG_FONT_SECTION("ucg_font_unifont_2_3");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_4_5[] UCG_FONT_SECTION("ucg_font_unifont_4_5");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_67_75[] UCG_FONT_SECTION("ucg_font_unifont_67_75");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_72_73[] UCG_FONT_SECTION("ucg_font_unifont_72_73");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_75r[] UCG_FONT_SECTION("ucg_font_unifont_75r");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_76[] UCG_FONT_SECTION("ucg_font_unifont_76");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_77[] UCG_FONT_SECTION("ucg_font_unifont_77");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_78_79[] UCG_FONT_SECTION("ucg_font_unifont_78_79");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_86[] UCG_FONT_SECTION("ucg_font_unifont_86");
extern const ucg_fntpgm_uint8_t ucg_font_unifont_8_9[] UCG_FONT_SECTION("ucg_font_unifont_8_9");
extern const ucg_fntpgm_uint8_t ucg_font_unifont[] UCG_FONT_SECTION("ucg_font_unifont");
extern const ucg_fntpgm_uint8_t ucg_font_unifontr[] UCG_FONT_SECTION("ucg_font_unifontr");
extern const ucg_fntpgm_uint8_t ucg_font_fub11[] UCG_FONT_SECTION("ucg_font_fub11");
extern const ucg_fntpgm_uint8_t ucg_font_fub11n[] UCG_FONT_SECTION("ucg_font_fub11n");
extern const ucg_fntpgm_uint8_t ucg_font_fub11r[] UCG_FONT_SECTION("ucg_font_fub11r");
extern const ucg_fntpgm_uint8_t ucg_font_fub14[] UCG_FONT_SECTION("ucg_font_fub14");
extern const ucg_fntpgm_uint8_t ucg_font_fub14n[] UCG_FONT_SECTION("ucg_font_fub14n");
extern const ucg_fntpgm_uint8_t ucg_font_fub14r[] UCG_FONT_SECTION("ucg_font_fub14r");
extern const ucg_fntpgm_uint8_t ucg_font_fub17[] UCG_FONT_SECTION("ucg_font_fub17");
extern const ucg_fntpgm_uint8_t ucg_font_fub17n[] UCG_FONT_SECTION("ucg_font_fub17n");
extern const ucg_fntpgm_uint8_t ucg_font_fub17r[] UCG_FONT_SECTION("ucg_font_fub17r");
extern const ucg_fntpgm_uint8_t ucg_font_fub20[] UCG_FONT_SECTION("ucg_font_fub20");
extern const ucg_fntpgm_uint8_t ucg_font_fub20n[] UCG_FONT_SECTION("ucg_font_fub20n");
extern const ucg_fntpgm_uint8_t ucg_font_fub20r[] UCG_FONT_SECTION("ucg_font_fub20r");
extern const ucg_fntpgm_uint8_t ucg_font_fub25[] UCG_FONT_SECTION("ucg_font_fub25");
extern const ucg_fntpgm_uint8_t ucg_font_fub25n[] UCG_FONT_SECTION("ucg_font_fub25n");
extern const ucg_fntpgm_uint8_t ucg_font_fub25r[] UCG_FONT_SECTION("ucg_font_fub25r");
extern const ucg_fntpgm_uint8_t ucg_font_fub30[] UCG_FONT_SECTION("ucg_font_fub30");
extern const ucg_fntpgm_uint8_t ucg_font_fub30n[] UCG_FONT_SECTION("ucg_font_fub30n");
extern const ucg_fntpgm_uint8_t ucg_font_fub30r[] UCG_FONT_SECTION("ucg_font_fub30r");
extern const ucg_fntpgm_uint8_t ucg_font_fub35n[] UCG_FONT_SECTION("ucg_font_fub35n");
extern const ucg_fntpgm_uint8_t ucg_font_fub42n[] UCG_FONT_SECTION("ucg_font_fub42n");
extern const ucg_fntpgm_uint8_t ucg_font_fub49n[] UCG_FONT_SECTION("ucg_font_fub49n");
extern const ucg_fntpgm_uint8_t ucg_font_fur11[] UCG_FONT_SECTION("ucg_font_fur11");
extern const ucg_fntpgm_uint8_t ucg_font_fur11n[] UCG_FONT_SECTION("ucg_font_fur11n");
extern const ucg_fntpgm_uint8_t ucg_font_fur11r[] UCG_FONT_SECTION("ucg_font_fur11r");
extern const ucg_fntpgm_uint8_t ucg_font_fur14[] UCG_FONT_SECTION("ucg_font_fur14");
extern const ucg_fntpgm_uint8_t ucg_font_fur14n[] UCG_FONT_SECTION("ucg_font_fur14n");
extern const ucg_fntpgm_uint8_t ucg_font_fur14r[] UCG_FONT_SECTION("ucg_font_fur14r");
extern const ucg_fntpgm_uint8_t ucg_font_fur17[] UCG_FONT_SECTION("ucg_font_fur17");
extern const ucg_fntpgm_uint8_t ucg_font_fur17n[] UCG_FONT_SECTION("ucg_font_fur17n");
extern const ucg_fntpgm_uint8_t ucg_font_fur17r[] UCG_FONT_SECTION("ucg_font_fur17r");
extern const ucg_fntpgm_uint8_t ucg_font_fur20[] UCG_FONT_SECTION("ucg_font_fur20");
extern const ucg_fntpgm_uint8_t ucg_font_fur20n[] UCG_FONT_SECTION("ucg_font_fur20n");
extern const ucg_fntpgm_uint8_t ucg_font_fur20r[] UCG_FONT_SECTION("ucg_font_fur20r");
extern const ucg_fntpgm_uint8_t ucg_font_fur25[] UCG_FONT_SECTION("ucg_font_fur25");
extern const ucg_fntpgm_uint8_t ucg_font_fur25n[] UCG_FONT_SECTION("ucg_font_fur25n");
extern const ucg_fntpgm_uint8_t ucg_font_fur25r[] UCG_FONT_SECTION("ucg_font_fur25r");
extern const ucg_fntpgm_uint8_t ucg_font_fur30[] UCG_FONT_SECTION("ucg_font_fur30");
extern const ucg_fntpgm_uint8_t ucg_font_fur30n[] UCG_FONT_SECTION("ucg_font_fur30n");
extern const ucg_fntpgm_uint8_t ucg_font_fur30r[] UCG_FONT_SECTION("ucg_font_fur30r");
extern const ucg_fntpgm_uint8_t ucg_font_fur35n[] UCG_FONT_SECTION("ucg_font_fur35n");
extern const ucg_fntpgm_uint8_t ucg_font_fur42n[] UCG_FONT_SECTION("ucg_font_fur42n");
extern const ucg_fntpgm_uint8_t ucg_font_fur49n[] UCG_FONT_SECTION("ucg_font_fur49n");
extern const ucg_fntpgm_uint8_t ucg_font_osb18[] UCG_FONT_SECTION("ucg_font_osb18");
extern const ucg_fntpgm_uint8_t ucg_font_osb18n[] UCG_FONT_SECTION("ucg_font_osb18n");
extern const ucg_fntpgm_uint8_t ucg_font_osb18r[] UCG_FONT_SECTION("ucg_font_osb18r");
extern const ucg_fntpgm_uint8_t ucg_font_osb21[] UCG_FONT_SECTION("ucg_font_osb21");
extern const ucg_fntpgm_uint8_t ucg_font_osb21n[] UCG_FONT_SECTION("ucg_font_osb21n");
extern const ucg_fntpgm_uint8_t ucg_font_osb21r[] UCG_FONT_SECTION("ucg_font_osb21r");
extern const ucg_fntpgm_uint8_t ucg_font_osb26[] UCG_FONT_SECTION("ucg_font_osb26");
extern const ucg_fntpgm_uint8_t ucg_font_osb26n[] UCG_FONT_SECTION("ucg_font_osb26n");
extern const ucg_fntpgm_uint8_t ucg_font_osb26r[] UCG_FONT_SECTION("ucg_font_osb26r");
extern const ucg_fntpgm_uint8_t ucg_font_osb29[] UCG_FONT_SECTION("ucg_font_osb29");
extern const ucg_fntpgm_uint8_t ucg_font_osb29n[] UCG_FONT_SECTION("ucg_font_osb29n");
extern const ucg_fntpgm_uint8_t ucg_font_osb29r[] UCG_FONT_SECTION("ucg_font_osb29r");
extern const ucg_fntpgm_uint8_t ucg_font_osb35[] UCG_FONT_SECTION("ucg_font_osb35");
extern const ucg_fntpgm_uint8_t ucg_font_osb35n[] UCG_FONT_SECTION("ucg_font_osb35n");
extern const ucg_fntpgm_uint8_t ucg_font_osb35r[] UCG_FONT_SECTION("ucg_font_osb35r");
extern const ucg_fntpgm_uint8_t ucg_font_osr18[] UCG_FONT_SECTION("ucg_font_osr18");
extern const ucg_fntpgm_uint8_t ucg_font_osr18n[] UCG_FONT_SECTION("ucg_font_osr18n");
extern const ucg_fntpgm_uint8_t ucg_font_osr18r[] UCG_FONT_SECTION("ucg_font_osr18r");
extern const ucg_fntpgm_uint8_t ucg_font_osr21[] UCG_FONT_SECTION("ucg_font_osr21");
extern const ucg_fntpgm_uint8_t ucg_font_osr21n[] UCG_FONT_SECTION("ucg_font_osr21n");
extern const ucg_fntpgm_uint8_t ucg_font_osr21r[] UCG_FONT_SECTION("ucg_font_osr21r");
extern const ucg_fntpgm_uint8_t ucg_font_osr26[] UCG_FONT_SECTION("ucg_font_osr26");
extern const ucg_fntpgm_uint8_t ucg_font_osr26n[] UCG_FONT_SECTION("ucg_font_osr26n");
extern const ucg_fntpgm_uint8_t ucg_font_osr26r[] UCG_FONT_SECTION("ucg_font_osr26r");
extern const ucg_fntpgm_uint8_t ucg_font_osr29[] UCG_FONT_SECTION("ucg_font_osr29");
extern const ucg_fntpgm_uint8_t ucg_font_osr29n[] UCG_FONT_SECTION("ucg_font_osr29n");
extern const ucg_fntpgm_uint8_t ucg_font_osr29r[] UCG_FONT_SECTION("ucg_font_osr29r");
extern const ucg_fntpgm_uint8_t ucg_font_osr35[] UCG_FONT_SECTION("ucg_font_osr35");
extern const ucg_fntpgm_uint8_t ucg_font_osr35n[] UCG_FONT_SECTION("ucg_font_osr35n");
extern const ucg_fntpgm_uint8_t ucg_font_osr35r[] UCG_FONT_SECTION("ucg_font_osr35r");


#ifdef __cplusplus
}
#endif


#endif /* _UCG_H */
