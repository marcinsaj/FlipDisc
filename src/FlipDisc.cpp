/*----------------------------------------------------------------------------------*
 * FlipDisc.cpp - Arduino library for flip-disc displays.                           *
 * This library is intended for use with the displays designed by                   *
 * www.Flipo.io - Marcin Saj.                                                       *
 *                                                                                  *
 * The MIT License                                                                  *
 * Marcin Saj 15 Jan 2023                                                           *
 * https://github.com/marcinsaj/FlipDisc                                            *
 *----------------------------------------------------------------------------------*/

#include "FlipDisc.h"

/* 
 * Declaration of the flip-disc display enable pin   
 * EN_PIN - the pin serves as a latch for shift registers on which 
 * the controllers built into the displays are based.
 */
uint16_t _EN_PIN = 0;       // Start & End SPI transfer data

/*
 * Declaration of the Pulse Shaper Power Supply Module control pins
 */
uint16_t _CH_PIN  = 0;      // Charging PSPS module - turn ON/OFF
uint16_t _PL_PIN  = 0;      // Release the current pulse - turn ON/OFF

uint8_t flip_delay = 0;     // Variable for the delay effect between flip discs
uint32_t time_now = 0;      // Variable for the millis() function
        
/* 
 * 2-dimensional array with 3 columns.
 * The first column lists all connected displays "module_type_column",
 * the second column is the number of data bytes required to control the display "number_bytes_column",
 * the third column is a number defining the relative position of the modules
 * in relation to each other and for each type separately "module_relative_position_column". 
 */
uint8_t moduleInitArray[8][3];

/* 
 *  An array of defined display names:
 * -> D7SEG - 7-Segment flip-disc display
 * -> D2X1 - 2x1 flip-disc display
 * -> D3X1 - 3x1 flip-disc display
 * -> D1X3 - 1x3 flip-disc display
 * -> D1X7 - 1x7 flip-disc display
 * -> D2X6 - 2x6 flip-disc display 
 * -> D3X3 - 3x3 flip-disc display
 * -> D3X4 - 3x4 flip-disc display  
 * -> D3X5 - 3x5 flip-disc display
 */
static const uint8_t moduleTypeArray[] PROGMEM = {D7SEG, D2X1, D3X1, D1X3, D1X7, D2X6, D3X3, D3X4, D3X5};

/*
 * Total length of data frame for all displays.
 * We can only control one disc out of all connected display modules at a time. 
 * Despite the fact that we only need two bits to control one disc, we have to send 
 * a data frame of a length equal to the sum of the data for all displays each time.
 * If there is no display module declaration, each empty module up to eight 
 * is supplemented with 3 bytes (largest display requires 3 bytes of data). 
 * If the user does not declare the connected display, incorrect operation 
 * or damage to the display may occur (thats why these 3 bytes).
 */
uint8_t number_all_bytes = 0; 

/*----------------------------------------------------------------------------------*
 * Constructor                                                                      *
 *----------------------------------------------------------------------------------*/ 
FlipDisc::FlipDisc()
{
  /* Do nothing */	
}
    
/*----------------------------------------------------------------------------------*
 * Initialization function for a series of displays. The function has 1 default     *
 * argument and 7 optional arguments. The function also prepares SPI.               *
 * Correct initialization requires code names of the serially connected displays.   *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Init(uint8_t MOD1, uint8_t MOD2 /* = 0xFF */, uint8_t MOD3 /*= 0xFF */, 
                                  uint8_t MOD4 /* = 0xFF */, uint8_t MOD5 /*= 0xFF */, 
                                  uint8_t MOD6 /* = 0xFF */, uint8_t MOD7 /*= 0xFF */, 
                                  uint8_t MOD8 /* = 0xFF */)
{  
  // SPI initialization 
  SPI.begin();

  // First charging Pulse Shaper Power Supply module after power up the device
  PrepareCurrentPulse();

  // Saving a list of displays to the array
  moduleInitArray[0][module_type_column] = MOD1;
  moduleInitArray[1][module_type_column] = MOD2;
  moduleInitArray[2][module_type_column] = MOD3;
  moduleInitArray[3][module_type_column] = MOD4;
  moduleInitArray[4][module_type_column] = MOD5;
  moduleInitArray[5][module_type_column] = MOD6;
  moduleInitArray[6][module_type_column] = MOD7;
  moduleInitArray[7][module_type_column] = MOD8;  
  
/*
 * module_relative_position variable
 * for example, if there is a D7SEG, D3X1, D7SEG, D7SEG, D3X1, D1X3 in a series
 * of displays, then the relative positions will be 1, 1, 2, 3, 2, 1.
 * Each type of display is counted separately.
 * In simple terms, it can be presented as a separate list for each
 * type of display and numbered starting from 1. Determining
 * the relative position of the display is used to simplify the display
 * handling functions.
 */
  uint8_t module_relative_position = 0;
  
  uint8_t module_type = 0;
  uint8_t module_number_types = sizeof(moduleTypeArray);

  // For all types of displays
  for(int i = 0; i < module_number_types; i++)
  {
    // The initial value of the relative position for each type of the display
    module_relative_position = 0;
    // Reading the first type of display to check
    module_type = pgm_read_byte(&moduleTypeArray[i]); 
    
    // For the selected display type, search the entire list of serially connected displays
    for(int j = 0; j < 8; j++) 
    {     
      // If the selected display type is found in the list 
      // then the relative position is incremented and stored in the array
      if(moduleInitArray[j][module_type_column] == module_type) 
      {
        module_relative_position = module_relative_position + 1;   
        moduleInitArray[j][module_relative_position_column] = module_relative_position;
      }
    }
  }
  
/*
 * Extracting the number of data bytes of each display type, the number of bytes 
 * determines the size of the control frame. Required by the displays architecture,
 * which is based on shift registers.
 * If the user does not declare the connected display, incorrect operation or
 * damage to the display may occur. Therefore, if there is no display module
 * declaration, each empty module up to eight is supplemented with 3 bytes.
 * We can only handle one disc from the entire display series at a time, so it is
 * very important where in the data stream to put the control bits for the selected
 * disc. In fact, with a data frame of a few or a dozen bytes, only two bits are
 * set to "1" the rest of the data is "0".
 */
  uint8_t number_bytes = 0;
  
  for(int i = 0; i < 8; i++)
  {
    switch (moduleInitArray[i][module_type_column]) 
    {
      case D7SEG:
        number_bytes = 3;
        break;

      /* D3X1 = D2X1 - are the same */
      case D3X1:
        number_bytes = 1;
        break; 

      case D1X3:
        number_bytes = 1;
        break;
        
      case D1X7:
        number_bytes = 2;
        break;
		
      case D2X6:
        number_bytes = 2;
        break; 			

      case D3X3:
        number_bytes = 2;
        break;   		

      case D3X4:
        number_bytes = 2;
        break;  

      case D3X5:
        number_bytes = 2;
        break;  
      
      case NONE:
        number_bytes = 3;
        break;   
        
      default:
        number_bytes = 3;
        break;
    }
    
    // Saving data about the number of data bytes required by the module
    moduleInitArray[i][number_bytes_column] = number_bytes;

    // Total length of data frame for all displays.
    number_all_bytes = number_all_bytes + number_bytes; 
  }
}

