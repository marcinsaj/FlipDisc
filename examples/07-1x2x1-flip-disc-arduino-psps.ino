/*----------------------------------------------------------------------------------*
 * A simple example of controlling one 2x1 flip-disc display                        *
 * Example connection diagram: https://bit.ly/1x2x1DOT                              *
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
  Example for two D2X1 displays: Flip.Init(D2X1, D2X1); */
  Flip.Init(D2X1);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(3000);
  
  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(3000);

  Flip.Clear();
  delay(1000);

  /* Function allows you to control a selected disc in a selected 2x1 display. 
  You can control only one disc of the selected display at a time.
  - Flip.Disc_2x1(module_number, disc_number, disc_status);
  The first argument module_number is the relative number of the display in the series of all displays. 
  For example, if we have a combination of D2X1, D7SEG, D2X1, then the second D2X1 display 
  will have a relative number of 2 even though there is a D7SEG display between the D2X1 displays. 
  - module_number - relative number of the D2X1 display
  - disc_number - display disc number counting from top to bottom 1-2
  - disc_status - reset disc "0" or set disc "1" */
  Flip.Disc_2x1(1, 1, 1);  /* Set first disc of the first 2x1 display */
  delay(1000);
  Flip.Disc_2x1(1, 2, 1);  /* Set second disc */
  delay(3000);

  /* Function allows you to control one or two discs of the selected display. 
  The first argument is the relative number "module_number" of the display in the series 
  of all displays. For example, if we have a combination of D2X1, D7SEG, D2X1, then 
  the second D2X1 display will have a relative number of 2 even though there is a D7SEG display 
  between the D2X1 displays. 
  - Flip.Display_2x1(module_number, disc1, disc2);
  - module_number - relative number of the D2X1 display
  - disc1, disc2 - display discs counting from top to bottom 1-2 */
  Flip.Display_2x1(1, 0);       /* Reset first disc of the first 2x1 display */
  delay(1000);
  Flip.Display_2x1(1, 1, 0);    /* Set first disc and reset second disc */
  delay(3000);

  for(int i = 0; i < 5; i++)
  {
    Flip.Display_2x1(1, 0, 1);
    delay(500);
    Flip.Display_2x1(1, 1, 0);
    delay(500);   
  }

  for(int i = 0; i < 10; i++)
  {
    Flip.Disc_2x1(1, 1, 1);
    delay(250);
    Flip.Disc_2x1(1, 2, 1);
    delay(250); 
    
    Flip.Disc_2x1(1, 1, 0);
    delay(250);
    Flip.Disc_2x1(1, 2, 0);
    delay(250); 
  }
}
