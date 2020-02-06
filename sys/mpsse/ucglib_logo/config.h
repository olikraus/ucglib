/* 
 * File:   config.h
 * Author: HappyCodingRobot
 *
 * Created on 16. April 2016, 23:49
 */
#ifndef CONFIG_H
#define	CONFIG_H


void loop(void);

/* in logo.c */
void draw_ucg_logo(ucg_t *_ucg);
void upper_pin(ucg_t *_ucg, ucg_int_t x, ucg_int_t y);
void lower_pin(ucg_t *_ucg, ucg_int_t x, ucg_int_t y);
void ic_body(ucg_t *_ucg, ucg_int_t x, ucg_int_t y);


#endif	/* CONFIG_H */