/*----------------------------------------------------------------------------------*
 * Function to control up to eight 7-Segment displays.                              *
 * The first argument is the default and the others are optional.                   *
 * This function allows you to display numbers and symbols: 0-9, "°", "C", "F", etc.*
 *----------------------------------------------------------------------------------*/
void FlipDisc::Matrix_7Seg(uint8_t data1, uint8_t data2 /* = 0xFF */, uint8_t data3 /* = 0xFF */, 
                                          uint8_t data4 /* = 0xFF */, uint8_t data5 /* = 0xFF */, 
                                          uint8_t data6 /* = 0xFF */, uint8_t data7 /* = 0xFF */, 
                                          uint8_t data8 /* = 0xFF */)
{ 
  // Saving a list of data to the array
  uint8_t newDataArray[8] = {data1, data2, data3, data4, data5, data6, data7, data8};
  
  for(int i = 0; i < 8; i++)
  {   
    // Call the function to handle the display only if there is data for it
    if(newDataArray[i] != 0xFF) Display_7Seg(i + 1, newDataArray[i]);
  }
}

/*----------------------------------------------------------------------------------*
 * The function allows you to control one 7-Segment display.                        *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D7SEG, D3X1, D7SEG then*
 * the second D7SEG display will have a relative number of 2 even though there      *
 * is a D3X1 display between the D7SEG displays.                                    *
 * -> module_number - relative number of the "D7SEG" display                        *
 * -> data.                                                                         *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists of 23 discs. The displayArray_7Seg[][] array contains       *
 * information about all disc statuses for the symbol we want to display.           *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * Disc statuses "0" and "1" correspond to different control outputs.               *
 * The list of information about all control outputs for corresponding              *
 * disc statuses of all discs and the currently selected digit/symbol to be         *
 * displayed are contained in two tables:                                           *
 * -> setDiscArray_7Seg[][] - "1"                                                   *
 * -> resetDiscArray_7Seg[][] - "0"                                                 *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_7Seg(uint8_t module_number, uint8_t new_data)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D7SEG) == true) return;
  
  bool disc_status = 0;
  uint8_t bit_number = 0;
  uint8_t current_column = 0;
  uint8_t current_row = new_data;
  
  // The display is built with 23 independently controlled flip-discs
  for(int disc_number = 0; disc_number < 23; disc_number++)
  { 
   /*
    * bit_number can only be in the range 0-7, so we must make sure that 
    * when changing the columns/bytes to read, start counting the bits again from 0.
    */   
    if(disc_number < 8) {bit_number = disc_number; current_column = 0;}
    if((disc_number >= 8) && (disc_number < 16)) {bit_number = disc_number - 8; current_column = 1;}
    if(disc_number >= 16) {bit_number = disc_number - 16; current_column = 2;}
    
   /*
    * 1 - Read one byte from location: displayArray_7Seg[current_row][current_column]
    * 2 - Shift byte from 0 to 7 bits to the right
    * 3 - Extract the bit that corresponds to the state of the selected display disc
    */ 
    disc_status = ((pgm_read_byte(&displayArray_7Seg[current_row][current_column])) >> (bit_number)) & 0b00000001;

    // Flip one selected disc
    Disc_7Seg(module_number, disc_number, disc_status);
  }
  // Finally, clear all display outputs
  ClearAllOutputs();
}


