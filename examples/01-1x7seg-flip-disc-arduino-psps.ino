/*----------------------------------------------------------------------------------*
 * A simple example of controlling a 7-segment flip-disc display                    *
 * Example connection diagram: https://bit.ly/1x7SEG                                * 
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 15 Jan 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *                                                                                  *
 * A dedicated controller or any Arduino board with a power module is required      * 
 * to operate the display:                                                          *
 * 1. Dedicated controller - https://bit.ly/AC1-FD                                  *
 * 2. Or any Arduino board + Pulse Shaper Power Supply - https://bit.ly/PSPS-FD     *                       
 *----------------------------------------------------------------------------------*/

/* The library <FlipDisc.h> uses SPI to control flip-disc display. 
The user must remember to connect the display inputs marked: 
- DIN - data in - to the MOSI (SPI) output of the microcontroller, 
- CLK - clock - input of the display to the SCK (SPI). 
In addition, it is very important to connect and declare EN, CH, PL pins. 
The declaration of DIN (MOSI) and CLK (SCK) is not necessary, 
because the SPI.h library handles the SPI hardware pins. */

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc 

/*
#define EN_PIN  'Set your pin'  // Start & End SPI transfer data
#define CH_PIN  'Set your pin'  // Charging PSPS module - turn ON/OFF
#define PL_PIN  'Set your pin'  // Release the current pulse - turn ON/OFF 
*/

/*
// 1. Pin declaration for a dedicated controller
#define EN_PIN  A7
#define CH_PIN  A2 
#define PL_PIN  A3
*/

// 2. Example pin declaration for Arduino Uno and PSPS module
#define EN_PIN  10
#define CH_PIN  8 
#define PL_PIN  9

void setup() 
{
  /* Flip.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
  Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* Flip.Init(display1, display2, ... display8); it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display  
  Example function call for 8 modules: Flip.Init(D7SEG,D7SEG,D3X1,D7SEG,D7SEG,D3X1,D7SEG,D7SEG); */
  Flip.Init(D7SEG);
  delay(3000);
}

void loop() 
{
  /* The function is used to test all declared displays - turn on and off all displays */
  Flip.Test();
  delay(3000);

  /* The function is used to set the delay effect between flip discs. 
  The default value without calling the function is 0. Can be called multiple times 
  anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms */
  Flip.Delay(50);

  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(3000);

  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(3000);

  Flip.Delay(0);

  /* An example of calling the function to set disc no.19 */
  Flip.Disc_7Seg(1, 19, 1);
  delay(1000);  

/* 0  1  2  3  4
	19           5
	18           6
	17 20 21 22  7
	16           8
	15           9
	14 13 12 11 10 */

  /* Set All discs */
  for(int i = 0; i <= 22; i ++)
  {
	Flip.Disc_7Seg(1, i, 1);
	delay(200);
  }
  
  delay(1000);

  /* Reset disc no.13 */ 
  Flip.Disc_7Seg(1, 13, 0);
  delay(3000);
  
  Flip.Clear();
  delay(1000);

 /* An example of calling the function to display the number 5 
  on the first 7-Segment display counting from the left */
  Flip.Display_7Seg(1, 5);
  delay(3000);

  /* Example function call assuming that we have declared one display 
  and we want to display "F" - Fahrenheit symbol */ 
  Flip.Matrix_7Seg(F);
  delay(3000);
  
  /* 7-Segment displays allow the display of numbers and symbols.
  Symbols can be displayed using their code name or number e.g. 37/DEG - "°" Degree symbol
  The full list of symbols can be found in the FlipDisc.h library repository https://github.com/marcinsaj/FlipDisc
  Code names for symbols:
  - 0-9
  - 1/VLR  - " |" - Vertical line - right
  - 8/ALL  - Set all discs
  - 10/CLR - Clear display
  - 11/A
  - 12/B
  - 13/C
  - 14/D
  - 15/E
  - 16/F
  - 17/G
  - 18/H
  - 19/I
  - 20/J
  - 21/K
  - 22/L
  - 23/M
  - 24/N
  - 25/O
  - 26/P
  - 27/Q
  - 28/R
  - 29/S
  - 30/T
  - 31/U
  - 32/V
  - 33/W
  - 34/X
  - 35/Y
  - 36/Z
  - 37/DEG - "°"  - Degree symbol
  - 37/PFH - "%"  - Percent first half symbol
  - 38/PSH - "%"  - Percent second half symbol
  - 39/HLU - "¯"  - Horizontal line - upper
  - 40/HLM - "-"  - Horizontal line - middle
  - 41/HLL - "_"  - Horizontal line - lower
  - 42/HLT - "="  - Horizontal line - upper & lower
  - 43/HLA - "≡"  - All three lines
  - 40/MIN - "-"  - Minus symbol
  - 44/VLL - "| " - Vertical line - left
  - 1/VLR  - " |" - Vertical line - right
  - 45/VLA - "||" - All Vertical lines */ 
  
  /* Symbols can be displayed using their code names or numbers */
  for(int symbol_number = 0; symbol_number <= 45; symbol_number++)
  {
    Flip.Matrix_7Seg(symbol_number);
    delay(1000);  
  }
  
  delay(3000);
}
