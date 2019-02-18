#include <ucg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>

#define GPIO_PIN_RST 22
#define GPIO_PIN_CD 23
#define GPIO_PIN_CS 8

ucg_t ucg;

int16_t ucg_com_raspberry_pi_4wire_HW_SPI(
    ucg_t *ucg,
    int16_t msg,
    uint16_t arg,
    uint8_t *data
) {
  switch(msg) {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*  ((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*  ((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      /* "arg" is not used */

      /* This message is sent once at the uC startup and for power up. */
      /* setup i/o or do any other setup */

      if (!bcm2835_init()){
        printf("Failed bcm2835_init().\n");
        exit(1);
      }

      if (!bcm2835_spi_begin()){
        printf("Failed bcm2835_spi_begin().\n");
        exit(1);
      }

      bcm2835_gpio_fsel(GPIO_PIN_RST, BCM2835_GPIO_FSEL_OUTP);
      bcm2835_gpio_fsel(GPIO_PIN_CD, BCM2835_GPIO_FSEL_OUTP);
      bcm2835_gpio_fsel(GPIO_PIN_CS, BCM2835_GPIO_FSEL_OUTP);

      bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
      bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
      bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);
      bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
      bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      /* "data" and "arg" are not used*/
      /* This message is sent for a power down request */
      bcm2835_spi_end();
      bcm2835_close();
      break;
    case UCG_COM_MSG_DELAY:
      /* "data" is not used */
      /* "arg" contains the number of microseconds for the delay */
      /* By receiving this message, the following code should delay by */
      /* "arg" microseconds. One microsecond is 0.000001 second */
      bcm2835_delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      /* "data" is not used */
      /* "arg" = 1: set the reset output line to 1 */
      /* "arg" = 0: set the reset output line to 0 */
      bcm2835_gpio_write(GPIO_PIN_RST, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      /* "ucg->com_status"  bit 0 contains the old level for the CD line */
      /* "data" is not used */
      /* "arg" = 1: set the command/data (a0) output line to 1 */
      /* "arg" = 0: set the command/data (a0) output line to 0 */
      bcm2835_gpio_write(GPIO_PIN_CD, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      /* "ucg->com_status"  bit 1 contains the old level for the CS line */
      /* "data" is not used */
      /* "arg" = 1: set the chipselect output line to 1 */
      /* "arg" = 0: set the chipselect output line to 0 */
      bcm2835_gpio_write(GPIO_PIN_CS, arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      /* "data" is not used */
      /* "arg" contains one byte, which should be sent to the display */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
    bcm2835_spi_writenb((const char *)&arg, 1);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      /* "data[0]" contains one byte */
      /* repeat sending the byte in data[0] "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
      while( arg > 0 ) {
        bcm2835_spi_writenb((const char *)data, 1);
        arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* repeat sending the two bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
      while( arg > 0 ) {
        bcm2835_spi_writenb((const char *)data, 2);
        arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* "data[2]" contains third byte */
      /* repeat sending the three bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
      while( arg > 0 ) {
        bcm2835_spi_writenb((const char *)data, 3);
        arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      /* "data" is an array with "arg" bytes */
      /* send "arg" bytes to the display */
      bcm2835_spi_writenb((const char *)data, arg);
      break;
    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
      /* "data" is a pointer to two bytes, which contain the cd line */
      /* status and display data */
      /* "arg" contains the number of these two byte tuples which need to */
      /* be analysed and sent. Bellow is a example sequence */
      /* The content of bit 0 in u8g->com_status is undefined for this message */
      while(arg > 0) {
        if ( *data != 0 ) {
          /* set the data line directly, ignore the setting from UCG_CFG_CD */
          if ( *data == 1 ) {
            bcm2835_gpio_write(GPIO_PIN_CD, 0);
          } else {
            bcm2835_gpio_write(GPIO_PIN_CD, 1);
          }
        }
        data++;
        bcm2835_spi_writenb((const char *)data, 1);
        data++;
        arg--;
      }
      break;
  }
  return 1;
}

int main(void) {
  ucg_Init(
    &ucg,
    ucg_dev_st7735_18x128x160,
    ucg_ext_st7735_18,
    ucg_com_raspberry_pi_4wire_HW_SPI
  );

  ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT);

  while(1) {
    ucg_ClearScreen(&ucg);
    ucg_SetColor(&ucg, 0, 255, 0, 255);
    ucg_SetColor(&ucg, 1, 0, 255, 0);
    ucg_SetColor(&ucg, 2, 0, 0, 255);
    ucg_SetColor(&ucg, 3, 255, 255, 255);
    ucg_DrawGradientBox(&ucg, 0, 0, ucg_GetWidth(&ucg), ucg_GetHeight(&ucg));
  }
}