/*----------------------------------------------------------------------------------*
 * The function allows you to control one selected disc of 7-Segment display.       *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D7SEG, D3X1, D7SEG then*
 * the second D7SEG display will have a relative number of 2 even though there      *
 * is a D3X1 display between the D7SEG displays. The second argument disc_number    *
 * is the number of selected disc 0-22 of the 7-Segment display.                    *
 * The third argument is the status of the selected disc                            *
 * -> module_number - relative number of the "D7SEG" display                        *
 * -> disc_number - there are 23 discs in 7-Segment display 0-22                    *
 * -> disc_status - reset disc "0" or set disc "1"                                  *                                            
 *                                                                                  *
 *  0  1  2  3  4                                                                   *
 * 19           5                                                                   *
 * 18           6                                                                   *
 * 17 20 21 22  7                                                                   *
 * 16           8                                                                   *
 * 15           9                                                                   *
 * 14 13 12 11 10                                                                   *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists of 23 discs.                                                *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * Disc statuses "0" and "1" correspond to different control outputs.               *
 * The list of information about all control outputs for corresponding              *
 * disc statuses of all discs are contained in two tables:                          *
 * -> setDiscArray_7Seg[][] - "1"                                                   *
 * -> resetDiscArray_7Seg[][] - "0"                                                 *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_7Seg(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
    // Start of SPI data transfer
    digitalWrite(_EN_PIN, LOW);

   /* 
    * Send blank data "0" to all control outputs of the other displays BEFORE 
    * sending control data to the selected display.
    * Detailed information in the function description SendBlankData().
    */
    SendBlankData(module_number, D7SEG, BEFORE);
    
   /*
    * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
    * the other side "0" - black. 
    * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
    * released into the disc, and thus for each of the statuses we must drive different 
    * controller outputs to achieve the desired effect. 
    * The list of information about the statuses of all discs for the entire display 
    * and the currently selected digit/symbol to be displayed is contained in two tables:
    * -> setDiscArray_7Seg[][] - "1" 
    * -> resetDiscArray_7Seg[][] - "0"
    * The arrays contains the addresses of all control outputs corresponding to the setting 
    * of the discs to the "color" side or "black" side.
    * Each separate display disc requires 3 bytes of data to be transferred. 
    * To flip the entire display, we need to send 3 bytes x 23 discs = 69 bytes of data
    */
    
    for(int byte_number = 0; byte_number < 3; byte_number++)
    {
      if(disc_status == 0) SPI.transfer(pgm_read_byte(&setDiscArray_7Seg[disc_number][byte_number]));
      if(disc_status == 1) SPI.transfer(pgm_read_byte(&resetDiscArray_7Seg[disc_number][byte_number]));
    }

   /* 
    * Send blank data "0" to all control outputs of the other displays AFTER 
    * sending control data to the selected display.
    * Detailed information in the function description SendBlankData().
    */
    SendBlankData(module_number, D7SEG, AFTER);

    // End of SPI data transfer
    digitalWrite(_EN_PIN, HIGH);
    
    // Release of 1ms current pulse
    ReleaseCurrentPulse();  
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a selected dot display.        *
 * We can control only one dot of the selected display at a time.                   *
 * The first argument module_number is the relative number of the display in        *
 * the series of all displays. For example, if we have a combination                *
 * of D3X1, D7SEG, D3X1, then the second D3X1 display will have a relative number   * 
 * of 2 even though there is a D7SEG display between the D3X1 displays.             *
 * -> module_number - relative number of the "D3X1" display                         *
 * -> disc_number - display disc number counting from top to bottom 1-3             *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_3x1(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X1) == true) return;
  
  uint8_t newDiscArray[3];
  
  /*
   * disc_number - display dot number counting from top to bottom 1, 2, 3
   * The array row numbers newDiscArray[] start at 0 so we need to subtract 1 (i-1)
   * If we assign the value 0xFF to discs, the Display_3x1() function will ignore these discs
   */
  for(int i = 1; i <= 3; i++)
  {
    if(disc_number == i) newDiscArray[i-1] = disc_status;
    else newDiscArray[i-1] = 0xFF; 
  }
  
  // Call the function to flip the dot (only one disc)
  Display_3x1(module_number, newDiscArray[0], newDiscArray[1], newDiscArray[2]);

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();  
}

