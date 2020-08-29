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
#define ST7789_MADCTL 0x36
#define ST7789_CASET 0x2A
#define ST7789_RASET 0x2B
#define ST7789_INVOFF 0x20
#define ST7789_INVON 0x21
#define ST7789_DISPON 0x29
#define ST7789_NORON 0x13
#define ST7789_RAMWR 0x2C
#define ST7789_MADCTL 0x36

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

static void send_data(ucg_t *ucg, uint16_t count, uint8_t *data) {
  ucg_com_SetCDLineStatus(ucg, (ucg->com_cfg_cd)&1);
  ucg_com_SendString(ucg, count, data);
}

static void send_cmd_data(ucg_t *ucg, uint8_t cmd, uint16_t count, uint8_t *data) {
  send_cmd(ucg, cmd);
  send_data(ucg, count, data);
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
        uint8_t r, g, b;
        uint8_t buff[4];
        uint16_t addr;

        ucg_com_SetCSLineStatus(ucg, 0);

         // Column addr set
        addr = ucg->arg.pixel.pos.x;
        buff[0] = (addr&0xFF00)>>8; // X start high bits
        buff[1] = addr&0xFF; // X start low bits
        buff[2] = buff[0]; // X end high bits
        buff[3] = buff[1]; // X end low bits
        send_cmd_data(ucg, ST7789_CASET, 4, buff);

         // Row addr set
        addr = ucg->arg.pixel.pos.y;
        buff[0] = (addr&0xFF00)>>8; // X start high bits
        buff[1] = addr&0xFF; // X start low bits
        buff[2] = buff[0]; // X end high bits
        buff[3] = buff[1]; // X end low bits
        send_cmd_data(ucg, ST7789_RASET, 4, buff);

         // Write to RAM
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
        send_cmd_data(ucg, ST7789_RAMWR, 2, buff);

        ucg_com_SetCSLineStatus(ucg, 1);
      }
      return 1;
    case UCG_MSG_DRAW_L90FX:
      ucg_handle_l90fx(ucg, ucg_dev_st7789_16x240x240);
      return 1;
  }

  // UCG_MSG_DRAW_L90SE
  // UCG_MSG_SET_CLIP_BOX
  // UCG_MSG_SEND_BUFFER
  return ucg_dev_default_cb(ucg, msg, data);
}