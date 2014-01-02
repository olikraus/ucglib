/*

  ucg_ic_ssd1351.c

  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/

static const uint8_t u8g_dev_ssd1351_128x128_init_seq[] PROGMEM = {
	UCG_CS(0),					/* disable chip */
	UCG_CFG_CD(0,1),				/* DC=0 for command mode, DC=1 for data and args */
	UCG_DLY_MS(20),
  	U8G_RST(1),					
	UCG_DLY_MS(20),
  	U8G_RST(0),					
	UCG_DLY_MS(20),
  	U8G_RST(1),
	UCG_DLY_MS(20),
	UCG_CS(1),					/* enable chip */
	UCG_DLY_MS(50),
	UCG_C11(0x0fd, 0x012);			/* Unock normal commands */
	UCG_C11(0x0fd, 0x0b1);			/* Unock extra commands */
	UCG_C10(0xae);				/* Set Display Off */

  	UCG_C11(0x0b3, 0x0f1);			/* Front Clock Div */
  	UCG_C11(0x0ca, 0x07f);			/* Set Multiplex Ratio */
  	UCG_C11(0x0a0, 0x0b4);			/* Set Colour Depth */
  	UCG_C12(0x015, 0x000, 0x07f);	/* Set Column Address */
  	UCG_C12(0x075, 0x000, 0x07f);	/* Set Row Address */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xa1,
	U8G_ESC_ADR(1),
	0x00,							/* Set Display Start Line */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xa2,
	U8G_ESC_ADR(1),
	0x00,							/* Set Display Offset */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xb5,
	U8G_ESC_ADR(1),
	0x00,							/* Set GPIO */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xab,
	U8G_ESC_ADR(1),
	0x01,							/* Set Function Selection */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xb1,
	U8G_ESC_ADR(1),
	0x32,							/* Set Phase Length */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xb4,
	U8G_ESC_ADR(1),
	0xa0, 0xb5, 0x55,				/* Set Segment Low Voltage */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xbb,
	U8G_ESC_ADR(1),
	0x17,							/* Set Precharge Voltage */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xbe,
	U8G_ESC_ADR(1),
	0x05,							/* Set VComH Voltage */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xc1,
	U8G_ESC_ADR(1),
	0xc8, 0x80, 0xc8,				/* Set Contrast */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xc7,
	U8G_ESC_ADR(1),
	0x0f,							/* Set Master Contrast */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xb6,
	U8G_ESC_ADR(1),
	0x01,							/* Set Second Precharge Period */

	U8G_ESC_ADR(0),					/* instruction mode */
	0xa6,							/* Set Display Mode Reset */


	U8G_ESC_ADR(0),					/* instruction mode */
	0xb8,							/* Set CMD Grayscale Lookup */
	U8G_ESC_ADR(1),
	0x05,
	0x06,
	0x07,
	0x08,
	0x09,
	0x0a,
	0x0b,
	0x0c,
	0x0D,
	0x0E,
	0x0F,
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x18,
	0x1a,
	0x1b,
	0x1C,
	0x1D,
	0x1F,
	0x21,
	0x23,
	0x25,
	0x27,
	0x2A,
	0x2D,
	0x30,
	0x33,
	0x36,
	0x39,
	0x3C,
	0x3F,
	0x42,
	0x45,
	0x48,
	0x4C,
	0x50,
	0x54,
	0x58,
	0x5C,
	0x60,
	0x64,
	0x68,
	0x6C,
	0x70,
	0x74,
	0x78,
	0x7D,
	0x82,
	0x87,
	0x8C,
	0x91,
	0x96,
	0x9B,
	0xA0,
	0xA5,
	0xAA,
	0xAF,
	0xB4,

	U8G_ESC_ADR(0),
	0xaf,							/* Set Display On */
	0x5c,
	U8G_ESC_DLY(50),
	U8G_ESC_CS(0),					/* disable chip */
	U8G_ESC_ADR(1),
	U8G_ESC_END						/* end of sequence */
};