/*----------------------------------------------------------------------------------*
 * Same functionality as Disc_3x1()function but to handle display 2x1               *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_2x1(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
  Disc_3x1(module_number, disc_number, disc_status);    
}

/*----------------------------------------------------------------------------------*
 * The function allows you to control 2x1 or 3x1 display.                           *
 * You can control one, two or three discs of the selected display at a time.       *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D3X1, D7SEG, D3X1,     * 
 * then the second D3X1 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D3X1 displays.                                    *
 * -> module_number - relative number of the "D3X1" display                         *
 * -> disc1, disc2, disc3.                                                          *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists of 2 or 3 discs.                                            *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * The list of information about control outputs for corresponding discs            *
 * to be displayed are contained in two tables:                                     *
 * -> setDiscArray_3x1[] - "1"                                                      *
 * -> resetDiscArray_3x1[] - "0"                                                    *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_3x1(uint8_t module_number, uint8_t disc1 /* = 0xFF */, uint8_t disc2 /* = 0xFF */, uint8_t disc3 /* = 0xFF */)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X1) == true) return;
  
  // Saving a list of dot statuses to the array
  uint8_t newDiscArray[3] = {disc1, disc2, disc3};

  // 3 D3X1 - 3 loops
  for(int disc = 0; disc < 3; disc++)
  {  
    // Check if we have new data for dot. 0xFF - no data
    if(newDiscArray[disc] != 0xFF)
    {
      // Start of SPI data transfer
      digitalWrite(_EN_PIN, LOW);

     /* 
      * Send blank data "0" to all control outputs of the other displays BEFORE 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D3X1, BEFORE);

     /*
      * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
      * the other side "0" - black. 
      * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
      * released into the disc, and thus for each of the statuses we must drive different 
      * controller outputs to achieve the desired effect. 
      * The list of information about the statuses of all discs for the display 
      * and the currently selected dot to be displayed is contained in two tables:
      * -> setDiscArray_3x1[] - "1" 
      * -> resetDiscArray_3x1[] - "0"
      * Each separate display disc requires 1 byte of data to be transferred. 
      * To flip all 3 discs, we need to send 3 bytes of data.
      */
      if(newDiscArray[disc] == 1) SPI.transfer(pgm_read_byte(&setDiscArray_3x1[disc]));
      if(newDiscArray[disc] == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_3x1[disc]));
      
     /* 
      * Send blank data "0" to all control outputs of the other displays AFTER 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D3X1, AFTER);

      // End of SPI data transfer
      digitalWrite(_EN_PIN, HIGH);

      // Release of 1ms current pulse 
      ReleaseCurrentPulse();
    }  
  }

  // Finally, clear all display outputs
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * Same functionality as Display_3x1()function but to handle only two discs         *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_2x1(uint8_t module_number, uint8_t disc1 /* = 0xFF */, uint8_t disc2 /* = 0xFF */)
{
  Display_3x1(module_number, disc1, disc2);
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control selected disc in a 1x3 display.                   *
 * We can control only one disc of the selected display at a time.                  *
 * The first argument module_number is the relative number of the display in        *
 * the series of all displays. For example, if we have a combination                *
 * of D1X3, D7SEG, D1X3, then the second D1X3 display will have a relative number   *
 * of 2 even though there is a D7SEG display between the D1X3 displays.             *
 * -> module_number - relative number of the "D1X3" display                         *
 * -> disc_number - display disc number counting from left to right 1-3             *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_1x3(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D1X3) == true) return;
  
  uint8_t newDiscArray[3];
  
  /*
   * disc_number - counting from left to right 1, 2, 3
   * The array row numbers newDiscArray[] start at 0 so we need to subtract 1 (i-1)
   * If we assign the value 0xFF to discs, the Display_1x3() function will ignore these discs
   */
  for(int i = 1; i <= 3; i++)
  {
    if(disc_number == i) newDiscArray[i-1] = disc_status;
    else newDiscArray[i-1] = 0xFF; 
  }
  
  // Call the function to flip the disc (only one disc)
  Display_1x3(module_number, newDiscArray[0], newDiscArray[1], newDiscArray[2]);

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * The function allows you to control 1x3 display.                                  *
 * We can control one, two or three discs of the selected display at a time.        *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D1X3, D7SEG, D1X3,     *
 * then the second D1X3 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D1X3 displays.                                    *
 * -> module_number - relative number of the "D1X3" display                         *
 * -> disc1, disc2, disc3.                                                          *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists 3 discs.                                                    *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * The list of information about control outputs for corresponding discs            *
 * to be displayed are contained in two tables:                                     *
 * -> setDisc_1x3[] - "1"                                                           *
 * -> resetDisc_1x3[] - "0"                                                         *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_1x3(uint8_t module_number, uint8_t disc1 /* = 0xFF */, uint8_t disc2 /* = 0xFF */, uint8_t disc3 /* = 0xFF */)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D1X3) == true) return;
  
  // Saving a list of disc statuses to the array
  uint8_t newDiscArray[3]= {disc1, disc2, disc3};

  // 3 discs - 3 loops
  for(int disc = 0; disc < 3; disc++)
  {  
    // Check if we have new data for disc. 0xFF - no data
    if(newDiscArray[disc] != 0xFF)
    {
      // Start of SPI data transfer
      digitalWrite(_EN_PIN, LOW);

     /* 
      * Send blank data "0" to all control outputs of the other displays BEFORE 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D1X3, BEFORE);

     /*
      * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
      * the other side "0" - black. 
      * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
      * released into the disc, and thus for each of the statuses we must drive different 
      * controller outputs to achieve the desired effect. 
      * The list of information about the statuses of all discs for the display 
      * and the currently selected dot to be displayed is contained in two tables:
      * -> setDisc_1x3[] - "1" 
      * -> resetDisc_1x3[] - "0"
      * Each separate display disc requires 1 byte of data to be transferred. 
      * To flip all 3 discs, we need to send 3 bytes of data.
      */
      if(newDiscArray[disc] == 1) SPI.transfer(pgm_read_byte(&setDiscArray_1x3[disc]));
      if(newDiscArray[disc] == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_1x3[disc]));
      
     /* 
      * Send blank data "0" to all control outputs of the other displays AFTER 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D1X3, AFTER);

      // End of SPI data transfer
      digitalWrite(_EN_PIN, HIGH);

      // Release of 1ms current pulse 
      ReleaseCurrentPulse();
    }  
  }

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 1x7 display.                 *
 * We can control only one disc of the selected display at a time. The first        *
 * argument module_number is the relative number of the display in the series       *
 * of all displays. For example, if we have a combination of D1X7, D7SEG, D1X7,     *
 * then the second D1X7 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D1X7 displays.                                    *
 * -> module_number - relative number of the "D1X7" display                         *
 * -> disc_number - display disc number counting from left to right 1-7             *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_1x7(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D1X7) == true) return;
  
  uint8_t newDiscArray[7];
  
 /*
  * disc_number - counting from left to right 1, 2,...7
  * The array row numbers newDiscArray[] start at 0 so we need to subtract 1 (i-1)
  * If we assign the value 0xFF to discs, the Display_1x7() function will ignore these discs
  */
  for(int i = 1; i <= 7; i++)
  {
    if(disc_number == i) newDiscArray[i-1] = disc_status;
    else newDiscArray[i-1] = 0xFF; 
  }
  
  // Call the function to flip the disc (only one disc)
  Display_1x7(module_number, newDiscArray[0], newDiscArray[1], newDiscArray[2],
              newDiscArray[3], newDiscArray[4], newDiscArray[5], newDiscArray[6]);

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * The function allows you to control 1x7 display.                                  *
 * We can control 7 discs of the selected display at a time.                        *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D1X7, D7SEG, D1X7,     *
 * then the second D1X7 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D1X7 displays.                                    *
 * -> module_number - relative number of the "D1X7" display                         *
 * -> disc1, disc2, disc3, disc4, disc5, disc6, disc7.                              *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists 7 discs.                                                    *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * The list of information about control outputs for corresponding discs            *
 * to be displayed are contained in two tables:                                     *
 * -> setDiscArray_1x7[] - "1"                                                      *
 * -> resetDiscArray_1x7[] - "0"                                                    *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_1x7(uint8_t module_number, uint8_t disc1 /* = 0xFF */, uint8_t disc2 /* = 0xFF */, uint8_t disc3 /* = 0xFF */,
                           uint8_t disc4 /* = 0xFF */,  uint8_t disc5 /* = 0xFF */, uint8_t disc6 /* = 0xFF */, uint8_t disc7 /* = 0xFF */)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D1X7) == true) return;
  
  // Saving a list of disc statuses to the array
  uint8_t newDiscArray[7] = {disc1, disc2, disc3, disc4, disc5, disc6, disc7};

  // 7 discs - 7 loops
  for(int disc = 0; disc < 7; disc++)
  {  
    // Check if we have new data for disc. 0xFF - no data
    if(newDiscArray[disc] != 0xFF)
    {
      // Start of SPI data transfer
      digitalWrite(_EN_PIN, LOW);

     /* 
      * Send blank data "0" to all control outputs of the other displays BEFORE 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D1X7, BEFORE);

     /*
      * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
      * the other side "0" - black. 
      * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
      * released into the disc, and thus for each of the statuses we must drive different 
      * controller outputs to achieve the desired effect. 
      * The list of information about the statuses of all discs for the display 
      * and the currently selected dot to be displayed is contained in two tables:
      * -> setDiscArray_1x7[] - "1" 
      * -> resetDiscArray_1x7[] - "0"
      * Each separate display disc requires 2 byte of data to be transferred. 
      * To flip all 7 discs, we need to send 14 bytes of data.
      */
      for(int byte_number = 0; byte_number < 2; byte_number++)
      {
        if(newDiscArray[disc] == 1) SPI.transfer(pgm_read_byte(&setDiscArray_1x7[disc][byte_number]));
        if(newDiscArray[disc] == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_1x7[disc][byte_number]));
      }
     /* 
      * Send blank data "0" to all control outputs of the other displays AFTER 
      * sending control data to the selected display.
      * Detailed information in the function description SendBlankData().
      */
      SendBlankData(module_number, D1X7, AFTER);

      // End of SPI data transfer
      digitalWrite(_EN_PIN, HIGH);

      // Release of 1ms current pulse 
      ReleaseCurrentPulse();
    }  
  }

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
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
void FlipDisc::Disc_2x6(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D2X6) == true) return;

  disc_number = disc_number - 1;
	
  // Start of SPI data transfer
  digitalWrite(_EN_PIN, LOW);

 /* 
  * Send blank data "0" to all control outputs of the other displays BEFORE 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D2X6, BEFORE);

 /*
  * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
  * the other side "0" - black. 
  * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
  * released into the disc, and thus for each of the statuses we must drive different 
  * controller outputs to achieve the desired effect. 
  * The list of information about the statuses of all discs for the display 
  * and the currently selected dot to be displayed is contained in two tables:
  * -> setDiscArray_2x6[] - "1" 
  * -> resetDiscArray_2x6[] - "0"
  * Each separate display disc requires 2 byte of data to be transferred. 
  * To flip all 12 discs, we need to send 24 bytes of data.
  */
  for(int byte_number = 0; byte_number < 2; byte_number++)
  {
	if(disc_status == 1) SPI.transfer(pgm_read_byte(&setDiscArray_2x6[disc_number][byte_number]));
	if(disc_status == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_2x6[disc_number][byte_number]));
  }
   
 /* 
  * Send blank data "0" to all control outputs of the other displays AFTER 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D2X6, AFTER);

  // End of SPI data transfer
  digitalWrite(_EN_PIN, HIGH);

  // Release of 1ms current pulse 
  ReleaseCurrentPulse();

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
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
 *     6  5  4  3  2  1                                                             *
 *    12 11 10  9  8  7                                                             *
 *     6  5  4  3  2  1                                                             *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_2x6(uint8_t module_number, uint8_t row_number, uint8_t column_number, bool disc_status)
{
  // Based on the row (1-2) and column (1-6) disc address, we determine the disc number 1-12
  uint8_t disc_number = (row_number - 1) * 6 + column_number;	
  
  Disc_2x6(module_number, disc_number, disc_status);
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 3x3 display.                 *
 * We can control only one disc of the selected display at a time. The first        *
 * argument module_number is the relative number of the display in the series       *
 * of all displays. For example, if we have a combination of D3X3, D7SEG, D3X3,     *
 * then the second D3X3 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D3X3 displays.                                    *
 * -> module_number - relative number of the "D3X3" display                         *
 * -> disc_number - display disc number counting from left to right in each row     *
 * first row 1-3, second row 4-6, third row 7-9                                     *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *	7  8  9                                                                     *
 *	4  5  6                                                                     *
 *	1  2  3                                                                     *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_3x3(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X3) == true) return;

  disc_number = disc_number - 1;
	
  // Start of SPI data transfer
  digitalWrite(_EN_PIN, LOW);

 /* 
  * Send blank data "0" to all control outputs of the other displays BEFORE 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X3, BEFORE);

 /*
  * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
  * the other side "0" - black. 
  * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
  * released into the disc, and thus for each of the statuses we must drive different 
  * controller outputs to achieve the desired effect. 
  * The list of information about the statuses of all discs for the display 
  * and the currently selected dot to be displayed is contained in two tables:
  * -> setDiscArray_3x3[] - "1" 
  * -> resetDiscArray_3x3[] - "0"
  * Each separate display disc requires 2 byte of data to be transferred. 
  * To flip all 9 discs, we need to send 18 bytes of data.
  */
  for(int byte_number = 0; byte_number < 2; byte_number++)
  {
	if(disc_status == 1) SPI.transfer(pgm_read_byte(&setDiscArray_3x3[disc_number][byte_number]));
	if(disc_status == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_3x3[disc_number][byte_number]));
  }
   
 /* 
  * Send blank data "0" to all control outputs of the other displays AFTER 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X3, AFTER);

  // End of SPI data transfer
  digitalWrite(_EN_PIN, HIGH);

  // Release of 1ms current pulse 
  ReleaseCurrentPulse();

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 3x3 display.                 *
 * We can control only one disc of the selected display at a time.                  *
 * Addressing selected disc using rows and columns.                                 *
 * The first argument module_number is the relative number of the display           *
 * in the series of all displays. For example, if we have a combination             *
 * of D3X3, D7SEG, D3X3, then the second D3X3 display will have a relative number   *
 * of 2 even though there is a D7SEG display between the D3X3 displays              *
 * -> module_number - relative number of the "D3X3" display                         *
 * -> row_number - display disc row number counting from bottom to top 1-3          *
 * -> column_number - display disc number counting from left to right 1-3           *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *                                                                                  *
 * Rows, columns & discs numbers                                                    *
 *    1  2  3                                                                       *
 * 3  7  8  9                                                                       *
 * 2  4  5  6                                                                       *
 * 1  1  2  3                                                                       *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_3x3(uint8_t module_number, uint8_t row_number, uint8_t column_number, bool disc_status)
{
  // Based on the row (1-3) and column (1-3) disc address, we determine the disc number 1-9
  uint8_t disc_number = (row_number - 1) * 3 + column_number;	
  
  Disc_3x3(module_number, disc_number, disc_status);
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 3x4 display.                 *
 * We can control only one disc of the selected display at a time. The first        *
 * argument module_number is the relative number of the display in the series       *
 * of all displays. For example, if we have a combination of D3X4, D7SEG, D3X4,     *
 * then the second D3X4 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D3X4 displays.                                    *
 * -> module_number - relative number of the "D3X4" display                         *
 * -> disc_number - display disc number counting from left to right in each row     *
 * first row 1-3, second row 4-6, third row 7-9, four row 10-12                     *
 * -> disc_status - reset disc "0" or set disc "1"                                  *   
 *	10 11 12                                                                    * 
 *	7  8  9                                                                     * 
 *	4  5  6                                                                     * 
 *	1  2  3                                                                     * 
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_3x4(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X4) == true) return;

  disc_number = disc_number - 1;
	
  // Start of SPI data transfer
  digitalWrite(_EN_PIN, LOW);

 /* 
  * Send blank data "0" to all control outputs of the other displays BEFORE 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X4, BEFORE);

 /*
  * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
  * the other side "0" - black. 
  * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
  * released into the disc, and thus for each of the statuses we must drive different 
  * controller outputs to achieve the desired effect. 
  * The list of information about the statuses of all discs for the display 
  * and the currently selected dot to be displayed is contained in two tables:
  * -> setDiscArray_3x4[] - "1" 
  * -> resetDiscArray_3x4[] - "0"
  * Each separate display disc requires 2 byte of data to be transferred. 
  * To flip all 7 discs, we need to send 14 bytes of data.
  */
  for(int byte_number = 0; byte_number < 2; byte_number++)
  {
    if(disc_status == 1) SPI.transfer(pgm_read_byte(&setDiscArray_3x4[disc_number][byte_number]));
    if(disc_status == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_3x4[disc_number][byte_number]));
  }
   
 /* 
  * Send blank data "0" to all control outputs of the other displays AFTER 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X4, AFTER);

  // End of SPI data transfer
  digitalWrite(_EN_PIN, HIGH);

  // Release of 1ms current pulse 
  ReleaseCurrentPulse();

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 3x4 display.                 *
 * We can control only one disc of the selected display at a time.                  *
 * Addressing selected disc using rows and columns.                                 *
 * The first argument module_number is the relative number of the display           *
 * in the series of all displays. For example, if we have a combination             *
 * of D3X4, D7SEG, D3X4, then the second D3X4 display will have a relative number   *
 * of 2 even though there is a D7SEG display between the D3X4 displays              *
 * -> module_number - relative number of the "D3X4" display                         *
 * -> row_number - display disc row number counting from bottom to top 1-4          *
 * -> column_number - display disc number counting from left to right 1-3           *
 * -> disc_status - reset disc "0" or set disc "1"                                  *
 *                                                                                  *
 * Rows, columns & discs numbers                                                    *
 *    1  2  3                                                                       *
 * 4  10 11 12                                                                      *
 * 3  7  8  9                                                                       *
 * 2  4  5  6                                                                       *
 * 1  1  2  3                                                                       *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_3x4(uint8_t module_number, uint8_t row_number, uint8_t column_number, bool disc_status)
{
  // Based on the row (1-4) and column (1-3) disc address, we determine the disc number 1-12
  uint8_t disc_number = (row_number - 1) * 3 + column_number;	
  
  Disc_3x4(module_number, disc_number, disc_status);
}

/*----------------------------------------------------------------------------------*
 * The function allows you to control one 3x5 display.                              *
 * The first argument is the relative number of the display in the series           *
 * of all displays. For example, if we have a combination of D3X5, D3X1, D3X5 then  *
 * the second D3X5 display will have a relative number of 2 even though there       *
 * is a D3X1 display between the D3X5 displays.                                     *
 * -> module_number - relative number of the "D7SEG" display                        *
 * -> data.                                                                         *
 *                                                                                  *
 * Brief:                                                                           *
 * The display consists of 15 discs. The displayArray_3x5[][] array contains        *
 * information about all disc statuses for the symbol we want to display.           *
 * To flip a selected disc, we need to know the corresponding control outputs.      *
 * Disc statuses "0" and "1" correspond to different control outputs.               *
 * The list of information about all control outputs for corresponding              *
 * disc statuses of all discs and the currently selected digit/symbol to be         *
 * displayed are contained in two tables:                                           *
 * -> setDiscArray_3x5[][] - "1"                                                    *
 * -> resetDiscArray_3x5[][] - "0"                                                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Display_3x5(uint8_t module_number, uint8_t new_data)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X5) == true) return;
  
  bool disc_status = 0;
  uint8_t bit_number = 0;
  uint8_t current_column = 0;
  uint8_t current_row = new_data;
  
  // The display is built with 15 independently controlled flip-discs
  for(int disc_number = 0; disc_number < 15; disc_number++)
  { 
   /*
    * bit_number can only be in the range 0-7, so we must make sure that 
    * when changing the columns/bytes to read, start counting the bits again from 0.
    */   
    if(disc_number <   8) {bit_number = disc_number; current_column = 0;}
    if(disc_number >=  8) {bit_number = disc_number - 8; current_column = 1;}
    
   /*
    * 1 - Read one byte from location: displayArray_3x5[current_row][current_column]
    * 2 - Shift byte from 0 to 7 bits to the right
    * 3 - Extract the bit that corresponds to the state of the selected display disc
    */ 
    disc_status = ((pgm_read_byte(&displayArray_3x5[current_row][current_column])) >> (bit_number)) & 0b00000001;

    // Flip one selected disc
    Disc_3x5(module_number, disc_number + 1, disc_status);
  }
  // Finally, clear all display outputs
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * Function to control up to eight 3x5 displays.                                    *
 * The first argument is the default and the others are optional.                   *
 * This function allows you to display numbers and symbols: 0-9, "C", "F", etc.     *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Matrix_3x5(uint8_t data1, uint8_t data2 /* = 0xFF */, uint8_t data3 /* = 0xFF */, 
                                         uint8_t data4 /* = 0xFF */, uint8_t data5 /* = 0xFF */, 
                                         uint8_t data6 /* = 0xFF */, uint8_t data7 /* = 0xFF */, 
                                         uint8_t data8 /* = 0xFF */)
{ 
  // Saving a list of data to the array
  uint8_t newDataArray[8] = {data1, data2, data3, data4, data5, data6, data7, data8};
  
  for(int i = 0; i < 8; i++)
  {   
    // Call the function to handle the display only if there is data for it
    if(newDataArray[i] != 0xFF) Display_3x5(i + 1, newDataArray[i]);
  }
}

