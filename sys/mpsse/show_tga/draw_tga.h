/* 
 * File:   draw_tga.h
 * Author: HappyCodingRobot
 *
 * Created on 17. April 2016, 19:51
 */

#ifndef DRAW_TGA_H
#define	DRAW_TGA_H

#ifdef	__cplusplus
extern "C" {
#endif

int draw_image(ucg_t *ucgPtr, const char *name);
void draw(void);

static uint8_t tga_read_byte(void);
static uint16_t tga_read_word(void);
static uint8_t tga_read_header(void);
static uint8_t tga_read_write_pixel(ucg_t *ucgPtr);
static uint8_t tga_read_byte(void);
static void tga_read_buf(uint8_t *buf, uint16_t len);
static uint8_t tga_open(const char *name);
static void tga_close(void);

#ifdef	__cplusplus
}
#endif

#endif	/* DRAW_TGA_H */

