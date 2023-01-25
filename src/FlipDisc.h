/*----------------------------------------------------------------------*
 * FlipDisc.h - Arduino library for flip-disc displays.                 *
 * This library is intended for use with the displays designed by       *
 * www.Flipo.io - Marcin Saj.                                           *
 *                                                                      *
 * The MIT License                                                      *
 * Marcin Saj 15 Jan 2023                                               *
 * https://github.com/marcinsaj/FlipDisc                                *
 *----------------------------------------------------------------------*/

#ifndef FlipDisc_h
#define FlipDisc_h

#include <SPI.h>
#include <avr/pgmspace.h>
#include "FlipDisc.h"

// Codenames of display modules
#define SEG     0x7F   
#define DOTS    0x3D
#define FLIP3   0x30
#define FLIP7   0x70
#define NONE    0xFF

// Codenames of symbols for 7-segment display
#define CLR   10  //  CLR - CLEAR DISPLAY
#define DEG   11  //  DEG - "°" - Degree symbol
#define CEL   12  //  CEL - "C" - Celsius symbol
#define FAH   13  //  FAH - "F" - Fahrenheit symbol 
#define HUM   14  //  HUM - "H" - Humidity symbol 
#define PFH   15  //  PFH - "%" - Percent first half symbol
#define PSH   16  //  PSH - "%" - Percent second half symbol 
#define UPD   17  //  UPD - "¯" - Upper dash symbol
#define MID   18  //  MID - "-" - Middle dash symbol
#define BTD   19  //  BTD - "_" - Bottom dash symbol

// Codenames for the SendBlankData() function
#define Before 0xAA
#define After  0xBB

// Codenames for the SendBlankData() function
#define moduleTypeColumn              0
#define numberBytesColumn             1
#define moduleRelativePositionColumn  2

/*
 * The 7-segment display consists of 23 disks. 
 * displaySegArray[][] - the array contains information about all the discs 
 * that we need to flip in order to display the selected digit/symbol.
 * Each of the discs has two sides, one "color" side corresponds to the "1", 
 * the "black" side "0".
 * 
 *
 *   0  1  2  3  4
 *  19           5
 *  18           6
 *  17 20 21 22  7
 *  16           8
 *  15           9
 *  14 13 12 11 10
*/ 
static const bool displaySegArray[20][23] = 
{
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22 
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},  //  0
  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //  1
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1},  //  2
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1},  //  3
  {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //  4
  {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},  //  5
  {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  6
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //  7
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  8
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1},  //  9
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //  CLR - CLEAR DISPLAY
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //  DEG - "°" - Degree symbol
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},  //  CEL - "C" - Celsius symbol  
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  FAH - "C" - Fahrenheit symbol 
  {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  HUM - "H" - Humidity symbol 
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},  //  PFH - "%" - Percent first half symbol  
  {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1},  //  PSH - "%" - Percent second half symbol  
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //  UPD - "¯" - Upper dash symbol
  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},  //  MID - "-" - Middle dash symbol
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}   //  BTD - "_" - Bottom dash symbol
}; 

/*
 * Refers to "SEG" - 7-segment display.
 * Each of the "0" or "1" disc statuses requires a different polarity of the current pulse 
 * released into the disc, and thus for each of the statuses we must drive different 
 * controller outputs to achieve the desired effect. 
 * -> setDiscArray[][] - the array contains the addresses of all control outputs corresponding 
 * to the setting of the discs to the "color" side.
 * A data frame to flip one disc requires 3 bytes and only two bits are set to "1" the other bits are "0".
 * To flip the entire display, we need to send 3 bytes x 23 discs = 69 bytes of data.
 */

static const uint8_t setDiscArray[23][3] PROGMEM =
{
  {0b00000010, 0b00000010, 0b00000000},  // 0
  {0b00000000, 0b00010010, 0b00000000},  // 1
  {0b01000000, 0b00010000, 0b00000000},  // 2
  {0b00001000, 0b00010000, 0b00000000},  // 3
  {0b01000010, 0b00000000, 0b00000000},  // 4
  {0b01000000, 0b00000100, 0b00000000},  // 5
  {0b01000000, 0b01000000, 0b00000000},  // 6
  {0b01000000, 0b00000000, 0b01000000},  // 7
  {0b01000000, 0b00000000, 0b00000100},  // 8
  {0b01000000, 0b00000000, 0b00000010},  // 9
  {0b11000000, 0b00000000, 0b00000000},  // 10
  {0b00001000, 0b00000000, 0b00000100},  // 11
  {0b00001000, 0b00000000, 0b00000010},  // 12
  {0b10001000, 0b00000000, 0b00000000},  // 13
  {0b10000000, 0b00000010, 0b00000000},  // 14
  {0b00000000, 0b00000010, 0b00000010},  // 15
  {0b00000000, 0b00000010, 0b00000100},  // 16
  {0b00000000, 0b00000010, 0b01000000},  // 17
  {0b00000000, 0b01000010, 0b00000000},  // 18
  {0b00000000, 0b00000110, 0b00000000},  // 19
  {0b00001000, 0b01000000, 0b00000000},  // 20
  {0b00001000, 0b00000100, 0b00000000},  // 21
  {0b00001000, 0b00000000, 0b01000000}   // 22
};

