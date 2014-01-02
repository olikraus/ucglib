

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


int ucg_sdl_get_key(void);


ucg_t ucg;

uint8_t my_init_sequence[] = {
  UCG_CFG_CD(0,0),
  UCG_RST(0),
  UCG_DLY_MS(2),
  UCG_RST(1),
  UCG_DLY_MS(2),
  UCG_C11(0xaa, 0x055),
  UCG_END()
};

ucg_int_t ucg_my_dev_cb(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch(msg)
  {
    case UCG_MSG_DEV_POWER_UP:
      ucg_com_PowerUp(ucg, 66);
      ucg_com_SendCmdSeq(ucg, my_init_sequence);
      return 1;
    case UCG_MSG_DEV_POWER_DOWN:
      return 1;
    case UCG_MSG_GET_DIMENSION:
      ((ucg_wh_t *)data)->w = 40;
      ((ucg_wh_t *)data)->h = 15;
      return 1;
    case UCG_MSG_DRAW_PIXEL:
      return 1;
    case UCG_MSG_DRAW_L90FX:
      ucg_handle_l90fx(ucg, ucg_my_dev_cb);
      return 1;
    case UCG_MSG_DRAW_L90TC:
      ucg_handle_l90tc(ucg, ucg_my_dev_cb);
      return 1;
    case UCG_MSG_DRAW_L90SE:
      ucg_handle_l90se(ucg, ucg_my_dev_cb);
      return 1;
  }
  return ucg_dev_default_cb(ucg, msg, data);  
}

int16_t ucg_my_com_cb(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_POWER_UP", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      break;
    case UCG_COM_MSG_DELAY:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_DELAY", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_CHANGE_RESET_LINE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_CHANGE_CD_LINE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_SEND_BYTE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      break;
    case UCG_COM_MSG_SEND_STR:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_SEND_STR", ucg->com_status, (long unsigned int)arg);
      break;
  }
  return 1;
}


unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(void)
{
  ucg_int_t i;
  
  ucg_Init(&ucg, ucg_my_dev_cb, ucg_my_com_cb);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  
  ucg_DrawBitmapLine(&ucg, 9,0, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,1, 0,16, bitmap);
  
  ucg_DrawBitmapLine(&ucg, 0,9, 1,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 1,10, 1,16, bitmap);
  
  for( i = 0; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 0; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);
 
  ucg_SetClipRange(&ucg, 10, 10, 25, 25);

  ucg_SetColor(&ucg, 0, 0, 255, 0);
  for( i = 1; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 1; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);

  ucg_SetColor(&ucg, 0, 80, 80, 255);

  
  ucg_DrawHLine(&ucg, 8, 9, 5);
  ucg_DrawHLine(&ucg, 8, 10, 5);
  ucg_DrawHLine(&ucg, 8, 11, 5);
  ucg_DrawHLine(&ucg, 8, 12, 100);

  ucg_DrawHLine(&ucg, 12, 13, 5);
  ucg_DrawHLine(&ucg, 12, 14, 100);

  ucg_DrawHLine(&ucg, 2, 15, 5);
  ucg_DrawHLine(&ucg, 40, 16, 5);

  ucg_DrawHRLine(&ucg, 12, 17, 1);
  ucg_DrawHRLine(&ucg, 12, 18, 2);
  ucg_DrawHRLine(&ucg, 12, 19, 3);
  ucg_DrawHRLine(&ucg, 12, 20, 4);

  ucg_DrawHRLine(&ucg, 36, 17, 1);
  ucg_DrawHRLine(&ucg, 36, 18, 2);
  ucg_DrawHRLine(&ucg, 36, 19, 3);
  ucg_DrawHRLine(&ucg, 36, 20, 4);

  ucg_DrawBitmapLine(&ucg, 9,22, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,23, 0,16, bitmap);

  ucg_SetClipRange(&ucg, 70-9, 20-9, 20, 20);

  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');


  ucg_SetMaxClipRange(&ucg);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  
  return 0;
}

