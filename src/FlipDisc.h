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

// Codenames of display modules
static const uint8_t D7SEG = 0x7F;
static const uint8_t D2X1  = 0x31; /* D3X1 = D2X1 - are the same */
static const uint8_t D3X1  = 0x31;
static const uint8_t D1X3  = 0x13;
static const uint8_t D1X7  = 0x17;
static const uint8_t NONE  = 0xFF;

// Codenames of symbols for 7-segment display
static const uint8_t ALL = 8;    // ALL - Set all discs
static const uint8_t CLR = 10;   // CLR - Clear display
static const uint8_t A   = 11;
static const uint8_t B   = 12;
static const uint8_t C   = 13;
static const uint8_t D   = 14;
static const uint8_t E   = 15;
static const uint8_t F   = 16;
static const uint8_t G   = 17;
static const uint8_t H   = 18;
static const uint8_t I   = 19;
static const uint8_t J   = 20;
static const uint8_t K   = 21;
static const uint8_t L   = 22;
static const uint8_t M   = 23;
static const uint8_t N   = 24;
static const uint8_t O   = 25;
static const uint8_t P   = 26;
static const uint8_t Q   = 27;
static const uint8_t R   = 28;
static const uint8_t S   = 29;
static const uint8_t T   = 30;
static const uint8_t U   = 31;
static const uint8_t V   = 32;
static const uint8_t W   = 33;
static const uint8_t X   = 34;
static const uint8_t Y   = 35;
static const uint8_t Z   = 36;
static const uint8_t DEG = 37;   // DEG - "°"  - Degree symbol
static const uint8_t PFH = 37;   // PFH - "%"  - Percent first half symbol
static const uint8_t PSH = 38;   // PSH - "%"  - Percent second half symbol
static const uint8_t HLU = 39;   // HLU - "¯"  - Horizontal line - upper
static const uint8_t HLM = 40;   // HLM - "-"  - Horizontal line - middle
static const uint8_t HLL = 41;   // HLL - "_"  - Horizontal line - lower
static const uint8_t HLT = 42;   // HLT - "="  - Horizontal line - upper & lower
static const uint8_t HLA = 43;   // HLA - "≡"  - All three lines
static const uint8_t MIN = 40;   // MIN - "-"  - Minus symbol
static const uint8_t VLL = 44;   // VLL - "| " - Vertical line - left
static const uint8_t VLR = 1 ;   // VLR - " |" - Vertical line - right
static const uint8_t VLA = 45;   // VLA - "||" - All Vertical lines


// Codenames for the SendBlankData() function
static const uint8_t BEFORE = 0xAA;
static const uint8_t AFTER = 0xBB;

// Codenames for the moduleInitArray[][3] columns
static const uint8_t module_type_column = 0;
static const uint8_t number_bytes_column = 1;
static const uint8_t module_relative_position_column = 2;

/*
 * The 7-segment display consists of 23 disks. 
 * displayArray_7Seg[][] - the array contains information about all the discs 
 * that we need to flip in order to display the selected digit/symbol.
 * Each of the discs has two sides, one "color" side corresponds to the "1", 
 * the "black" side "0".
 * 
 *  0  1  2  3  4
 * 19           5
 * 18           6
 * 17 20 21 22  7
 * 16           8
 * 15           9
 * 14 13 12 11 10
 
 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22 
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  0
 * 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  1/VLR - " |" - Vertical line - right
 * 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1  //  2
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1  //  3
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1  //  4
 * 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1  //  5
 * 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  6
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  7
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  8/ALL - Set all discs 
 * 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1  //  9
 * 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  10/CLR - Clear display
 * 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  11/A
 * 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  12/B
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  13/C
 * 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  14/D 
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  15/E
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  16/F
 * 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1  //  17/G 
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  18/H
 * 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  19/I
 * 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0  //  20/J
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  21/K
 * 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  22/L 
 * 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0  //  23/M
 * 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0  //  24/N 
 * 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0  //  25/0
 * 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  26/P
 * 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0  //  27/Q
 * 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1  //  28/R
 * 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1  //  29/S
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0  //  30/T
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0  //  31/U 
 * 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0  //  32/V 
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0  //  33/W
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1  //  34/X
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1  //  35/Y 
 * 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0  //  36/Z
 * 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1  //  37/DEG - "°"  - Degree symbol / PFH - "%" - Percent first half symbol
 * 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1  //  37/PFH - "%"  - Percent first half symbol 
 * 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1  //  38/PSH - "%"  - Percent second half symbol  
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  39/HLU - "¯"  - Upper line symbol
 * 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1  //  40/HLM - "-"  - Middle line symbol
 * 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  //  41/HLL - "_"  - Lower line symbol
 * 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0  //  42/HLT - "="  - Upper & lower lines
 * 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1  //  43/HLA - "≡"  - All three lines
 * 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  44/VLL - "| "  - Vertical line - left
 * 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  //  1/VLR  - " |"  - Vertical line - right
 * 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0  //  45/VLA - "||"  - All Vertical lines
 */ 