/*
 * Refers to "SEG" - 7-segment display.
 * -> resetDiscArray[][] - the array contains the addresses of all control outputs corresponding 
 * to the setting of the discs to the "black" side.
 * Each of the "0" or "1" disc statuses requires a different polarity of the current pulse 
 * released into the disc, and thus for each of the statuses we must drive different 
 * controller outputs to achieve the desired effect. 
 * A data frame to flip one disc requires 3 bytes and only two bits are set to "1" the other bits are "0".
 * To flip the entire display, we need to send 3 bytes x 23 discs = 69 bytes of data.
*/
static const uint8_t resetDiscArray[23][3] PROGMEM =
{
  {0b00000100, 0b00000000, 0b10000000},  // 0
  {0b00000000, 0b00100000, 0b10000000},  // 1
  {0b00100000, 0b00100000, 0b00000000},  // 2
  {0b00010000, 0b00100000, 0b00000000},  // 3
  {0b00100100, 0b00000000, 0b00000000},  // 4
  {0b00100000, 0b00001000, 0b00000000},  // 5
  {0b00100000, 0b10000000, 0b00000000},  // 6
  {0b00100000, 0b00000000, 0b00100000},  // 7
  {0b00100000, 0b00000000, 0b00000001},  // 8
  {0b00100000, 0b00000001, 0b00000000},  // 9
  {0b00100001, 0b00000000, 0b00000000},  // 10
  {0b00010000, 0b00000000, 0b00000001},  // 11
  {0b00010000, 0b00000001, 0b00000000},  // 12
  {0b00010001, 0b00000000, 0b00000000},  // 13
  {0b00000001, 0b00000000, 0b10000000},  // 14
  {0b00000000, 0b00000001, 0b10000000},  // 15
  {0b00000000, 0b00000000, 0b10000001},  // 16
  {0b00000000, 0b00000000, 0b10100000},  // 17
  {0b00000000, 0b10000000, 0b10000000},  // 18
  {0b00000000, 0b00001000, 0b10000000},  // 19
  {0b00010000, 0b10000000, 0b00000000},  // 20
  {0b00010000, 0b00001000, 0b00000000},  // 21
  {0b00010000, 0b00000000, 0b00100000}   // 22
};

/* 
 * Refers to "DOTS" - 2 and 3-dot display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "color" side.
 */ 
static const uint8_t setDiscDot[3] PROGMEM =
{
  0b00100001,  
  0b00101000,
  0b00100010
};

/* 
 * Refers to "DOTS" - 2 and 3-dot display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "black" side.
 */ 
static const uint8_t resetDiscDot[3] PROGMEM =
{
  0b11000000,
  0b01010000,
  0b01000100
};

class FlipDisc
{
    public:
        FlipDisc();
        void Pin(uint16_t EN_PIN, uint16_t CH_PIN, uint16_t PL_PIN);
        void Init(uint8_t MOD1, uint8_t MOD2 = 0xFF, uint8_t MOD3 = 0xFF, 
                                uint8_t MOD4 = 0xFF, uint8_t MOD5 = 0xFF, 
                                uint8_t MOD6 = 0xFF, uint8_t MOD7 = 0xFF, 
                                uint8_t MOD8 = 0xFF);
        void Seg(uint8_t data1, uint8_t data2 = 0xFF, uint8_t data3 = 0xFF, 
                                uint8_t data4 = 0xFF, uint8_t data5 = 0xFF, 
                                uint8_t data6 = 0xFF, uint8_t data7 = 0xFF, 
                                uint8_t data8 = 0xFF);
        void ToSeg(uint8_t segNumber, uint8_t data);
        void Dot(uint8_t segNumber, uint8_t dot1, uint8_t dot2 = 0xFF, uint8_t dot3 = 0xFF);
        
    private:
        void SendBlankData(uint8_t moduleNumber, uint8_t moduleType, uint8_t dataPosition);
        void ClearAllOutputs(void);
        void PrepareCurrentPulse(void);
        void ReleaseCurrentPulse(void);
};

extern FlipDisc FlipDisc;

#endif
