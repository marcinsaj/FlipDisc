## Arduino FlipDisc Library v1.1.2
![GitHub Release](https://img.shields.io/github/v/release/marcinsaj/FlipDisc?sort=date&style=flat&label=Version) ![GitHub License](https://img.shields.io/github/license/marcinsaj/FlipDisc)

https://github.com/marcinsaj/FlipDisc  
The MIT License
Marcin Saj 15 Jan 2023  
  
Dear Maker!   
you are dealing with a very large project and not everything can be clear, because it is difficult to provide such extensive documentation about the library itself, several displays and side modules, display methods and many example program codes. If you need help or have any comments, please contact me: marcin@flipo.io

<a href="https://www.buymeacoffee.com/marcinsaj"><img src="https://github.com/marcinsaj/marcinsaj/blob/main/Buy-me-a-coffee.png" /></a> 
</br>

-------------------------------------------------------------------------------------------  

 
## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/about.png) Introduction  

Arduino library for flip-disc displays.
This library is intended for use with the displays designed by www.Flipo.io - Marcin Saj.  

The library allows you to easily control displays connected in series. You can connect up to 8 different displays in any order. Example codes and diagrams on how to connect the displays with the Arduino and the [Pulse Shaper Power Supply](https://flipo.io/project/flip-disc-power-supply/) module can be found below and on the project website: www.Flipo.io  
  
All the functions responsible for controlling the displays are described in example codes and in the library files [FlipDisc.ccp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp) & [FlipDisc.h](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.h)  

**✔️ Supported Displays & Modules:**       

- [dedicated Arduino controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/)
- [7-segment flip-disc display](https://flipo.io/project/flip-disc-7-segment-display/)
- [2x1 flip-disc display](https://flipo.io/project/flip-disc-2x1-display/)
- [3x1 flip-disc display](https://flipo.io/project/flip-disc-3x1-display/)
- [1x3 flip-disc display](https://flipo.io/project/flip-disc-1x3-display/)
- [1x7 flip-disc display](https://flipo.io/project/flip-disc-1x7-display/)
- [2x6 flip-disc display](https://flipo.io/project/2x6-flip-disc-display/)
- 3x3 flip-disc display - work in progress
- 3x4 flip-disc display - work in progress
- 3x5 flip-disc display - work in progress
- 4x3x3 flip-disc display - work in progress
- [flip-disc power supply module](https://flipo.io/project/flip-disc-power-supply/)   

-------------------------------------------------------------------------------------------     

## Library Installation ##
To use the **FlipDisc** library:
- First method
  - Open Library Manager in Arduino IDE.
  - Type library name "FlipDisc" and install it.
- Second method
  - Go to https://github.com/marcinsaj/FlipDisc, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
  - Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually      **FlipDisc-master** or **FlipDisc-main**.
  - Rename the folder to just **FlipDisc**.
  - Copy the renamed folder to the Arduino sketchbook\libraries folder.  

-------------------------------------------------------------------------------------------   

## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/ok.png) Examples - Code & Diagrams

Several [example sketches](https://github.com/marcinsaj/FlipDisc/tree/main/examples) are included with the **FlipDisc** library.  
In order to better understand the code, a visualization of connecting individual modules has been attached to each program code.  

All diagrams below include the Arduino UNO as a reference. You can use any Arduino board to control the displays. ⚠️ Remember that for proper operation, each of the display connection configurations and the library itself requires the connection of the [Pulse Shaper Power Supply](https://flipo.io/project/flip-disc-power-supply/) module.  
  
In order to simplify the control of the displays, a [dedicated controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/) was designed as the Arduino Shield for the Arduino Nano Every and Nano 33 IoT boards. The controller has a built-in pulse shaper power supply module and several other features.
  
In summary, there are two options:
- use any Arduino board + [power supply module](https://flipo.io/project/flip-disc-power-supply/)
- or a [dedicated controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/)  

</br>
</br>

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-controller-for-flip-disc-displays.png"></p>  

-------------------------------------------------------------------    

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-7-seg-flip-disc-psps-module.png"></p>    

1. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/01-1x7seg-flip-disc-arduino-psps/01-1x7seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:     

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2x7-seg-flip-disc-psps-module.png"></p> 

2. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/02-2x7seg-flip-disc-arduino-psps/02-2x7seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-02.pdf) :small_red_triangle_down:

-------------------------------------------------------------------   
  
<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2x7-seg-3dots-flip-disc-psps-module.png"></p>        

3. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/03-2x7seg-1x3x1-flip-disc-arduino-psps/03-2x7seg-1x3x1-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-03.pdf) :small_red_triangle_down:  

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-4x7-seg-3dots-flip-disc-psps-module.png"></p>
 
4. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/04-4x7seg-1x3x1-flip-disc-arduino-psps/04-4x7seg-1x3x1-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-04.pdf) :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-6x7-seg-flip-disc-psps-module.png"></p>    

5. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/05-6x7seg-flip-disc-arduino-psps/05-6x7seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-05.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-6x7-seg-2x3dots-flip-disc-psps-module.png"></p>

6. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/06-6x7seg-2x3x1-flip-disc-arduino-psps/06-6x7seg-2x3x1-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-06.pdf) :small_red_triangle_down:
  
-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2dots-flip-disc-psps-module.png"></p>

7. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/07-1x2x1-flip-disc-arduino-psps/07-1x2x1-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-2x1-Dot-Module-Arduino-Example-Connection-Schematic.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-3dots-flip-disc-psps-module.png"></p>

8. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/08-1x3x1-flip-disc-arduino-psps/08-1x3x1-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-3x1-Dot-Module-Arduino-Example-Connection-Schematic.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x3-flip-disc-psps-module.png"></p>

9. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/09-1x1x3-flip-disc-arduino-psps/09-1x1x3-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-1x3-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x7-flip-disc-psps-module.png"></p>

10. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/10-1x1x7-flip-disc-arduino-psps/10-1x1x7-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-1x7-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2x6-flip-disc-psps-module.png"></p>

11. [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/11-1x2x6-flip-disc-arduino-psps/11-1x2x6-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-2x6-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-3x3-flip-disc-psps-module.png"></p>

12. Code - to do &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/blob/main/datasheet/Flip-disc-3x3-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

-------------------------------------------------------------------

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-4x3x3-flip-disc-psps-module.png"></p>

13. Code - to do &nbsp; Diagram - to do :small_red_triangle_down:

-------------------------------------------------------------------

## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/note.png) Warning!    

The library uses SPI to control flip-disc displays. The user must remember to connect the display inputs marked DIN - data in - to the MOSI (SPI) output of the microcontroller and the CLK - clock - input of the display to the SCK (SPI) output of the microcontroller. In addition, it is very important to connect and declare EN, CH, PL pins. The declaration of DIN (MOSI) and CLK (SCK) is not necessary, because the <SPI.h> library handles the SPI hardware pins. 

 ```
 display -> microcontroller  
 DIN -----> MOSI (SPI)  
 CLK -----> SCK (SPI)  
 EN ------> any digital pin  
 CH ------> any digital pin  
 PL ------> any digital pin 
 ```

Incorrect declaration of control pins or incorrect connection of modules may result in damage to flip-disc displays. 
When using the **FlipDisc** library with flip-disc displays, the user is responsible for ensuring that the connection of the display and power module corresponds to the declared control pins.

-------------------------------------------------------------------------------------------  

## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/tools.png) Functions  

1.⚠️
```c++
#define EN_PIN  'Set your pin'  // Start & End SPI transfer data
#define CH_PIN  'Set your pin'  // Charging PSPS module - turn ON/OFF
#define PL_PIN  'Set your pin'  // Release the current pulse - turn ON/OFF

Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
```
Flip.Pin(...); it is most important function and first to call before everything else. The function is used to declare pin functions. Before starting the device, double check that the declarations and connection are correct. If the connection of the control outputs is incorrect, the display may be physically damaged.

------------------------------------------------------------------------------------------- 

2.⚠️
```c++
Flip.Init(MOD1, MOD2 = 0xFF, MOD3 = 0xFF, MOD4 = 0xFF, 
                   MOD5 = 0xFF, MOD6 = 0xFF, MOD7 = 0xFF, MOD8 = 0xFF);  
                   
/* Examples function call */
/* 8 modules */
Flip.Init(D7SEG, D7SEG, D3X1, D7SEG, D7SEG, D3X1, D7SEG, D7SEG);

/* 1x3 display */
Flip.Init(D1X3);

/* 1x7 display */
Flip.Init(D1X7);

/* 2 x 7-Segment displays */
Flip.Init(D7SEG, D7SEG);
```
Flip.Init(...) it is second most important function. Initialization function for a series of displays. Up to 8 displays can be connected in series in any configuration. The function has 1 default argument and 7 optional arguments. The function also prepares SPI. Correct initialization requires code names of the serially connected displays:
 - D7SEG - [7-segment display](https://flipo.io/project/flip-disc-7-segment-display/)   
 - D2X1 - [2x1 display](https://flipo.io/project/flip-disc-2x1-display/)  
 - D3X1 - [3x1 display](https://flipo.io/project/flip-disc-3x1-display/)
 - D1X3 - [1x3 display](https://flipo.io/project/flip-disc-1x3-display/)
 - D1X7 - [1x7 display](https://flipo.io/project/flip-disc-1x7-display/)
 - D2X6 - [2x6 display](https://flipo.io/project/2x6-flip-disc-display/)
 - D3X3 - work in progress
 - D3X4 - work in progress
 - D3X5 - work in progress

------------------------------------------------------------------------------------------- 

3.
```c++
Flip.Delay(0-100ms);

/* Example function call */
Flip.Delay(20);
```
The function is used to set the delay effect between flip discs. The default value without calling the function is 0. Can be called multiple times anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms  

------------------------------------------------------------------------------------------- 

4.
```c++
Flip.Test();
```
The function is used to test all declared displays - turn on and off all displays.   

------------------------------------------------------------------------------------------- 

5.
```c++
Flip.All();
```
The function is used to turn on (set) all discs of all displays.  

------------------------------------------------------------------------------------------- 

6.
```c++
Flip.Clear();
```

The function is used to turn off (clear) all displays.  

------------------------------------------------------------------------------------------- 

7.
```c++
Flip.Disc_7Seg(module_number, disc_number, disc_status);

/* An example of calling the function to display disc no.19 
of the first 7-Segment display counting from the left */
Flip.Disc_7Seg(1, 19, 1); 

  0  1  2  3  4
 19           5
 18           6
 17 20 21 22  7
 16           8
 15           9
 14 13 12 11 10
```
  
The function allows you to control one selected disc of 7-Segment display. The first argument is the relative number of the display in the series of all 7-Segment displays. For example, if we have a combination of D7SEG, D3X1, D7SEG then the second D7SEG display will have a relative number of 2 even though there is a D3X1 display between the D7SEG displays. The second argument disc_number is the number of selected disc 0-22 of the 7-Segment display. The third argument is the status of the selected disc:  
 - module_number - relative number of the "D7SEG" display
 - disc_number - there are 23 discs in 7-Segment display 0-22
 - disc_status - reset disc "0" or set disc "1"                                       

See the function description in [FlipDisc.cpp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp)

------------------------------------------------------------------------------------------- 

8.
```c++
Flip.Display_7Seg(module_number, data);

/* An example of calling the function to display the number 5 
on the first 7-Segment display counting from the left 
 - module_number - 1-8 D7SEG display
 - data - symbol to display. */
Flip.Display_7Seg(1, 5); 
```
  
The function allows you to control one 7-segment display. The first argument "module_number" is the relative number of the display in the series of all displays. For example, if we have a combination of D7SEG, D3X1, D7SEG then the second D7SEG display will have a relative number of 2 even though there is a D3X1 display between the D7SEG displays.  
  
7-Segment display consists of 23 discs. The displayArray_7Seg[][] array contains information about all disc statuses for the symbol we want to display. To flip a selected disc, we need to know the corresponding control outputs. Disc statuses "0" and "1" correspond to different control outputs. The list of information about all control outputs for corresponding disc statuses of all discs and the currently selected digit/symbol to be displayed are contained in two tables:
 - setDiscArray_7Seg[] - "1"
 - resetDiscArray_7Seg[] - "0"
  
See the function description in [FlipDisc.cpp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp)

------------------------------------------------------------------------------------------- 

9.
```c++
Flip.Matrix_7Seg(data1, data2 = 0xFF, data3 = 0xFF, data4 = 0xFF, 
                  data5 = 0xFF, data6 = 0xFF, data7 = 0xFF, data8 = 0xFF);
                  
/* Example function call assuming that we have declared the following displays 
Flip.Init(D7SEG, D7SEG, D7SEG, D7SEG) and we want to display temperature 70°F. */ 
Flip.Matrix_7Seg(7, 0, DEG, F);  

/* Or Celsius 23°C */ 
Flip.Matrix_7Seg(2, 3, DEG, C);

```

Function to control up to eight 7-segment displays.

7-segment displays allow the display of numbers and symbols.
Symbols can be displayed using their code name or number   
e.g. 37/DEG - "°"  - Degree symbol   

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
  - 45/VLA - "||" - All Vertical lines

------------------------------------------------------------------------------------------- 

10.
```c++
Flip.Disc_3x1(module_number, disc_number, disc_status);

/* Example function call. Set the second disc of the first display, counting from the left */
Flip.Disc_3x1(1, 2, 1);
```

Function allows you to control a selected disc in a selected 3x1 display. You can control only one disc of the selected display at a time. The first argument module_number is the relative number of the display in the series of all displays. For example, if we have a combination of D3X1, D7SEG, D3X1, then the second D3X1 display will have a relative number of 2 even though there is a D7SEG display between the D3X1 displays.  
 - module_number - relative number of the D3X1 display
 - disc_number - display disc number counting from top to bottom 1-3
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 

11. 
```c++
Flip.Display_3x1(module_number, disc1 = 0xFF, disc2 = 0xFF, disc3 = 0xFF);

/* Example function call. Set the first and third disc and reset second disc 
of the second 3x1 display, counting from the left */
Flip.Display_3x1(2, 1, 0, 1);

/* Reset first disc of the first 3x1 display */
Flip.Display_3x1(1, 0);

/* Reset first disc and set second disc of the first 3x1 display */
Flip.Display_3x1(1, 0, 1);

```

Function allows you to control one, two or three discs of the selected 3x1 display. The first argument is the relative number "module_number" of the display in the series of all 3x1 displays. For example, if we have a combination of D3X1, D7SEG, D3X1, then the second D3X1 display will have a relative number of 2 even though there is a D7SEG display between the D3X1 displays.
 - module_number - relative number of the D3X1 display
 - disc1, disc2, disc3 - display discs counting from top to bottom 1-3

------------------------------------------------------------------------------------------- 

12. 
```c++
Flip.Disc_2x1(module_number, disc_number, disc_status);

/* Example function call. Set the second disc of the first display, counting from the left */
Flip.Disc_2x1(1, 2, 1);
```

Function allows you to control a selected disc in a selected 2x1 display. You can control only one disc of the selected display at a time. The first argument module_number is the relative number of the display in the series of all 2x1 displays. For example, if we have a combination of D2X1, D7SEG, D2X1, then the second D2X1 display will have a relative number of 2 even though there is a D7SEG display between the D2X1 displays.  
 - module_number - relative number of the D2X1 display
 - disc_number - display disc number counting from top to bottom 1-2
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 

13. 
```c++
Flip.Display_2x1(module_number, disc1 = 0xFF, disc2 = 0xFF);

/* Example function call. Set the first disc and reset second disc 
of the second 2x1 display, counting from the left */
Flip.Display_2x1(2, 1, 0);

/* Reset first disc of the first 2x1 display */
Flip.Display_2x1(1, 0);

/* Reset first disc and set second disc of the first 2x1 display */
Flip.Display_2x1(1, 0, 1);

```

Function allows you to control one or two discs of the selected 2x1 display. The first argument is the relative number "module_number" of the display in the series of all 2x1 displays. For example, if we have a combination of D2X1, D7SEG, D2X1, then the second D2X1 display will have a relative number of 2 even though there is a D7SEG display between the D2X1 displays.
 - module_number - relative number of the D2X1 display
 - disc1, disc2 - display discs counting from top to bottom 1-2

------------------------------------------------------------------------------------------- 

14. 
```c++
Flip.Disc_1x3(module_number, disc_number, disc_status);

/* Example function call. Reset the second disc, counting from the left 
of the first display, counting from the left */
Flip.Disc_1x3(1, 2, 0);
```

Function allows you to control a selected disc in a selected 1x3 display. You can control only one disc of the selected display at a time. The first argument module_number is the relative number of the display in the series of all displays. For example, if we have a combination of D1X3, D7SEG, D1X3, then the second D1X3 display will have a relative number of 2 even though there is a D7SEG display between the D1X3 displays.  
 - module_number - relative number of the D1X3 display
 - disc_number - display disc number counting from left to right 1-3
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 
15. 
```c++
void Flip.Display_1x3(module_number, disc1 = 0xFF, disc2 = 0xFF, disc3 = 0xFF);

/* Example function call. Set the first and third disc and reset second disc 
of the second 1x3 display, counting from the left */
Flip.Display_1x3(2, 1, 0, 1);

/* Set first disc of the first display */
Flip.Display_1x3(1, 1);

/* Set first disc and reset second disc of the first display */
Flip.Display_1x3(1, 1, 0);
```

The function allows you to control one, two or three discs of the selected 1x3 display. The first argument is the relative number "module_number" of the display in the series of all displays. For example, if we have a combination of D1X3, D7SEG, D1X3, then the second D1X3 display will have a relative number of 2 even though there is a D7SEG display between the D1X3 displays.
 - module_number - relative number of the D1X3 display
 - disc1, disc2, disc3 - display discs counting from left to right 1-3

------------------------------------------------------------------------------------------- 
16. 
```c++
Flip.Disc_1x7(module_number, disc_number, disc_status);

/* Example function call. Set the fifth disc, counting from the left 
of the second 1x7 display, counting from the left */
Flip.Disc_1x7(2, 5, 1);

/* Reset the third disc, counting from the left of the first display, counting from the left */
Flip.Disc_1x7(1, 3, 0);
```

Function allows you to control a selected disc in a selected 1x7 display. You can control only one disc of the selected display at a time. The first argument module_number is the relative number of the display in the series of all 1x7 displays. For example, if we have a combination of D1X7, D7SEG, D1X7, then the second D1X7 display will have a relative number of 2 even though there is a D7SEG display between the D1X7 displays.  
 - module_number - relative number of the D1X7 display
 - disc_number - display disc number counting from left to right 1-7
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 
17. 
```c++
Flip.Display_1x7(module_number, disc1 = 0xFF, disc2 = 0xFF, disc3 = 0xFF, 
                    disc4 = 0xFF, disc5 = 0xFF, disc6 = 0xFF, disc7 = 0xFF);
                    
/* Example function call. Reset the second and seventh disc counting from the left 
and set rest of the discs of the first 1x7 display, counting from the left */
Flip.Display_1x7(1, 1, 0, 1, 1, 1, 1, 0);
```

The function allows you to control up to seven discs of the selected display. The first argument is the relative number "module_number" of the display in the series of all 1x7 displays. For example, if we have a combination of D1X7, D7SEG, D1X7, then the second D1X7 display will have a relative number of 2 even though there is a D7SEG display between the D1X7 displays.
 - module_number - relative number of the D1X7 display
 - disc1, disc2, disc3, disc4, disc5, disc6, disc7 - display discs counting from left to right 1-7

------------------------------------------------------------------------------------------- 
18. 
```c++
Flip.Disc_2x6(uint8_t module_number, uint8_t disc_number, bool disc_status);
                    
// Example function call. Set the second disc counting from the right
Flip.Disc_2x6(1, 2, 1);

/* 12 11 10  9  8  7
    6  5  4  3  2  1 */

```

Function allows you to control a selected disc in a 2x6 display. The first argument is the relative number "module_number" of the display in the series of all displays. For example, if we have a combination of D2X6, D7SEG, D2X6, then the second D2X6 display will have a relative number of 2 even though there is a D7SEG display between the D2X6 displays.
 -  module_number - relative number of the "D2X6" display
 -  disc_number - display disc number counting from left to right in each row
 - first row 1-6, second row 7-12
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 
19. 
```c++
Flip.Display_2x6(uint8_t module_number, uint8_t row_number, uint8_t column_number, bool disc_status);
                    
// Example function call. Reset disc in third column, second row.
Flip.Display_2x6(1, 2, 3, 1);

 /* Rows, columns & discs numbers
     6  5  4  3  2  1
    12 11 10  9  8  7
     6  5  4  3  2  1 */
```

Function allows you to control a selected disc in a 2x6 display. Addressing selected disc using rows and columns. The first argument module_number is the relative number of the display in the series of all displays. For example, if we have a combination of D2X6, D7SEG, D2X6, then the second D2X6 display will have a relative number of 2 even though there is a D7SEG display between the D2X6 displays.
 - module_number - relative number of the "D2X6" display
 - row_number - display disc row number counting from bottom to top 1-2
 - column_number - display disc number counting from left to right 1-6
 - disc_status - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 

## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/check.png) Supported Displays & Modules      

- [dedicated Arduino controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/)
- [7-segment flip-disc display](https://flipo.io/project/flip-disc-7-segment-display/)
- [2-disc flip-disc display](https://flipo.io/project/flip-disc-2x1-display/)
- [3-disc flip-disc display](https://flipo.io/project/flip-disc-3x1-display/)
- [1x3 flip-disc display](https://flipo.io/project/flip-disc-1x3-display/)
- [1x7 flip-disc display](https://flipo.io/project/flip-disc-1x7-display/)
- [2x6 flip-disc display](https://flipo.io/project/2x6-flip-disc-display/)
- 3x3 flip-disc display - work in progress
- 3x4 flip-disc display - work in progress
- 3x5 flip-disc display - work in progress
- [flip-disc power supply module](https://flipo.io/project/flip-disc-power-supply/)  

------------------------------------------------------------------------------------------- 

![flip-disc arduino controller](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-arduino-controller.jpg)
![flip-disc 7-segment display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-7-segment-display.jpg)
![flip-disc 2x1 display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-2x1-display.jpg)
![flip-disc 3x1 display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-3x1-display.jpg)
![flip-disc 1x3 display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x3-display.jpg)
![flip-disc 1x7 display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x7-display.jpg)
![flip-disc 2x6 display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flipo-2x6-flip-disc-display-project.jpg)
![4x3x3 flip-disc display](https://github.com/marcinsaj/FlipDisc/blob/main/extras/4x3x3-flip-disc-display-cover-github.webp)
![flip-disc power-supply module](https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-power-supply-module.jpg)
