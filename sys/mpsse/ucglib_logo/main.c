/* 
 * File:   main.c
 * Author: HappyCodingRobot
 *
 * Created on 16. April 2016, 23:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ucg.h"
#include "ucglib_com_mpsse.h"
#include "config.h"

ucg_t ucg;


/*
 * 
 */
int main(int argc, char** argv) {
    printf(".init\n\r");
    //ucg_Init(&ucg, ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, ucg_com_mpsse_spi);
    ucg_Init(&ucg, ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, ucg_com_mpsse_spi);
    
    ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT) ;
    
    printf(".clearscreen\n\r");
    ucg_ClearScreen(&ucg);
    
    printf(".draw logo\n\r");
    draw_ucg_logo(&ucg);
    
    printf(".draw image\n\r");
    //draw_image();

    /*-----------------------------------------------*/
    printf("closing..\n\r");
    ucg_com_PowerDown(&ucg);
    return (mpsse_retval);
}

