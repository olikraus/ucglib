#include <ucg.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define WIRING_PI_PIN_RST 3
#define WIRING_PI_PIN_CD 4
#define WIRING_PI_PIN_CS 10
#define WIRING_PI_SPI_CHANNEL 0

ucg_t ucg;
int spi_fd;

void spi_send(size_t len, unsigned char *data){
  if(len != (size_t)write(spi_fd, data, len)){
    printf("Failed to write to SPI device.\n");
    exit(1);
  }
}

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

      wiringPiSetup();

      pinMode(WIRING_PI_PIN_RST, OUTPUT) ;
      pinMode(WIRING_PI_PIN_CD, OUTPUT) ;
      pinMode(WIRING_PI_PIN_CS, OUTPUT) ;

      // Defaults to MSB-first and Mode 0
      spi_fd = wiringPiSPISetup(
        WIRING_PI_SPI_CHANNEL,
        1000000000UL/((ucg_com_info_t *)data)->serial_clk_speed
      );
      if(-1 == spi_fd){
        printf("Failed to open SPI file descriptor.\n");
        exit(1);
      }
      break;
    case UCG_COM_MSG_POWER_DOWN:
      /* "data" and "arg" are not used*/
      /* This message is sent for a power down request */
      close(spi_fd);
      break;
    case UCG_COM_MSG_DELAY:
      /* "data" is not used */
      /* "arg" contains the number of microseconds for the delay */
      /* By receiving this message, the following code should delay by */
      /* "arg" microseconds. One microsecond is 0.000001 second */
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      /* "data" is not used */
      /* "arg" = 1: set the reset output line to 1 */
      /* "arg" = 0: set the reset output line to 0 */
      digitalWrite(WIRING_PI_PIN_RST, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      /* "ucg->com_status"  bit 0 contains the old level for the CD line */
      /* "data" is not used */
      /* "arg" = 1: set the command/data (a0) output line to 1 */
      /* "arg" = 0: set the command/data (a0) output line to 0 */
      digitalWrite(WIRING_PI_PIN_CD, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      /* "ucg->com_status"  bit 1 contains the old level for the CS line */
      /* "data" is not used */
      /* "arg" = 1: set the chipselect output line to 1 */
      /* "arg" = 0: set the chipselect output line to 0 */
      digitalWrite(WIRING_PI_PIN_CS, arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      /* "data" is not used */
      /* "arg" contains one byte, which should be sent to the display */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
      spi_send(1, (unsigned char *)&arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      /* "data[0]" contains one byte */
      /* repeat sending the byte in data[0] "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
      while( arg > 0 ) {
        spi_send(1, (unsigned char *)data);
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
        spi_send(2, (unsigned char *)data);
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
        spi_send(3, (unsigned char *)data);
        arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      /* "data" is an array with "arg" bytes */
      /* send "arg" bytes to the display */
      spi_send(arg, (unsigned char *)data);
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
            digitalWrite(WIRING_PI_PIN_CD, 0);
          } else {
            digitalWrite(WIRING_PI_PIN_CD, 1);
          }
        }
        data++;
        spi_send(1, (unsigned char *)data);
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