/*----------------------------------------------------------------------------------*
 * Function allows you to control a selected disc in a 3x5 display.                 *
 * We can control only one disc of the selected display at a time. The first        *
 * argument module_number is the relative number of the display in the series       *
 * of all displays. For example, if we have a combination of D3X5, D7SEG, D3X5,     *
 * then the second D3X5 display will have a relative number of 2 even though there  *
 * is a D7SEG display between the D3X5 displays.                                    *
 * -> module_number - relative number of the "D3X5" display                         *
 * -> disc_number - display disc number counting from left to right in each row     *
 * first row 1-3, second row 4-6, third row 7-9, four row 10-12, five 13-15 	    *
 * -> disc_status - reset disc "0" or set disc "1"                                  *  
 *	13 14 15                                                                    *
 *	10 11 12                                                                    *
 *	7  8  9                                                                     *
 *	4  5  6                                                                     *
 *	1  2  3                                                                     *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Disc_3x5(uint8_t module_number, uint8_t disc_number, bool disc_status)
{
 /*
  * Simple protection from user error. 
  * If the selected display has not been declared in Init() then the function will not execute.
  */
  if(Fuse(module_number, D3X5) == true) return;

  disc_number = disc_number - 1;
	
  // Start of SPI data transfer
  digitalWrite(_EN_PIN, LOW);

 /* 
  * Send blank data "0" to all control outputs of the other displays BEFORE 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X5, BEFORE);

 /*
  * Each of the discs has two sides, one side corresponds to the disk status "1" - color, 
  * the other side "0" - black. 
  * Each of the "0" or "1" statuses requires a different polarity of the current pulse 
  * released into the disc, and thus for each of the statuses we must drive different 
  * controller outputs to achieve the desired effect. 
  * The list of information about the statuses of all discs for the display 
  * and the currently selected dot to be displayed is contained in two tables:
  * -> setDiscArray_3x5[] - "1" 
  * -> resetDiscArray_3x5[] - "0"
  * Each separate display disc requires 2 byte of data to be transferred. 
  * To flip all 15 discs, we need to send 30 bytes of data.
  */
  for(int byte_number = 0; byte_number < 2; byte_number++)
  {
    if(disc_status == 1) SPI.transfer(pgm_read_byte(&setDiscArray_3x5[disc_number][byte_number]));
    if(disc_status == 0) SPI.transfer(pgm_read_byte(&resetDiscArray_3x5[disc_number][byte_number]));
  }
   
 /* 
  * Send blank data "0" to all control outputs of the other displays AFTER 
  * sending control data to the selected display.
  * Detailed information in the function description SendBlankData().
  */
  SendBlankData(module_number, D3X5, AFTER);

  // End of SPI data transfer
  digitalWrite(_EN_PIN, HIGH);

  // Release of 1ms current pulse 
  ReleaseCurrentPulse();

  // Clear all outputs of the controllers built into the displays
  ClearAllOutputs();
}

