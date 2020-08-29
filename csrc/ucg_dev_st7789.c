#include "ucg.h"

#define ST7789_SWRESET 0x01
#define ST7789_SWRESET_DELAY_MS 5
#define ST7789_SWRESET_DELAY_SLEEP_OUT_MS 120
#define ST7789_SLPOUT 0x11
#define ST7789_SLPOUT_DELAY_MS 5
#define ST7789_SLPOUT_DELAY_SLEEP_IN_MS 120
#define ST7789_COLMOD 0x3A
#define ST7789_COLMOD_RGB_65K (1<<6|1<<4)  // 0x50
#define ST7789_COLMOD_RGB_262K (1<<6|1<<5)  // 0x60
#define ST7789_COLMOD_COLOR_12BIT (1<<1|1)  // 0x03
#define ST7789_COLMOD_COLOR_16BIT (1<<2|1)  // 0x05
#define ST7789_COLMOD_COLOR_16BIT_WRITE (ST7789_COLMOD_RGB_65K|ST7789_COLMOD_COLOR_16BIT)
#define ST7789_COLMOD_COLOR_18BIT (1<<2|1<<1)  // 0x06
#define ST7789_COLMOD_COLOR_READ (ST7789_COLMOD_RGB_262K|ST7789_COLMOD_COLOR_18BIT)
#define ST7789_COLMOD_COLOR_16M (1<<2|1<<1|1)  // 0x07
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_DISPON 0x29
#define ST7789_NORON 0x13
#define ST7789_RAMWR 0x2C
#define ST7789_MADCTL 0x36
#define ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM 0
#define ST7789_MADCTL_PAGE_ADDRESS_ORDER_BOTTOM_TO_TOP (1<<7)
#define ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT 0
#define ST7789_MADCTL_COLUMN_ADDRESS_ORDER_RIGHT_TO_LEFT (1<<6)
#define ST7789_MADCTL_PAGE_COLUMN_ORDER_NORMAL 0
#define ST7789_MADCTL_PAGE_COLUMN_ORDER_REVERSE (1<<5)
#define ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM 0
#define ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_BOTTOM_TO_TOP (1<<4)
#define ST7789_MADCTL_ORDER_RGB 0
#define ST7789_MADCTL_ORDER_BGR (1<<3)
#define ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_LEFT_TO_RIGHT 0
#define ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_RIGHT_TO_LEFT 1

#define ST7789_RESX_TRW_MS 10 // Reset pulse duration 
#define ST7789_RESX_TRT_MS 120 // Reset cancel

static const ucg_pgm_uint8_t ucg_st7789_16x240x240_init_seq[] = {
  UCG_CFG_CD(0,1),
  UCG_RST(1),
  UCG_CS(1),

  // Hardware reset
  UCG_RST(0),
  UCG_DLY_MS(ST7789_RESX_TRW_MS),
  UCG_RST(1),
  UCG_DLY_MS(ST7789_RESX_TRT_MS),

  // Software reset
  UCG_CS(0),
  UCG_C10(ST7789_SWRESET),
  UCG_CS(1),
  UCG_DLY_MS(ST7789_SWRESET_DELAY_MS),

  UCG_CS(0),

  // Out of sleep mode
  UCG_C10(ST7789_SLPOUT),
  UCG_DLY_MS(ST7789_SLPOUT_DELAY_SLEEP_IN_MS),

  // Set color mode
  UCG_C11(ST7789_COLMOD, ST7789_COLMOD_COLOR_16BIT_WRITE),

  // Memory Data Access Control
  UCG_C11(
    ST7789_MADCTL,
    ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM |
    ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT |
    ST7789_MADCTL_PAGE_COLUMN_ORDER_NORMAL |
    ST7789_MADCTL_LINE_ADDRESS_ORDER_LCD_REFRESH_TOP_TO_BOTTOM |
    ST7789_MADCTL_ORDER_RGB |
    ST7789_MADCTL_DISPLAY_DATA_LATCH_ORDER_LCD_REFRESH_LEFT_TO_RIGHT
  ),

  // Display inversion in practice works the opposite of what the datasheet
  // says: on is off and off is on.
  UCG_C10(ST7789_INVON),
  // Datasheet states NORON should be the default after sw reset, but unless
  // we explicitly set it, INVON will have no effect.
  UCG_C10(ST7789_NORON),

  // TODO clear RAM

  // Main screen turn on
  UCG_C10(ST7789_DISPON),

  UCG_CS(1),

  UCG_END(),
};

