/*----------------------------------------------------------------------------------*
 * A simple example of controlling one 2x6 flip-disc display                        *
 * Example connection diagram: https://bit.ly/1x2x6FDD                              *
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 15 Jan 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *                                                                                  *
 * A dedicated controller or any Arduino board with a power module is required      *
 * to operate the display:                                                          *
 * 1. Binary Clock Controller                                                       *
 * 2. Flip-disc controller - https://bit.ly/AC1-FD                                  *
 * 3. Or any Arduino board + Pulse Shaper Power Supply - https://bit.ly/PSPS-FD     *
 *----------------------------------------------------------------------------------*/

/* The library <FlipDisc.h> uses SPI to control flip-disc displays. 
The user must remember to connect the display inputs marked: 
- DIN - data in - to the MOSI (SPI) output of the microcontroller, 
- CLK - clock - input of the display to the SCK (SPI).
Displays can be connected in series, the DOUT output of the first display 
should be connected to the DIN input of the next one.
 
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
// 1. Pin declaration for a binary clock controller
#define EN_PIN  10
#define CH_PIN  A1 
#define PL_PIN  A0
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
  
  /* Flip.Init(display1, display2, ... display8) it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display
  - D2X6 - 2x6 display
  Example for two D2X6 displays: Flip.Init(D2X6, D2X6); */
  Flip.Init(D2X6);
  delay(3000);
}

void loop() 
{
  // The function is used to turn off (clear) all displays
  Flip.Clear();
  delay(1000);
  
  // The function is used to turn on (set) all discs of all displays
  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000);


/*----------------------------------------------------------------------------------*
 * Flip.Disc_2x6(module_number, disc_number, disc_status)                           *
 * Function allows you to control a selected disc in a 2x6 display.                 *
 * We can control only one disc of the selected display at a time. The first        *
 * argument module_number is the relative number of the display in the series       *
 * of all displays. For example, if we have a combination of D2X6, D7SEG, D2X6,     *
 * then the second D2X6 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D2X6 displays.                                    *
 * -> module_number - relative number of the "D2X6" display                         *
 * -> disc_number - display disc number counting from right to left in each row     *
 * first row 1-6, second row 7-12                                                   *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *    12 11 10  9  8  7                                                             *
 *     6  5  4  3  2  1                                                             *
 *----------------------------------------------------------------------------------*/
  for(int i = 0; i < 2; i++)
  {
    for(int j = 1; j <= 12; j++)
    {
      Flip.Disc_2x6(1, j, 1);
      delay(100);
    }

    delay(1000);

    for(int j = 1; j <= 12; j++)
    {
      Flip.Disc_2x6(1, j, 0);
      delay(100);
    }

    delay(1000);  
  }

/*----------------------------------------------------------------------------------*
 * Display_2x6(module_number, row_number, column_number, disc_status)               *
 * Function allows you to control a selected disc in a 2x6 display.                 *
 * We can control only one disc of the selected display at a time.                  *
 * Addressing selected disc using rows and columns.                                 *
 * The first argument module_number is the relative number of the display           *
 * in the series of all displays. For example, if we have a combination             *
 * of D2X6, D7SEG, D2X6, then the second D2X6 display will have a relative number   *
 * of 2 even though there is a D7SEG display between the D2X6 displays              *
 * -> module_number - relative number of the "D2X6" display                         *
 * -> row_number - display disc row number counting from bottom to top 1-2          *
 * -> column_number - display disc number counting from right to left 1-6           *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *                                                                                  *
 * Rows, columns & discs numbers                                                    *
 *      6  5  4  3  2  1                                                            *
 *  2  12 11 10  9  8  7                                                            *
 *  1   6  5  4  3  2  1                                                            *
 *----------------------------------------------------------------------------------*/

  for(int i = 0; i < 2; i++)
  {
    for(int j = 1; j <= 6; j++)
    {
      for(int k = 1; k <= 2; k++)
      {
        Flip.Display_2x6(1, k, j, 1);
        delay(200);
      }
    }

    delay(1000);

    for(int j = 1; j <= 6; j++)
    {
      for(int k = 1; k <= 2; k++)
      {
        Flip.Display_2x6(1, k, j, 0);
        delay(200);
      }
    }

    delay(1000);
  } 

  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000); 

  for(int i = 0; i < 2; i++)
  {
    for(int j = 1; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 0);}
    for(int j = 2; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 1);}
    delay(1000);
    for(int j = 1; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 1);}
    for(int j = 2; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 0);}
    delay(1000);
  }

  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000);

  for(int i = 0; i < 2; i++)
  {
    for(int j = 1; j <= 6;  j = j+2) {Flip.Disc_2x6(1, j, 0);}
    for(int j = 8; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 0);}
    for(int j = 2; j <= 6;  j = j+2) {Flip.Disc_2x6(1, j, 1);}
    for(int j = 7; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 1);}
    delay(1000);
    for(int j = 1; j <= 6;  j = j+2) {Flip.Disc_2x6(1, j, 1);}
    for(int j = 8; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 1);}
    for(int j = 2; j <= 6;  j = j+2) {Flip.Disc_2x6(1, j, 0);}
    for(int j = 7; j <= 12; j = j+2) {Flip.Disc_2x6(1, j, 0);}
    delay(1000);
  }
}
