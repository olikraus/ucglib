

# Com Interface Manual #

## Signal Names ##

| **Signal Name** | **Ucglib** | **Also known as...** |
|:----------------|:-----------|:---------------------|
| Command/Data Selection | CD | RS, D/C, A0 |
| Chip Select | CS |  |
| Controller Reset | Reset | Res |

## Command Table ##

The following commands are available withing the command sequence (`ucg_com_SendCmdSeq`):

| **Cmd**			| **Description** |
|:----------|:----------------|
| UCG\_C10(c0)			| Send 1x command byte |
| UCG\_C20(c0,c1)		| Send 2x command byte, high byte first |
| UCG\_C11(c0,a0)		| Send 1x command byte and 1x data byte |
| UCG\_C21(c0,c1,a0)		| Send 2x command byte and 1x data byte |
| UCG\_C12(c0,a0,a1)		| Send 1x command byte and 2x data byte |
| UCG\_C22(c0,c1,a0,a1)		| Send 2x command byte and 2x data byte |
| UCG\_C13(c0,a0,a1,a2)		| Send 1x command byte and 3x data byte |
| UCG\_C23(c0,c1,a0,a1,a2)	| Send 2x command byte and 3x data byte |
| UCG\_C14(c0,a0,a1,a2,a3)	| Send 1x command byte and 4x data byte |
| UCG\_C24(c0,c1,a0,a1,a2,a3)	| Send 2x command byte and 4x data byte |
| UCG\_C15(c0,a0,a1,a2,a3,a4)	| Send 1x command byte and 5x data byte |
| UCG\_A1(d0)				| Send 1x argument byte |
| UCG\_A2(d0,d1)			| Send 2x argument byte |
| UCG\_A3(d0,d1,d2)			| Send 3x argument byte |
| UCG\_A4(d0,d1,d2,d3)			| Send 4x argument byte |
| UCG\_A5(d0,d1,d2,d3,d4)		| Send 5x argument byte |
| UCG\_A6(d0,d1,d2,d3,d4,d5)		| Send 6x argument byte |
| UCG\_A7(d0,d1,d2,d3,d4,d5,d6)		| Send 7x argument byte |
| UCG\_A8(d0,d1,d2,d3,d4,d5,d6,d7) 	| Send 8x argument byte |
| UCG\_DATA()				| Force data output for next byte |
| UCG\_D1(d0)				| Send 1x data byte |
| UCG\_D2(d0,d1)			| Send 2x data byte |
| UCG\_D3(d0,d1,d2)			| Send 3x data byte |
| UCG\_D4(d0,d1,d2,d3)			| Send 4x data byte |
| UCG\_D5(d0,d1,d2,d3,d4)		| Send 5x data byte |
| UCG\_D6(d0,d1,d2,d3,d4,d5)		| Send 6x data byte |
| UCG\_DLY\_MS(t)			| Delay 0..4095 milliseconds |
| UCG\_DLY\_US(t)			| Delay 0..4095 microseconds |
| UCG\_VARX(s,a,o)			| Send ((XPOS>>s)&a)|o |
| UCG\_VARY(s,a,o)			| Send ((YPOS>>s)&a)|o |
| UCG\_RST(level)			| Force reset line to `level` |
| UCG\_CS(level)			| Force CS line to `level` |
| UCG\_CFG\_CD(c,a)			| Define values for command (c) and argument (a) bytes |
| UCG\_END()				| Terminate sequence |



## `ucg_com_DelayMicroseconds` ##
  * **C Prototype:**
```
void ucg_com_DelayMicroseconds(ucg_t *ucg, uint16_t delay);
```
  * **Description:** Delay by the specified number of microseconds. There are 1000000 microseconds in one second. `delay` must be smaller than 4096.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `delay`: Number of microseconds for the delay (Range: 0..4095)
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_DelayMilliseconds` ##
  * **C Prototype:**
```
void ucg_com_DelayMilliseconds(ucg_t *ucg, uint16_t delay);
```
  * **Description:** Delay by the specified number of milliseconds. There are 1000 milliseconds in one second. `delay` must be smaller than 4096.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `delay`: Number of milliseconds for the delay (Range: 0..4095)
  * **Returns:** -
  * **See also:**
  * **Example:**


## `ucg_com_SendByte` ##
  * **C Prototype:**
```
void ucg_com_SendByte(ucg_t *ug, uint8_t byte);
```
  * **Description:** Send one byte to the display
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `byte`: The value which should be sent to the display
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_SendCmdDataSequence` ##
  * **C Prototype:**
