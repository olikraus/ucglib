# Introduction #

This wiki page describes the Hardware Abstraction Layer (HAL) for Ucglib

# Details #

The hardware abtraction layer is implemented as callback function. The callback function receives several messages. The following code can be used as a template:

```
int16_t ucg_com_my_own_hal(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data)
{

  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      /* "arg" is not used */

      /* This message is sent once at the uC startup and for power up. */
      /* setup i/o or do any other setup */
      break;

    case UCG_COM_MSG_POWER_DOWN:
      /* "data" and "arg" are not used*/
      /* This message is sent for a power down request */

      break;
    case UCG_COM_MSG_DELAY:
      /* "data" is not used */
      /* "arg" contains the number of microseconds for the delay */
      /* By receiving this message, the following code should delay by */
      /* "arg" microseconds. One microsecond is 0.000001 second */

      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      /* "data" is not used */
      /* "arg" = 1: set the reset output line to 1 */
      /* "arg" = 0: set the reset output line to 0 */

      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      /* "ucg->com_status"  bit 0 contains the old level for the CD line */
      /* "data" is not used */
      /* "arg" = 1: set the command/data (a0) output line to 1 */
      /* "arg" = 0: set the command/data (a0) output line to 0 */

      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      /* "ucg->com_status"  bit 1 contains the old level for the CS line */
      /* "data" is not used */
      /* "arg" = 1: set the chipselect output line to 1 */
      /* "arg" = 0: set the chipselect output line to 0 */

      break;
    case UCG_COM_MSG_SEND_BYTE:
      /* "data" is not used */
      /* "arg" contains one byte, which should be sent to the display */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */

      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      /* "data[0]" contains one byte */
      /* repeat sending the byte in data[0] "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */

      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* repeat sending the two bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */

      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* "data[2]" contains third byte */
      /* repeat sending the three bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */

      break;
    case UCG_COM_MSG_SEND_STR:
      /* "data" is an array with "arg" bytes */
      /* send "arg" bytes to the display */

      break;
    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
      /* "data" is a pointer to two bytes, which contain the cd line */
      /* status and display data */
      /* "arg" contains the number of these two byte tuples which need to */
      /* be analysed and sent. Bellow is a example sequence */
      /* The content of bit 0 in u8g->com_status is undefined for this message */

      while(arg > 0)
      {
	if ( *data != 0 )
	{
	  if ( *data == 1 )
	  {
            /* set CD (=D/C=A0) line to low */
	  }
	  else
	  {
            /* set CD (=D/C=A0) line to high */
	  }
	}
	data++;
        /* send *data to the display */
	data++;
	arg--;
      }
      break;
  }
  return 1;
}

```

To setup the library, use the following init procedure:

```
ucg_int_t ucg_Init(ucg_t *ucg, ucg_dev_fnptr device_cb, ucg_dev_fnptr ext_cb, ucg_com_fnptr com_cb);
```

The above mentioned HAL-callback is the last argument for this procedure:
```
/* create memory area for ucglib variables */
ucg_t ucg;

/* setup ucglib, see ucg.h for a list of ucg_dev and ucg_ext objects */
ucg_Init(&ucg, ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, ucg_com_my_own_hal);

/* define prefered font rendering method (no text will be visibile, if this is missing */
ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT); 
```