/*----------------------------------------------------------------------------------*
 * The function is used to test all displays                                        *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Test(void)
{
  uint8_t current_time_delay = flip_delay; // Save current time delay

  Delay(100);                               // Change flip delay time to 100 
  Clear();                                  // Clear all displays               
  All();                                    // Set all discs of all displays 
  Clear();                                  // Clear all displays 
  Delay(current_time_delay);                // Restore current time delay
}

/*----------------------------------------------------------------------------------*
 * The function is used to turn on (set) all discs of all displays                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::All(void)
{
  for(int i = 0; i < 8; i++)
  {
    switch (moduleInitArray[i][module_type_column]) 
    {
      case D7SEG:
        Display_7Seg((moduleInitArray[i][module_relative_position_column]), ALL);
        break; 

      /* D3X1 = D2X1 - are the same */
      case D3X1:
        Display_3x1((moduleInitArray[i][module_relative_position_column]), 1,1,1);
        break;  

      case D1X3:
        Display_1x3((moduleInitArray[i][module_relative_position_column]), 1,1,1);
        break;
        
      case D1X7:
        Display_1x7((moduleInitArray[i][module_relative_position_column]), 1,1,1,1,1,1,1);
        break;

      case D2X6:
        for(int disc = 1; disc <= 12; disc++)
        {
          Disc_2x6((moduleInitArray[i][module_relative_position_column]), disc, 1); 
        }
        break;
		
      case D3X3:
        for(int disc = 1; disc <= 9; disc++)
        {
          Disc_3x3((moduleInitArray[i][module_relative_position_column]), disc, 1); 
        }
        break;

      case D3X4:
        for(int disc = 1; disc <= 12; disc++)
        {
          Disc_3x4((moduleInitArray[i][module_relative_position_column]), disc, 1); 
        }
        break;

      case D3X5:
        for(int disc = 1; disc <= 15; disc++)
        {
          Disc_3x5((moduleInitArray[i][module_relative_position_column]), disc, 1); 
        }
        break;	
        
      default:
        break;
    }
  }  
}