/* 
 * Compressed array of all bits corresponding to discs states for selected symbols.
 * Disc numbers in individual bytes:
 * 7,6,5,4,3,2,1,0  15,14,13,12,11,10,9,8  23,22,21,20,19,18,17,16 
 */
static const uint8_t displayArray_7Seg[46][3] PROGMEM =
{    
  {0b11111111, 0b11111111, 0b00001111}, // 0 
  {0b11110000, 0b00000111, 0b00000000}, // 1/VLR - " |" - Vertical line - right
  {0b11111111, 0b11111100, 0b01110011}, // 2
  {0b11111111, 0b01111111, 0b01110010}, // 3
  {0b11110001, 0b00000111, 0b01111110}, // 4
  {0b10011111, 0b01111111, 0b01111110}, // 5
  {0b10011111, 0b11111111, 0b01111111}, // 6
  {0b11111111, 0b00000111, 0b00000000}, // 7
  {0b11111111, 0b11111111, 0b01111111}, // 8/ALL - Set all discs
  {0b11111111, 0b01111111, 0b01111110}, // 9
  {0b00000000, 0b00000000, 0b00000000}, // 10/CLR - Clear display
  {0b11101110, 0b11000111, 0b01111111}, // 11/A
  {0b01101111, 0b11111011, 0b01111111}, // 12/B
  {0b00011111, 0b11111100, 0b00001111}, // 13/C
  {0b11101111, 0b11111011, 0b00001111}, // 14/D
  {0b00011111, 0b11111100, 0b01111111}, // 15/E
  {0b00011111, 0b11000000, 0b01111111}, // 16/F
  {0b10011110, 0b10111111, 0b01001111}, // 17/G
  {0b11110001, 0b11000111, 0b01111111}, // 18/H
  {0b11110000, 0b00000111, 0b00000000}, // 19/I/VLR - " |" - Vertical line - right
  {0b11110000, 0b10111011, 0b00000000}, // 20/J  
  {0b01110001, 0b11000111, 0b01111111}, // 21/K
  {0b00000001, 0b11111100, 0b00001111}, // 22/L
  {0b11111011, 0b11000111, 0b00101111}, // 23/M
  {0b11110011, 0b11001111, 0b00101111}, // 24/N
  {0b11101110, 0b10111011, 0b00001111}, // 25/0
  {0b01101111, 0b11000000, 0b01111111}, // 26/P
  {0b11101110, 0b10111111, 0b00001111}, // 27/Q
  {0b01101111, 0b11000111, 0b01111111}, // 28/R
  {0b00011110, 0b01111011, 0b01111100}, // 29/S
  {0b00011111, 0b00010000, 0b00100000}, // 30/T
  {0b11110001, 0b10111011, 0b00001111}, // 31/U
  {0b00010001, 0b11100000, 0b00101111}, // 32/V
  {0b11110001, 0b11101111, 0b00101111}, // 33/W
  {0b01110001, 0b11000111, 0b01111101}, // 34/X
  {0b11110001, 0b00000111, 0b01111100}, // 35/Y
  {0b00111111, 0b11111100, 0b00100000}, // 36/Z
  {0b11111111, 0b00000000, 0b01111110}, // 37/DEG/PFH - "°" - Degree symbol / "%" - Percent first half symbol
  {0b10000000, 0b11111111, 0b01110011}, // 38/PSH - "%"  - Percent second half symbol  
  {0b00011111, 0b00000000, 0b00000000}, // 39/HLU - "¯"  - Horizontal line - upper
  {0b10000000, 0b00000000, 0b01110010}, // 40/HLM - "-"  - Horizontal line - middle
  {0b00000000, 0b01111100, 0b00000000}, // 41/HLL - "_"  - Horizontal line - lower 
  {0b00011111, 0b01111100, 0b00000000}, // 42/HLT - "="  - Horizontal line - upper & lower
  {0b10011111, 0b01111100, 0b01110010}, // 43/HLA - "≡"  - All three lines 
  {0b00000001, 0b11000000, 0b00001111}, // 44/VLL - "| " - Vertical line - left
  {0b11110001, 0b11000111, 0b00001111}  // 45/VLA - "||" - All Vertical lines
};

/*
 * Refers to "D7SEG" - 7-segment display.
 * Each of the "0" or "1" disc statuses requires a different polarity of the current pulse 
 * released into the disc, and thus for each of the statuses we must drive different 
 * controller outputs to achieve the desired effect. 
 * -> setDiscArray_7Seg[][] - the array contains the addresses of all control outputs corresponding 
 * to the setting of the discs to the "color" side.
 * A data frame to flip one disc requires 3 bytes and only two bits are set to "1" the other bits are "0".
 * To flip the entire display, we need to send 3 bytes x 23 discs = 69 bytes of data.
 */

static const uint8_t setDiscArray_7Seg[23][3] PROGMEM =
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
 * Refers to "D7SEG" - 7-segment display.
 * -> resetDiscArray_7Seg[][] - the array contains the addresses of all control outputs corresponding 
 * to the setting of the discs to the "black" side.
 * Each of the "0" or "1" disc statuses requires a different polarity of the current pulse 
 * released into the disc, and thus for each of the statuses we must drive different 
 * controller outputs to achieve the desired effect. 
 * A data frame to flip one disc requires 3 bytes and only two bits are set to "1" the other bits are "0".
 * To flip the entire display, we need to send 3 bytes x 23 discs = 69 bytes of data.
