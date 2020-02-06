/* 
 * File:        main.c
 * Author:      HappyCodingRobot
 * Descripion:  com interace for ucglib and mpsse library
 *
 * Created on 16. April 2016, 23:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mpsse.h>
#include "ucg.h"
#include "ucglib_com_mpsse.h"

struct mpsse_context *SPIif;
int mpsse_retval = EXIT_FAILURE;


int16_t ucg_com_mpsse_spi(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data) {
    //char rdata;
    //uint8_t *dat = data;
    switch (msg) {
        case UCG_COM_MSG_POWER_UP:
            /* "data" is a pointer to ucg_com_info_t structure with the following information: */
            /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
            /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
            
            /* setup pins */
            PinHigh(SPIif, GPIOL0);
            PinHigh(SPIif, GPIOL1);
#ifdef USE_SW_CS
            PinHigh(SPIif, PIN_CS);
#endif

            /* setup SPI */
            if ((SPIif = MPSSE(SPI0, TEN_MHZ, MSB)) != NULL && SPIif->open) {
                printf("%s initialized at %iHz\n\r", GetDescription(SPIif), GetClock(SPIif));
                SetCSIdle(SPIif, HIGH);
                mpsse_retval = EXIT_SUCCESS;
            } else {
                printf("Failed to initialize MPSSE: %s\n\r", ErrorString(SPIif));
                exit(mpsse_retval);
            }
            break;
        case UCG_COM_MSG_POWER_DOWN:
            Close(SPIif);
            break;
        case UCG_COM_MSG_DELAY:
            delayMicroseconds(arg);
            break;
        case UCG_COM_MSG_CHANGE_RESET_LINE:
            if (arg == HIGH) {
                PinHigh(SPIif, PIN_RST);
            } else {
                PinLow(SPIif, PIN_RST);
            }
            break;
        case UCG_COM_MSG_CHANGE_CS_LINE:
#ifdef USE_SW_CS
            if (arg == HIGH) {
                PinHigh(SPIif, PIN_CS);
            } else {
                PinLow(SPIif, PIN_CS);
            }
            break;
#else
            if (arg == LOW) {
                Stop(SPIif);
            } else {
                Start(SPIif);
            }
#endif
            break;
        case UCG_COM_MSG_CHANGE_CD_LINE:
            if (arg == HIGH) {
                PinHigh(SPIif, PIN_CD);
            } else {
                PinLow(SPIif, PIN_CD);
            }
            break;
        case UCG_COM_MSG_SEND_BYTE:
            FastWrite(SPIif, (char*) &arg, 1);
            break;
        case UCG_COM_MSG_REPEAT_1_BYTE:
            while (arg > 0) {
                FastWrite(SPIif, (char*) data, 1);
                arg--;
            }
            break;
        case UCG_COM_MSG_REPEAT_2_BYTES:
            while (arg > 0) {
                FastWrite(SPIif, (char*) data, 2);
                arg--;
            }
            break;
        case UCG_COM_MSG_REPEAT_3_BYTES:
            while (arg > 0) {
                FastWrite(SPIif, (char*) data, 3);
                arg--;
            }
            break;
        case UCG_COM_MSG_SEND_STR:
            while (arg > 0) {
                //SPI.transfer(*data++);
                FastWrite(SPIif, (char*) data++, 1);
                arg--;
            }
            break;
        case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
            while (arg > 0) {
                if (*data != 0) {
                    /* set the data line directly, ignore the setting from UCG_CFG_CD */
                    if (*data == 1) {
                        //SPI.setPin((int) ucg->pin_list[UCG_PIN_CD], 0);
                        PinLow(SPIif, PIN_CD);
                    } else {
                        //SPI.setPin((int) ucg->pin_list[UCG_PIN_CD], 1);
                        PinHigh(SPIif, PIN_CD);
                    }
                }
                data++;
                //SPI.transfer(*data);
                FastWrite(SPIif, (char*) data, 1);
                data++;
                arg--;
            }
            break;
        default:
            printf("! Error: unknown com message %d\r\n", msg);
    }
    return 1;
}


void delayMicroseconds(int us_delay) {
    struct timespec req = {0}, rem = {0};
    time_t sec = (int) (us_delay / 1000000L);
    us_delay = us_delay - (sec * 1000000L);
    req.tv_sec = sec;
    req.tv_nsec = us_delay * 1000L;
    if (nanosleep(&req, &rem) < 0) {
        printf("# nanosleep() failed for delay_us()\n");
    }
}
