

This page describes supported displays. Ucglib only supports color displays with internal controller and local display RAM. The setup for Ucglib depends on the internal controller, which is build into the color display.


# ST7735 #

  * Type: Color TFT
  * Dimension: 128x160
  * Color Depth: 18 Bit
  * Interfaces: HW SPI, SW SPI
  * Tutorial: [How to Connect a ST7735 Display](connectst7735.md)

## Arduino Constructor ##
| **Constructor** | **Description** |
|:----------------|:----------------|
| Ucglib\_ST7735\_18x128x160\_SWSPI ucg(`sclk`, `data`, `cd`, `cs`, `[reset]`) | Software SPI |
| Ucglib\_ST7735\_18x128x160\_HWSPI ucg(`cd`, `cs`, `[reset]`) | Hardware SPI |

## Device Procedures ##
  * Controller Device: `ucg_dev_st7735_18x128x160`
  * Extensions: `ucg_ext_st7735_18`, `ucg_ext_none`


# ILI9341 #

  * Type: Color TFT
  * Dimension: 240x320
  * Color Depth: 18 Bit
  * Interfaces: HW SPI, SW SPI
  * Tutorial: [How to connect a ILI9341 display](connectili9341.md)

## Arduino Constructor ##
| **Constructor** | **Description** |
|:----------------|:----------------|
| Ucglib\_ILI9341\_18x240x320\_SWSPI ucg(`sclk`, `data`, `cd`, `cs`, `[reset]`) | Software SPI |
| Ucglib\_ILI9341\_18x240x320\_HWSPI ucg(`cd`, `cs`, `[reset]`) | Hardware SPI |

## Device Procedures ##
  * Controller Device: `ucg_dev_ili9341_18x240x320`
  * Extensions: `ucg_ext_ili9341_18`, `ucg_ext_none`


# PCF8833 #

  * Type: Color TFT
  * Dimension: 132x132
  * Color Depth: 16 Bit
  * Interfaces: HW SPI, SW SPI
  * Tutorial: [How to connect a PCF8833 display](connectpcf8833.md)

## Arduino Constructor ##
| **Constructor** | **Description** |
|:----------------|:----------------|
| Ucglib\_PCF8833\_16x132x132\_SWSPI ucg(`sclk`, `data`, `cd`, `cs`, `[reset]`) | Software SPI |
| Ucglib\_PCF8833\_16x132x132\_HWSPI ucg(`cd`, `cs`, `[reset]`) | Hardware SPI |

## Device Procedures ##
  * Controller Device: `ucg_dev_pcf8833_16x132x132`
  * Extensions: `ucg_ext_pcf8833_16`, `ucg_ext_none`


# SSD1351 #

  * Type: Color OLED
  * Dimension: 128x128
  * Color Depth: 18 Bit
  * Interfaces: HW SPI, SW SPI
  * Tutorial: n.a.

## Arduino Constructor ##
| **Constructor** | **Description** |
|:----------------|:----------------|
| Ucglib\_SSD1351\_18x128x128\_SWSPI ucg(`sclk`, `data`, `cd`, `cs`, `[reset]`) | Software SPI, GPIO set to 0 (ILSoft OLED) |
| Ucglib\_SSD1351\_18x128x128\_HWSPI ucg(`cd`, `cs`, `[reset]`) | Hardware SPI, GPIO set to 0 (ILSoft OLED) |
| Ucglib\_SSD1351\_18x128x128\_FT\_SWSPI ucg(`sclk`, `data`, `cd`, `cs`, `[reset]`) | Software SPI, GPIO set to 1 (Freetronics OLED) |
| Ucglib\_SSD1351\_18x128x128\_FT\_HWSPI ucg(`cd`, `cs`, `[reset]`) | Hardware SPI, GPIO set to 1 (Freetronics OLED) |

## Device Procedures ##
  * Controller Devices: `ucg_dev_ssd1351_18x128x128_ilsoft`, `ucg_dev_ssd1351_18x128x128_ft`
  * Extensions: `ucg_ext_ssd1351_18`, `ucg_ext_none`





# Links #

  * [Wiki Main Page](ucglib.md)
  * [Reference Manual](reference.md)