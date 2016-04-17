/* 
 * File:   main.c
 * Author: HappyCodingRobot
 *
 * Created on 17. April 2016, 19:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ucg.h"
#include "ucglib_com_mpsse.h"
#include "draw_tga.h"

ucg_t ucg;


/*
 * 
 */
int main(int argc, char** argv) {
    printf(".init\n\r");
    //ucg_Init(&ucg, ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, ucg_com_mpsse_spi);
    ucg_Init(&ucg, ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, ucg_com_mpsse_spi);
    
    ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT) ;
    
    printf(".draw image\n\r");
    if (draw_image(&ucg, "smokey_320.tga") > 0) {
    //if (draw_image(&ucg, "testing.tga") > 0) {
    //if (draw_image(&ucg, "smokey_128.tga") > 0) {
        printf("! some error happened..\n\r");
    }
    
    /*-----------------------------------------------*/
    printf("closing..\n\r");
    ucg_com_PowerDown(&ucg);
    return (mpsse_retval);
}