/*----------------------------------------------------------------------------------*
 * The function is used to turn off (clear) all displays                            *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Clear(void)
{
  for(int i = 0; i < 8; i++)
  {
    switch (moduleInitArray[i][module_type_column]) 
    {
      case D7SEG:
        Display_7Seg((moduleInitArray[i][module_relative_position_column]), CLR);
        break;

      /* D3X1 = D2X1 - are the same */
      case D3X1:
        Display_3x1((moduleInitArray[i][module_relative_position_column]), 0,0,0);
        break;  

      case D1X3:
        Display_1x3((moduleInitArray[i][module_relative_position_column]), 0,0,0);
        break;
        
      case D1X7:
        Display_1x7((moduleInitArray[i][module_relative_position_column]), 0,0,0,0,0,0,0);
        break;

      case D2X6:
        for(int disc = 1; disc <= 12; disc++)
        {
          Disc_2x6((moduleInitArray[i][module_relative_position_column]), disc, 0); 
        }
        break;        
        
      case D3X3:
        for(int disc = 1; disc <= 9; disc++)
        {
          Disc_3x3((moduleInitArray[i][module_relative_position_column]), disc, 0); 
        }
        break;

      case D3X4:
        for(int disc = 1; disc <= 12; disc++)
        {
          Disc_3x4((moduleInitArray[i][module_relative_position_column]), disc, 0); 
        }
        break;

      case D3X5:
        for(int disc = 1; disc <= 15; disc++)
        {
          Disc_3x5((moduleInitArray[i][module_relative_position_column]), disc, 0); 
        }
        break;			
	  
      default:
        break;
    }
  }  
}

/*----------------------------------------------------------------------------------*
 * The function is used to configure the control pins                               *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Pin(uint16_t EN_PIN, uint16_t CH_PIN, uint16_t PL_PIN)
{
  // Release the current pulse - turn ON/OFF
  pinMode(PL_PIN, OUTPUT);
  _PL_PIN = PL_PIN;
  digitalWrite(_PL_PIN, LOW);

  // Charging PSPS module - turn ON/OFF
  pinMode(CH_PIN, OUTPUT);
  _CH_PIN = CH_PIN;
  digitalWrite(_CH_PIN, LOW);
  
  // Start & End SPI transfer data
  pinMode(EN_PIN, OUTPUT);
  _EN_PIN = EN_PIN;
  digitalWrite(_EN_PIN, LOW);  
}

/*----------------------------------------------------------------------------------*
 * The function is used to set the delay effect between flip discs                  *
 * The default value without calling the function is 0                              *
 * Recommended delay range: 0 - 100ms, max 255ms                                    *
 *----------------------------------------------------------------------------------*/