static void send_cmd(ucg_t *ucg, uint8_t cmd) {
  ucg_com_SetCDLineStatus(ucg, (ucg->com_cfg_cd>>1)&1);
  ucg_com_SendString(ucg, 1, &cmd);
}

static void send_cmd_data(ucg_t *ucg, uint8_t cmd, uint16_t count, uint8_t *data) {
  send_cmd(ucg, cmd);
  ucg_com_SetCDLineStatus(ucg, (ucg->com_cfg_cd)&1);
  ucg_com_SendString(ucg, count, data);
}

static void set_column_address(ucg_t *ucg, uint16_t x_start, uint16_t x_end) {
  uint8_t buff[4];

  buff[0] = (x_start&0xFF00)>>8;
  buff[1] = x_start&0xFF;
  buff[2] = (x_end&0xFF00)>>8;
  buff[3] = x_end&0xFF;

  send_cmd_data(ucg, ST7789_CASET, 4, buff);
}

static void set_row_address(ucg_t *ucg, uint16_t y_start, uint16_t y_end) {
  uint8_t buff[4];

  buff[0] = (y_start&0xFF00)>>8;
  buff[1] = y_start&0xFF;
  buff[2] = (y_end&0xFF00)>>8;
  buff[3] = y_end&0xFF;

  send_cmd_data(ucg, ST7789_RASET, 4, buff);
}

static void set_16bit_color(ucg_t *ucg, uint8_t buff[2]) {
  uint8_t r, g, b;

  // 16 bit: RRRRRGGG GGGBBBBB
  buff[0] = 0;
  buff[1] = 0;
  r = ucg->arg.pixel.rgb.color[0]>>(8-5);
  buff[0] |= r << 3;
  g = ucg->arg.pixel.rgb.color[1]>>(8-6);
  buff[0] |= g>>3;
  buff[1] |= g<<5;
  b = ucg->arg.pixel.rgb.color[2]>>(8-5);
  buff[1] |= b&0x1F;
}

static ucg_int_t handle_l90fx(ucg_t *ucg) {
  ucg_int_t dx=0, dy=0;
  uint8_t madctl_data=0;
  uint8_t buff[2];

  if ( ucg_clip_l90fx(ucg) == 0 )
    return 0;

  switch(ucg->arg.dir) {
    case 0:
      dx = 1;
      dy = 0;
      madctl_data = ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT;
      break;
    case 1:
      dx = 0;
      dy = 1;
      madctl_data = ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM;
      break;
    case 2:
      dx = -1;
      dy = 0;
      madctl_data = ST7789_MADCTL_COLUMN_ADDRESS_ORDER_RIGHT_TO_LEFT;
      break;
    case 3:
      dx = 0;
      dy = -1;
      madctl_data = ST7789_MADCTL_PAGE_ADDRESS_ORDER_BOTTOM_TO_TOP;
      break;
  }

  ucg_com_SetCSLineStatus(ucg, 0);

  send_cmd_data(ucg, ST7789_MADCTL, 1, &madctl_data);

  set_column_address(
    ucg,
    ucg->arg.pixel.pos.x, // x_start
    ucg->arg.pixel.pos.x + (ucg->arg.len * dx) // x_end
  );
  set_row_address(
    ucg,
    ucg->arg.pixel.pos.y, // y_start
    ucg->arg.pixel.pos.y + (ucg->arg.len * dy) // y_end
  );

  send_cmd(ucg, ST7789_RAMWR);
  ucg_com_SetCDLineStatus(ucg, (ucg->com_cfg_cd)&1);

  set_16bit_color(ucg, buff);

  for(ucg_int_t i = 0; i < ucg->arg.len; i++ ) {
    ucg_com_SendByte(ucg, buff[0]);
    ucg_com_SendByte(ucg, buff[1]);
    ucg->arg.pixel.pos.x+=dx;
    ucg->arg.pixel.pos.y+=dy;
  }

  ucg_com_SetCSLineStatus(ucg, 1);

  return 1;
}