```
void ucg_com_SendCmdDataSequence(ucg_t *ucg, uint16_t cnt, const uint8_t *byte_ptr, uint8_t cd_line_status_at_end);
```
  * **Description:** Send a sequence of command-data/data pairs. The sequence of bytes must look like this:
> | 0,1,2 | data | 0,1,2 | data | ... | 0,1,2 | data |
|:------|:-----|:------|:-----|:----|:------|:-----|
> Where the first value of the two byte CD/data pair is 0 (do not change CD line), 1 (force CD line to 0) or 2 (force CD line to 1).
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `cnt`: The number of CD/data pairs in the sequence
    * `byte_ptr`: Pointer to the first pair
    * `cd_line_status_at_end`: The line status, that is forced on the CD line (0 for low, 1 for high)
  * **Returns:** -
  * **See also:**
  * **Example:**


## `ucg_com_SendCmdSeq` ##
  * **C Prototype:**
```
void ucg_com_SendCmdSeq(ucg_t *ucg, const ucg_pgm_uint8_t *data);
```
  * **Description:** Execute a command sequence. The command sequence must be terminated with `UCG_END()`. In AVR systems, this sequence is placed into PROGMEM area. See above for the description of the commands.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `data`: Pointer to the first byte of the command sequence
  * **Returns:** -
  * **See also:**
  * **Example:**
```
const ucg_pgm_uint8_t ucg_ili9325_set_pos_seq[] = 
{
  UCG_CS(0),					/* enable chip */
  UCG_C10(0x020),	UCG_VARX(0,0x00, 0), UCG_VARX(0,0x0ff, 0), /* set x position */
  UCG_C10(0x021),	UCG_VARY(8,0x01, 0), UCG_VARY(0,0x0ff, 0), /* set y position */
  UCG_C10(0x022),							/* write to RAM */
  UCG_DATA(),								/* change to data mode */
  UCG_END()
};
...
ucg_com_SendCmdSeq(ucg, ucg_ili9325_set_pos_seq);
```


## `ucg_com_SendRepeatByte` ##
  * **C Prototype:**
```
void ucg_com_SendRepeatByte(ucg_t *ucg, uint16_t cnt, uint8_t byte);
```
  * **Description:** Repeated sending of one byte to the display. `cnt` bytes will be transfered.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `cnt`: How often the byte should be sent.
    * `byte`: The value which should be sent to the display
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_SendRepeat2Bytes` ##
  * **C Prototype:**
```
void ucg_com_SendRepeat2Bytes(ucg_t *ucg, uint16_t cnt, uint8_t *byte_ptr);
```
  * **Description:** Repeated sending of two bytes to the display. `2*cnt` bytes will be transfered.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `cnt`: How often the two-byte sequence should be sent.
    * `byte_ptr`: A pointer to two bytes
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_SendRepeat3Bytes` ##
  * **C Prototype:**
```
void ucg_com_SendRepeat3Bytes(ucg_t *ucg, uint16_t cnt, uint8_t *byte_ptr);
```
  * **Description:** Repeated sending of three bytes to the display. `3*cnt` bytes will be transfered.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `cnt`: How often the three-byte sequence should be sent.
    * `byte_ptr`: A pointer to three bytes
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_SendString` ##
  * **C Prototype:**
```
void ucg_com_SendString(ucg_t *ucg, uint16_t cnt, const uint8_t *byte_ptr);
```
  * **Description:** Send a sequence of `cnt`bytes.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `cnt`: The total number of bytes in the sequence
    * `byte_ptr`: A pointer to the first byte of the sequence
  * **Returns:** -
  * **See also:**
  * **Example:**


## `ucg_com_SetCSLineStatus` ##
  * **C Prototype:**
```
void ucg_com_SetCSLineStatus(ucg_t *ucg, uint8_t level);
```
  * **Description:** Force the digital signal level on the CS (chip select) line to the specified value.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `level`: 0 for low level, 1 for high level
  * **Returns:** -
  * **See also:**
  * **Example:**

## `ucg_com_SetCDLineStatus` ##
  * **C Prototype:**
```
void ucg_com_SetCDLineStatus(ucg_t *ucg, uint8_t level);
```
  * **Description:** Force the digital signal level on the CD (command/data) line to the specified value.
  * **Arguments:**
    * `ucg`: Pointer to the Ucg data structure
    * `level`: 0 for low level, 1 for high level
  * **Returns:** -
  * **See also:**
  * **Example:**