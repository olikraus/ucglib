

# How to Connect a ILI9341 Display #

## Breakout Board ##

The red breakout board from the following picture is a 3.3V board. It can be connected to the Arduino Due, but requires level shifters for the Uno and Mega boards.
![http://wiki.ucglib.googlecode.com/hg/pic/ili9341_breakout_front.jpg](http://wiki.ucglib.googlecode.com/hg/pic/ili9341_breakout_front.jpg)

Backlight LED requires a resistor (I have used 33 Ohm). The resistor is placed on the connector (behind the cable).
![http://wiki.ucglib.googlecode.com/hg/pic/ili9341_breakout_back.jpg](http://wiki.ucglib.googlecode.com/hg/pic/ili9341_breakout_back.jpg)

### Wiring ###

The following constructor can be used for this ILI9341 display:
```
Ucglib_ILI9341_18x240x320_SWSPI ucg(uint8_t sclk, uint8_t data, uint8_t cd, uint8_t cs, uint8_t reset);
```

The best method for wiring a display is to start with a table that contains the signals. The sequence should be the same as for the arguments of the constructor call:

| **Constructor argument** | **Arduino pin number** |
|:-------------------------|:-----------------------|
| sclk | <pin number> |
| data | <pin number> |
| cd | <pin number> |
| cs | <pin number> |
| reset | <pin number> |

Now the signal lines need to be matched to the display pins. This should be easy except for the "cd" argument. The cd signal (command/data) has a lot of names. Often used are: CD, DC, DC, RS, A0. In this case, the "cd" line is named as "C/D" on the PCB.

Now, the display can be connected to the Arduino Due. The table will look like this (see picture above):

| **Constructor argument** | **Arduino pin number** |
|:-------------------------|:-----------------------|
| sclk | 7 (green) |
| data | 6 (blue) |
| cd | 5 (purple) |
| cs | 3 (white) |
| reset | 4 (gray) |

With the numbers from the table, the corresponding constructor call will look like this:
```
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
```

### Software ###

Here is A simple "Hello World" example:
```
#include <SPI.h>
#include "Ucglib.h"

Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);

void setup(void) {
  delay(1000);
  ucg.begin();
  ucg.clearScreen();
}

void loop(void) {
  ucg.setFont(ucg_font_ncenR14r);
  ucg.setPrintPos(0,25);
  ucg.setColor(255, 255, 255);
  ucg.print("Hello World!");

  delay(500);  
}
```

## Elec Freaks Shield ##

The Elec Freaks Shield already includes a proper supply power for the backlight LED and also level shifters for the Arduino Uno boards

![http://wiki.ucglib.googlecode.com/hg/pic/ili9341_elec_freaks_display.jpg](http://wiki.ucglib.googlecode.com/hg/pic/ili9341_elec_freaks_display.jpg)

![http://wiki.ucglib.googlecode.com/hg/pic/ili9341_elec_freaks_back.jpg](http://wiki.ucglib.googlecode.com/hg/pic/ili9341_elec_freaks_back.jpg)

The wiring is fixed by the shield:

| **Constructor argument** | **Arduino pin number** |
|:-------------------------|:-----------------------|
| sclk | 4 |
| data | 3 |
| cd | 6  |
| cs | 7  |
| reset | 5 |

Together with this information, the constructor will look like this:
```
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6 , /*cs=*/ 7, /*reset=*/ 5);
```

# Links #

  * [Wiki Main Page](ucglib.md)
  * [Reference Manual](reference.md)
  * [Supported Displays](displays.md)