static ucg_int_t handle_l90se(ucg_t *ucg) {
  ucg_int_t dx=0, dy=0;
  ucg_int_t k, j;
  uint8_t madctl_data=0;
  uint8_t buff[2];

  if ( ucg_clip_l90se(ucg) == 0 )
    return 0;
  
  for (int i = 0; i < 3; i++ )
    ucg_ccs_init(
      ucg->arg.ccs_line+i,
      ucg->arg.rgb[0].color[i],
      ucg->arg.rgb[1].color[i],
      ucg->arg.len
    );

  switch(ucg->arg.dir) {
    case 0:
      dx = 1;
      dy = 0;
      madctl_data = ST7789_MADCTL_COLUMN_ADDRESS_ORDER_LEFT_TO_RIGHT;
      break;
    case 1:
      dx = 0;
      dy = 1;
      madctl_data = ST7789_MADCTL_PAGE_ADDRESS_ORDER_TOP_TO_BOTTOM;
      break;
    case 2:
      dx = -1;
      dy = 0;
      madctl_data = ST7789_MADCTL_COLUMN_ADDRESS_ORDER_RIGHT_TO_LEFT;
      break;
    case 3:
      dx = 0;
      dy = -1;
      madctl_data = ST7789_MADCTL_PAGE_ADDRESS_ORDER_BOTTOM_TO_TOP;
      break;
  }

  ucg_com_SetCSLineStatus(ucg, 0);

  send_cmd_data(ucg, ST7789_MADCTL, 1, &madctl_data);

  set_column_address(
    ucg,
    ucg->arg.pixel.pos.x, // x_start
    ucg->arg.pixel.pos.x + (ucg->arg.len * dx) // x_end
  );
  set_row_address(
    ucg,
    ucg->arg.pixel.pos.y, // y_start
    ucg->arg.pixel.pos.y + (ucg->arg.len * dy) // y_end
  );

  send_cmd(ucg, ST7789_RAMWR);
  ucg_com_SetCDLineStatus(ucg, (ucg->com_cfg_cd)&1);

  for( k = 0; k < ucg->arg.len; k++ ) {
    ucg->arg.pixel.rgb.color[0] = ucg->arg.ccs_line[0].current;
    ucg->arg.pixel.rgb.color[1] = ucg->arg.ccs_line[1].current; 
    ucg->arg.pixel.rgb.color[2] = ucg->arg.ccs_line[2].current;

    set_16bit_color(ucg, buff);
    ucg_com_SendByte(ucg, buff[0]);
    ucg_com_SendByte(ucg, buff[1]);

    ucg->arg.pixel.pos.x+=dx;
    ucg->arg.pixel.pos.y+=dy;
    for ( j = 0; j < 3; j++ ) {
      ucg_ccs_step(ucg->arg.ccs_line+j);
    }
  }

  ucg_com_SetCSLineStatus(ucg, 1);

  return 1;
}

ucg_int_t ucg_dev_st7789_16x240x240(ucg_t *ucg, ucg_int_t msg, void *data) {
  switch(msg) {
    case UCG_MSG_DEV_POWER_UP:
      // Datasheet states 66ms for Serial clock cycle (Write) (~15MHz),
      // But it seems to work fine at 20MHz...
      ucg_com_PowerUp(ucg, 66, 0);
      ucg_com_SendCmdSeq(ucg, ucg_st7789_16x240x240_init_seq);
      return 1;
    case UCG_MSG_DEV_POWER_DOWN:
      return 1;
    case UCG_MSG_GET_DIMENSION:
      ((ucg_wh_t *)data)->w = 240;
      ((ucg_wh_t *)data)->h = 240;
      return 1;
    case UCG_MSG_DRAW_PIXEL:
      if ( ucg_clip_is_pixel_visible(ucg) !=0 )  {
        uint8_t buff[2];

        ucg_com_SetCSLineStatus(ucg, 0);

        set_column_address(ucg, ucg->arg.pixel.pos.x, ucg->arg.pixel.pos.x);
        set_row_address(ucg, ucg->arg.pixel.pos.y, ucg->arg.pixel.pos.y);

         // Write to RAM
        set_16bit_color(ucg, buff);
        send_cmd_data(ucg, ST7789_RAMWR, 2, buff);

        ucg_com_SetCSLineStatus(ucg, 1);
      }
      return 1;
    case UCG_MSG_DRAW_L90FX:
      return handle_l90fx(ucg);
    case UCG_MSG_DRAW_L90SE:
      return handle_l90se(ucg);
  }

  return ucg_dev_default_cb(ucg, msg, data);
}