void FlipDisc::Delay(uint8_t new_time_delay)
{
  flip_delay = new_time_delay;  
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * The function is used to check whether the number (module_number) of the selected *
 * display (module_type) exists.                                                    *
 * For example, if the display no.3 (module_number) of a specific type (module_type)*
 * was selected and earlier in the Init() function we declared fewer or no displays *
 * of the selected type (module_type), the function returns 1 - the fuse has tripped*
 *----------------------------------------------------------------------------------*/
bool FlipDisc::Fuse(uint8_t module_number, uint8_t module_type)
{
  uint8_t highest_module_number = 0;
  
  for(int i = 0; i < 8; i++)
  {
    if(moduleInitArray[i][module_type_column] == module_type) highest_module_number = highest_module_number + 1;
  }
  
  if(highest_module_number < module_number) return 1;
  else return 0;
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * The function is used to wait between flip discs                                  *
 * Recommended delay range: 0 - 100ms, max 255ms                                    *
 *----------------------------------------------------------------------------------*/
void FlipDisc::FlipDelay(void)
{
  time_now = millis();
  
  while(millis() - time_now < flip_delay)
  {
    // Do nothing and wait
  }  
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * The function is used to sending empty data to complete the control data string.  *
 * -> module_number - (1-8) the relative position of the display in relation        *
 *    to the displays of the selected type                                          *
 * -> module_type - (D7SEG, D2X1, D3X1, D1X3, D1X7) selected display type           *
 * -> data_position - ("BEFORE", "AFTER") order of sending data, BEFORE control data*
 *    or AFTER control data.                                                        *
 *                                                                                  *
 * Brief:                                                                           *
 * First, based on the arguments, the function determines the absolute position     *
 * of the selected display in the series of all displays. Then, based on the        *
 * information about the types of displays BEFORE or AFTER the currently selected   *
 * display, it prepares an empty data frame "0" and sends this data.                *
 * For proper control of the display, the so-called empty supplementary data frames *
 * are absolutely necessary!                                                        *
 * The point is that we can only control one disc out of all connected display      *
 * modules at a time. So in the entire data frame for e.g. eight 7-Segment displays,* 
 * for 24 bytes of data there are only 2 bits set to "1" and the remaining 190 bits *
 * must be set to "0".                                                              *
 * The architecture of the embedded display controller requires it.                 *
 *----------------------------------------------------------------------------------*/
void FlipDisc::SendBlankData(uint8_t module_number, uint8_t module_type, uint8_t data_position)
{
  uint8_t empty_byte = 0;

  for(int module_absolute_position = 0; module_absolute_position < 8; module_absolute_position++)
  {  
    // Look for the selected display type
    if(moduleInitArray[module_absolute_position][module_type_column] == module_type)
    { 
     /*
      * Then look for a specific display based on a relative number from a series 
      * of displays of the same type. Based on these two parameters "module_number" and 
      * "module_type" we determined the absolute position of the display "module_absolute_position". 
      * Then, based on the absolute position of the display, we calculate the empty data frame "0"
      * and sending this data.
      */
      if(moduleInitArray[module_absolute_position][module_relative_position_column] == module_number)
      {       
        if(data_position == BEFORE)
        {
          // In the calculation, we omit the currently selected display "(module_absolute_position + 1)"
          for(int i = (module_absolute_position + 1); i < 8; i++) empty_byte = moduleInitArray[i][number_bytes_column] + empty_byte;     
          for(int j = 0; j < empty_byte; j++) SPI.transfer(0);
          return;     
        }
        
        if(data_position == AFTER)
        {
          // In the calculation, we omit the currently selected display "(module_absolute_position - 1)"
          for(int i = 0; i <= (module_absolute_position - 1); i++) empty_byte = moduleInitArray[i][number_bytes_column] + empty_byte;
          for(int j = 0; j < empty_byte; j++) SPI.transfer(0);
          return;      
        }
      }
    }
  }   
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * This function is used to disable all outputs of all displays in order to protect *
 * the displays against incorrect control or failure of the power module.           *
 *----------------------------------------------------------------------------------*/
void FlipDisc::ClearAllOutputs(void)
{
  // Start of SPI data transfer
  digitalWrite(_EN_PIN, LOW);

  // Clear all outputs of connected displays 
  for(int i = 0; i < number_all_bytes; i++) SPI.transfer(0);

  // End of SPI data transfer
  digitalWrite(_EN_PIN, HIGH);
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * This function is used to prepare the Pulse Shaper Power Supply module            * 
 * for the first time AFTER power up the device.                                    *
 *----------------------------------------------------------------------------------*/
void FlipDisc::PrepareCurrentPulse(void)
{			
  digitalWrite(_PL_PIN, LOW);    // Turn OFF PSPS module output
  digitalWrite(_CH_PIN, HIGH);   // Turn ON charging
  delay(1000);                   // First charging time 1000ms
  digitalWrite(_CH_PIN, LOW);    // Turn OFF charging
}

/*----------------------------------------------------------------------------------*
 * Private function                                                                 *
 * The function is used to generate a current pulse of 1ms length                   *
 * required by flip-disc displays.                                                  *
 *----------------------------------------------------------------------------------*/
void FlipDisc::ReleaseCurrentPulse(void)
{
  digitalWrite(_PL_PIN, LOW);    // Turn OFF PSPS module output
  digitalWrite(_CH_PIN, HIGH);   // Turn ON charging
  delayMicroseconds(100);        // Charging time 100us
  digitalWrite(_CH_PIN, LOW);    // Turn OFF charging 
  digitalWrite(_PL_PIN, HIGH);   // Turn ON PSPS module output
  delay(1);                      // 1ms current pulse
  digitalWrite(_PL_PIN, LOW);    // Turn OFF PSPS module output
  FlipDelay();                   // Delay effect between flip discs
}

/*----------------------------------------------------------------------------------*
 * Preinstantiate Object                                                            *
 *----------------------------------------------------------------------------------*/
FlipDisc Flip = FlipDisc();
