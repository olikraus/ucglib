

# How to Connect a PCF8833 Display #

## Linksprite Shield ##

The Linksprinte Shield can be connected directly to the Arduino Uno. Level shifters and power supply are part of the shield.

![http://wiki.ucglib.googlecode.com/hg/pic/pcf8833_linksprite_shield.jpg](http://wiki.ucglib.googlecode.com/hg/pic/pcf8833_linksprite_shield.jpg)


The wiring is fixed by the shield:

| **Constructor argument** | **Arduino pin number** |
|:-------------------------|:-----------------------|
| sclk | 13 |
| data | 11 |
| cd | n.a.  |
| cs | 9  |
| reset | 8 |


The PCF8833 does not have a command/data input line. Instead this information is part of the 9-bit SPI transfer. The Ucglib constructor looks like this:
```
Ucglib_PCF8833_16x132x132_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 9, /*reset=*/ 8);
```




## Software ##

Here is A simple "Hello World" example:
```
#include <SPI.h>
#include "Ucglib.h"

Ucglib_PCF8833_16x132x132_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 9, /*reset=*/ 8);

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



# Links #

  * [Wiki Main Page](ucglib.md)
  * [Reference Manual](reference.md)
  * [Supported Displays](displays.md)