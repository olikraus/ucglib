/* 
 * File:   ucglib_com_mpsse.h
 * Author: HappyCodingRobot
 *
 * Created on 17. April 2016, 15:07
 */

#ifndef UCGLIB_COM_MPSSE_H
#define	UCGLIB_COM_MPSSE_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define USE_SW_CS
#ifdef USE_SW_CS
#define PIN_CS  GPIOL2
#endif

#define PIN_RST GPIOL1
#define PIN_CD  GPIOL0

extern int mpsse_retval;


/* com interface for mpsse SPI */
int16_t ucg_com_mpsse_spi(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data);

/* com interface for mpsse I2C */
// TBD

/* helper functions */
void delayMicroseconds(int us_delay);


#ifdef	__cplusplus
}
#endif

#endif	/* UCGLIB_COM_MPSSE_H */