*/
static const uint8_t resetDiscArray_7Seg[23][3] PROGMEM =
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
 * Refers to "D3X1 & D2X1" - 2 and 3-dot display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "color" side.
 */ 
static const uint8_t setDiscArray_3x1[3] PROGMEM =
{
  0b00100001,  
  0b00101000,
  0b00100010
};

/* 
 * Refers to "D3X1 & D2X1" - 2 and 3-dot display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "black" side.
 */ 
static const uint8_t resetDiscArray_3x1[3] PROGMEM =
{
  0b11000000,
  0b01010000,
  0b01000100
};

/* 
 * Refers to "D1X3" - 1x3 display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "color" side.
 */ 
static const uint8_t setDiscArray_1x3[3] PROGMEM =
{
  0b10000010,
  0b10010000,
  0b10100000
};

/* 
 * Refers to "D1X3" - 1x3 display.    
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "black" side.
 */ 
static const uint8_t resetDiscArray_1x3[3] PROGMEM =
{
  0b00000101, 
  0b01000100,
  0b00001100
};

/* 
 * Refers to "D1X7" - 1x7 display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "color" side.
 */ 
static const uint8_t setDiscArray_1x7[7][2] PROGMEM =
{
  {0b00101000, 0b00000000},
  {0b10001000, 0b00000000},
  {0b00001100, 0b00000000},
  {0b00001000, 0b01000000},
  {0b00001000, 0b00000010},
  {0b00001000, 0b00010000},
  {0b00001000, 0b00000001}
}; 

/* 
 * Refers to "D1X7" - 1x7 display.  
 * The array contains the addresses of the control outputs corresponding 
 * to the setting of the discs to the "black" side.
 */ 
static const uint8_t resetDiscArray_1x7[7][2] PROGMEM =
{
  {0b00010001, 0b00000000},
  {0b01000001, 0b00000000},
  {0b00000001, 0b10000000},
  {0b00000011, 0b00000000},
  {0b00000001, 0b00000100},
  {0b00000001, 0b00100000},
  {0b00000001, 0b00001000}
}; 
  
class FlipDisc
{
    public:
        FlipDisc();
        void Pin(uint16_t EN_PIN, uint16_t CH_PIN, uint16_t PL_PIN);
        void Init(uint8_t MOD1, uint8_t MOD2 = 0xFF, uint8_t MOD3 = 0xFF, uint8_t MOD4 = 0xFF, 
                  uint8_t MOD5 = 0xFF, uint8_t MOD6 = 0xFF, uint8_t MOD7 = 0xFF, uint8_t MOD8 = 0xFF);

        void Disc_7Seg(uint8_t module_number, uint8_t disc_number, bool disc_status);
        void Display_7Seg(uint8_t module_number, uint8_t new_data);                                
        void Matrix_7Seg(uint8_t data1, uint8_t data2 = 0xFF, uint8_t data3 = 0xFF, uint8_t data4 = 0xFF, 
                              uint8_t data5 = 0xFF, uint8_t data6 = 0xFF, uint8_t data7 = 0xFF, uint8_t data8 = 0xFF);
                              
        void Disc_2x1(uint8_t module_number, uint8_t dot_number, bool disc_status);
        void Display_2x1(uint8_t module_number, uint8_t disc1 = 0xFF, uint8_t disc2 = 0xFF);

        void Disc_3x1(uint8_t module_number, uint8_t dot_number, bool disc_status);
        void Display_3x1(uint8_t module_number, uint8_t disc1 = 0xFF, uint8_t disc2 = 0xFF, uint8_t disc3 = 0xFF);

        void Disc_1x3(uint8_t module_number, uint8_t discNumber, bool disc_status);
        void Display_1x3(uint8_t module_number, uint8_t disc1 = 0xFF, uint8_t disc2 = 0xFF, uint8_t disc3 = 0xFF);

        void Disc_1x7(uint8_t module_number, uint8_t discNumber, bool disc_status);
        void Display_1x7(uint8_t module_number, uint8_t disc1 = 0xFF, uint8_t disc2 = 0xFF, uint8_t disc3 = 0xFF, 
                         uint8_t disc4 = 0xFF, uint8_t disc5 = 0xFF, uint8_t disc6 = 0xFF, uint8_t disc7 = 0xFF);

        void Delay(uint8_t new_time_delay);
        void Test(void);
        void All(void);
        void Clear(void);
        
    private:
        void FlipDelay(void);
        void SendBlankData(uint8_t module_number, uint8_t module_type, uint8_t data_position);
        void ClearAllOutputs(void);
        void PrepareCurrentPulse(void);
        void ReleaseCurrentPulse(void);
        bool Fuse(uint8_t module_number, uint8_t module_type);
};

extern FlipDisc Flip;

#endif
