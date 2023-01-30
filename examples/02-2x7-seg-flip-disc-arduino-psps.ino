/*----------------------------------------------------------------------------------*
 * A simple example of controlling two 7-segment flip-disc displays                 *
 * Example connection diagram: https://bit.ly/2x7SEG                                * 
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

/* The library <FlipDisc.h> uses SPI to control flip-disc displays. 
The user must remember to connect the display inputs marked: 
- DIN - data in - to the MOSI (SPI) output of the microcontroller, 
- CLK - clock - input of the display to the SCK (SPI).
The displays are connected in series through the built-in connectors, 
only the first display from the left is connected to the Arduino or a dedicated controller.
 
It is very important to connect and declare EN, CH, PL pins. 
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
  /* FlipDisc.Pin() it is most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
  FlipDisc.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* FlipDisc.Init(display1, display2, ... display8); it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - SEG - 7-segment display
  - DOTS - 2x1 or 3x1 dot display
  - FLIP3 - 1x3 display
  - FLIP7 - 1x7 display  */
  FlipDisc.Init(SEG, SEG);
  delay(3000);
}

void loop() 
{
  /* The function is used to test all declared displays - turn on and off all displays */
  FlipDisc.Test();
  delay(3000);

  /* The function is used to set the delay effect between flip discs. 
  The default value without calling the function is 0. Can be called multiple times 
  anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms */
  FlipDisc.Delay(50);

  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(3000);

  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(3000);

  /* An example of calling the functions to display the digit "6" on the first 
  7-Segment display counting from the left and digit 3 on the second display */
  FlipDisc.ToSeg(1, 6);
  FlipDisc.ToSeg(2, 3);
  delay(3000);

  /* A function used to control two displays simultaneously */ 
  FlipDisc.Seg(5, 2);
  delay(3000);
  FlipDisc.Seg(DEG, CEL);
  delay(3000);
  
  /* This function allows you to display numbers and symbols: 0-9, "°","C" , "F", etc.
  Code names for symbols:
  - 8/ALL - Set all discs
  - 10/CLR - Clear Display
  - 11/DEG - "°" - Degree symbol
  - 12/CEL - "C" - Celsius symbol
  - 13/FAH - "F" - Fahrenheit symbol
  - 14/HUM - "H" - Humidity symbol
  - 15/PFH - "%" - Percent first half symbol
  - 16/PSH - "%" - Percent second half symbol
  - 17/UPD - "¯" - Upper dash symbol
  - 18/MID - "-" - Middle dash symbol
  - 19/BTD - "_" - Bottom dash symbol
  - 20/ALD - All three dashes */ 

  FlipDisc.Delay(0);
  
  /* Symbols can be displayed using their code names or numbers */
  for(int symbolNumber = 0; symbolNumber <= 20; symbolNumber++)
  {
    FlipDisc.Seg(symbolNumber, 20 - symbolNumber);
    delay(1000);  
  }
  
  delay(3000);
}
