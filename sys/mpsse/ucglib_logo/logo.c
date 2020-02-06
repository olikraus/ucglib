
#include "ucg.h"
#include "config.h"

void draw_ucg_logo(ucg_t *_ucg) {
    ucg_int_t a, b;
    //ucg_Init(ucg, ucg_sdl_dev_cb, ucg_ext_none, (ucg_com_fnptr)0);
    ucg_SetFont(_ucg, ucg_font_ncenB24_tr);
    //ucg_SetRotate270(ucg);  
    //ucg_SetClipRange(ucg, 10,5,40,20);
    a = 2;
    b = 3;
    ucg_SetColor(_ucg, 0, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 1, 176 * a / b, 226 * a / b, 255 * a / b);
    ucg_SetColor(_ucg, 2, 25 * a / b, 25 * a / b, 112 * a / b);
    ucg_SetColor(_ucg, 3, 85 * a / b, 26 * a / b, 139 * a / b);
    ucg_DrawGradientBox(_ucg, 0, 0, ucg_GetWidth(_ucg) / 4, ucg_GetHeight(_ucg));

    ucg_SetColor(_ucg, 1, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 0, 176 * a / b, 226 * a / b, 255 * a / b);
    ucg_SetColor(_ucg, 3, 25 * a / b, 25 * a / b, 112 * a / b);
    ucg_SetColor(_ucg, 2, 85 * a / b, 26 * a / b, 139 * a / b);
    ucg_DrawGradientBox(_ucg, ucg_GetWidth(_ucg) / 4, 0, ucg_GetWidth(_ucg) / 4, ucg_GetHeight(_ucg));

    ucg_SetColor(_ucg, 0, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 1, 176 * a / b, 226 * a / b, 255 * a / b);
    ucg_SetColor(_ucg, 2, 25 * a / b, 25 * a / b, 112 * a / b);
    ucg_SetColor(_ucg, 3, 85 * a / b, 26 * a / b, 139 * a / b);
    ucg_DrawGradientBox(_ucg, ucg_GetWidth(_ucg)*2 / 4, 0, ucg_GetWidth(_ucg) / 4, ucg_GetHeight(_ucg));

    ucg_SetColor(_ucg, 1, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 0, 176 * a / b, 226 * a / b, 255 * a / b);
    ucg_SetColor(_ucg, 3, 25 * a / b, 25 * a / b, 112 * a / b);
    ucg_SetColor(_ucg, 2, 85 * a / b, 26 * a / b, 139 * a / b);
    ucg_DrawGradientBox(_ucg, ucg_GetWidth(_ucg)*3 / 4, 0, ucg_GetWidth(_ucg) / 4, ucg_GetHeight(_ucg));

    upper_pin(_ucg, 7 + 0 * 14, 4);
    upper_pin(_ucg, 7 + 1 * 14, 4);
    upper_pin(_ucg, 7 + 2 * 14, 4);
    upper_pin(_ucg, 7 + 3 * 14, 4);

    ic_body(_ucg, 2, 10);

    lower_pin(_ucg, 7 + 0 * 14, 41);
    lower_pin(_ucg, 7 + 1 * 14, 41);
    lower_pin(_ucg, 7 + 2 * 14, 41);
    lower_pin(_ucg, 7 + 3 * 14, 41);

    ucg_SetColor(_ucg, 0, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_DrawString(_ucg, 63 + 1, 33 + 1, 0, "glib");

    ucg_SetColor(_ucg, 0, 255, 168, 0);
    ucg_DrawGlyph(_ucg, 26, 38, 0, 'U');
    ucg_DrawString(_ucg, 63, 33, 0, "glib");

    ucg_SetColor(_ucg, 0, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 1, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 2, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_SetColor(_ucg, 3, 135 * a / b, 206 * a / b, 250 * a / b);
    ucg_DrawGradientBox(_ucg, 84 + 1, 42 + 1 - 6, 42, 4);

    ucg_SetColor(_ucg, 0, 255, 180, 40);
    ucg_SetColor(_ucg, 1, 235, 148, 0);
    //ucg_DrawGradientLine(ucg, 79, 42, 20, 0);
    ucg_SetColor(_ucg, 2, 245, 158, 0);
    ucg_SetColor(_ucg, 3, 220, 138, 0);
    ucg_DrawGradientBox(_ucg, 84, 42 - 6, 42, 4);

    ucg_SetColor(_ucg, 0, 255, 168, 0);
    //ucg_SetFont(ucg, ucg_font_5x8_tr);
    ucg_SetFont(_ucg, ucg_font_7x13B_tr);
    //ucg_SetFont(ucg, ucg_font_courB08_tr);
    //ucg_SetFont(ucg, ucg_font_timR08_tr);
    ucg_DrawString(_ucg, 2, 54 + 5, 0, "http://github.com");
    ucg_DrawString(_ucg, 2, 61 + 10, 0, "/olikraus/ucglib");
    //ucg_DrawString(ucg, 1, 61, 0, "code.google.com/p/ucglib/");
}

void upper_pin(ucg_t *_ucg, ucg_int_t x, ucg_int_t y) {
    ucg_int_t w = 7;
    ucg_int_t h = 6;
    ucg_SetColor(_ucg, 0, 212, 212, 212);
    ucg_SetColor(_ucg, 1, 200, 200, 200);
    ucg_SetColor(_ucg, 2, 200, 200, 200);
    ucg_SetColor(_ucg, 3, 188, 188, 188);
    ucg_DrawGradientBox(_ucg, x, y, w, h);

    //ucg_DrawVLine(ucg, x+w, y+1, len);
    ucg_SetColor(_ucg, 0, 220, 220, 220);
    ucg_SetColor(_ucg, 1, 232, 232, 232);
    ucg_DrawGradientLine(_ucg, x + w, y, h, 1);
}

void lower_pin(ucg_t *_ucg, ucg_int_t x, ucg_int_t y) {
    ucg_int_t w = 7;
    ucg_int_t h = 5;
    ucg_SetColor(_ucg, 0, 212, 212, 212);
    ucg_SetColor(_ucg, 1, 200, 200, 200);
    ucg_SetColor(_ucg, 2, 200, 200, 200);
    ucg_SetColor(_ucg, 3, 188, 188, 188);
    ucg_DrawGradientBox(_ucg, x, y, w, h);

    //ucg_DrawVLine(ucg, x+w, y+1, len);
    ucg_SetColor(_ucg, 0, 220, 220, 220);
    ucg_SetColor(_ucg, 1, 232, 232, 232);
    ucg_DrawGradientLine(_ucg, x + w, y, h, 1);
    ucg_SetColor(_ucg, 0, 220, 220, 220);
    ucg_SetColor(_ucg, 1, 232, 232, 232);
    ucg_DrawGradientLine(_ucg, x, y + h, w, 0);
    ucg_SetColor(_ucg, 0, 240, 240, 240);
    ucg_DrawPixel(_ucg, x + w, y + h);
}

void ic_body(ucg_t *_ucg, ucg_int_t x, ucg_int_t y) {
    ucg_int_t w = 4 * 14 + 4;
    ucg_int_t h = 31;
    ucg_SetColor(_ucg, 0, 60, 60, 60);
    ucg_SetColor(_ucg, 1, 40, 40, 40);
    ucg_SetColor(_ucg, 2, 48, 48, 48);
    ucg_SetColor(_ucg, 3, 30, 30, 30);
    ucg_DrawGradientBox(_ucg, x, y, w, h);

    ucg_SetColor(_ucg, 0, 255, 168, 0);
    //ucg_SetColor(0, 225, 168, 30);
    ucg_DrawDisc(_ucg, x + w - 1, y + h / 2 - 1, 7, UCG_DRAW_UPPER_LEFT | UCG_DRAW_LOWER_LEFT);

    ucg_SetColor(_ucg, 0, 60, 30, 0);
    //_ucg.drawDisc(x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);

    ucg_SetColor(_ucg, 0, 50, 50, 50);
    ucg_SetColor(_ucg, 0, 25, 25, 25);
    ucg_DrawDisc(_ucg, x + w - 1, y + h / 2 + 1, 7, UCG_DRAW_UPPER_LEFT | UCG_DRAW_LOWER_LEFT);
}

