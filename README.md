...work in progress...:  
...work in progress...:  
...work in progress...:  


# Arduino FlipDisc Library v1.0.0
https://github.com/marcinsaj/FlipDisc  
The MIT License  
Marcin Saj 15 Jan 2023  
  
Dear Maker!   
you are dealing with a very large project and not everything can be clear, because it is difficult to provide such extensive documentation about the library itself, several displays and side modules, display methods and many example program codes. If you need help or have any comments, please contact me: marcin@flipo.io


-------------------------------------------------------------------------------------------  

 
## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/about.png) Introduction  

Arduino library for flip-disc displays.
This library is intended for use with the displays designed by www.Flipo.io - Marcin Saj.  

The library allows you to easily control displays connected in series. You can connect up to 8 different displays in any order. Example codes and diagrams on how to connect the displays with the Arduino and the [Pulse Shaper Power Supply](https://flipo.io/project/flip-disc-power-supply/) module can be found below and on the project website: www.Flipo.io  
  
All the functions responsible for controlling the displays are described in example codes and in the library files [FlipDisc.ccp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp) & [FlipDisc.h](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.h)  

**✔️ Supported Displays & Modules:**       

- [dedicated Arduino controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/)
- [7-segment flip-disc display](https://flipo.io/project/flip-disc-7-segment-display/)
- [2-dot flip-disc display](https://flipo.io/project/flip-disc-2x1-display/)
- [3-dot flip-disc display](https://flipo.io/project/flip-disc-3x1-display/)
- [1x3 flip-disc display](https://flipo.io/project/flip-disc-1x3-display/)
- [1x7 flip-disc display](https://flipo.io/project/flip-disc-1x7-display/)
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

Several example sketches are included with the **FlipDisc** library.  
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

1️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/01-1x7-seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:     

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2x7-seg-flip-disc-psps-module.png"></p> 

2️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/02-2x7-seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-02.pdf) :small_red_triangle_down:

-------------------------------------------------------------------   
  
<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2x7-seg-3dots-flip-disc-psps-module.png"></p>        

3️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/03-2x7-seg-1x3dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-03.pdf) :small_red_triangle_down:  

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-4x7-seg-3dots-flip-disc-psps-module.png"></p>
 
4️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/04-4x7-seg-1x3dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-04.pdf) :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-6x7-seg-flip-disc-psps-module.png"></p>    

5️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/05-6x7-seg-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-05.pdf) :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-6x7-seg-2x3dots-flip-disc-psps-module.png"></p>

6️⃣ [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/06-6x7-seg-2x3dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-7-Segment-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-06.pdf) :small_red_triangle_down:
  
-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-2dots-flip-disc-psps-module.png"></p>   

:seven: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/07-1x2dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-2x1-Dot-Module-Arduino-Example-Connection-Schematic.pdf) :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-3dots-flip-disc-psps-module.png"></p>  

:eight: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/08-1x3dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-3x1-Dot-Module-Arduino-Example-Connection-Schematic.pdf) :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x3-flip-disc-psps-module.png"></p>  

:nine: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/09-1x1x3-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-1x3-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

-------------------------------------------------------------------    

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x7-flip-disc-psps-module.png"></p>  

:one::zero: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/10-1x1x7-flip-disc-arduino-psps.ino) &nbsp; [Download diagram](https://github.com/marcinsaj/FlipDisc/raw/main/datasheet/Flip-disc-1x7-Display-Arduino-Example-Connection-with-Pulse-Shaper-Schematic-01.pdf) :small_red_triangle_down:

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

1️⃣⚠️
```c++
#define EN_PIN  'Set your pin'  // Start & End SPI transfer data
#define CH_PIN  'Set your pin'  // Charging PSPS module - turn ON/OFF
#define PL_PIN  'Set your pin'  // Release the current pulse - turn ON/OFF

FlipDisc.Pin(EN_PIN, CH_PIN, PL_PIN);
```
FlipDisc.Pin(...); it is most important function and first to call before everything else. The function is used to declare pin functions. Before starting the device, double check that the declarations and connection are correct. If the connection of the control outputs is incorrect, the display may be physically damaged.

------------------------------------------------------------------------------------------- 

2️⃣⚠️
```c++
FlipDisc.Init(MOD1, MOD2 = 0xFF, MOD3 = 0xFF, MOD4 = 0xFF, 
                   MOD5 = 0xFF, MOD6 = 0xFF, MOD7 = 0xFF, MOD8 = 0xFF);  
                   
/* Examples function call */
/* 8 modules */
FlipDisc.Init(SEG, SEG, DOTS, SEG, SEG, DOTS, SEG, SEG);

/* 1x3 display */
FlipDisc.Init(FLIP3);

/* 1x7 display */
FlipDisc.Init(FLIP7);

/* 2 x 7-Segment displays */
FlipDisc.Init(SEG, SEG);
```
FlipDisc.Init(...) it is second most important function. Initialization function for a series of displays. Up to 8 displays can be connected in series in any configuration. The function has 1 default argument and 7 optional arguments. The function also prepares SPI. Correct initialization requires code names of the serially connected displays:
 - SEG - 7-segment display    
 - DOTS - 2x1 or 3x1 dot display  
 - FLIP3 - 1x3 display  
 - FLIP7 - 1x7 display  

------------------------------------------------------------------------------------------- 

3️⃣
```c++
FlipDisc.Delay(0-100ms);

/* Example function call */
FlipDisc.Delay(20);
```
The function is used to set the delay effect between flip discs. The default value without calling the function is 0. Can be called multiple times anywhere in the code. Recommended delay range: 0 - 100ms, max 255ms  

------------------------------------------------------------------------------------------- 

4️⃣
```c++
FlipDisc.Test();
```
The function is used to test all declared displays - turn on and off all displays.   

------------------------------------------------------------------------------------------- 

5️⃣
```c++
FlipDisc.All();
```
The function is used to turn on (set) all discs of all displays.  

------------------------------------------------------------------------------------------- 

6️⃣
```c++
FlipDisc.Clear();
```

The function is used to turn off (clear) all displays.  

------------------------------------------------------------------------------------------- 

7️⃣
```c++
FlipDisc.ToSeg(moduleNumber, data);

/* An example of calling the function to display the number 5 
on the first 7-Segment display counting from the left 
 - moduleNumber - 1-8 SEG display
 - data - symbol to display. */
FlipDisc.ToSeg(1, 5); 
```
  
The function allows you to control one 7-segment display. The first argument "moduleNumber" is the relative number of the display in the series of all displays. For example, if we have a combination of SEG, DOTS, SEG then the second SEG display will have a relative number of 2 even though there is a DOTS display between the SEG displays.  
  
7-Segment display consists of 23 discs. The displaySegArray[][] array contains information about all disc statuses for the symbol we want to display. To flip a selected disc, we need to know the corresponding control outputs. Disc statuses "0" and "1" correspond to different control outputs. The list of information about all control outputs for corresponding disc statuses of all discs and the currently selected digit/symbol to be displayed are contained in two tables:
 - setDiscArray[] - "1"
 - resetDiscArray[] - "0"
  
See the function description in [FlipDisc.cpp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp)

------------------------------------------------------------------------------------------- 

8️⃣
```c++
FlipDisc.Seg(data1, data2 = 0xFF, data3 = 0xFF, data4 = 0xFF, 
                  data5 = 0xFF, data6 = 0xFF, data7 = 0xFF, data8 = 0xFF);
                  
/* Example function call assuming that we have declared the following displays 
FlipDisc.Init(SEG, SEG, SEG, SEG) and we want to display temperature 70°F. */ 
FlipDisc.Seg(7, 0, DEG, FAH);  

/* Or Celsius 23°C */ 
FlipDisc.Seg(2, 3, DEG, CEL);

```

Function to control up to eight 7-segment displays. The first argument is the default and the others are optional. This function allows you to display numbers and symbols: 0-9, "°","C" , "F", etc.  
Code names for symbols: 
 - ALL - Set all discs
 - CLR - Clear Display
 - DEG - "°" - Degree symbol
 - CEL - "C" - Celsius symbol
 - FAH - "F" - Fahrenheit symbol 
 - HUM - "H" - Humidity symbol 
 - PFH - "%" - Percent first half symbol
 - PSH - "%" - Percent second half symbol 
 - UPD - "¯" - Upper dash symbol
 - MID - "-" - Middle dash symbol
 - BTD - "_" - Bottom dash symbol
 - ALD - All three dashes

------------------------------------------------------------------------------------------- 

9️⃣
```c++
FlipDisc.ToDot(moduleNumber, dotNumber, dotStatus);

/* Example function call. Set the second dot of the first display, counting from the left */
FlipDisc.ToDot(1, 2, 1);
```

Function allows you to control a selected disc in a selected dot display. You can control only one dot of the selected display at a time. The first argument moduleNumber is the relative number of the display in the series of all displays. For example, if we have a combination of DOTS, SEG, DOTS, then the second DOTS display will have a relative number of 2 even though there is a SEG display between the DOTS displays.  
 - moduleNumber - relative number of the DOTS display
 - dotNumber - display dot number counting from top to bottom 1-3
 - dotStatus - reset dot "0" or set disc "1"

------------------------------------------------------------------------------------------- 

1️⃣0️⃣
```c++
FlipDisc.Dot(moduleNumber, dot1 = 0xFF, dot2 = 0xFF, dot3 = 0xFF);

/* Example function call. Set the first and third dot and reset second dot 
of the second dot display, counting from the left */
FlipDisc.Dot(2, 1, 0, 1);

/* Reset first dot of the first dot display */
FlipDisc.Dot(1, 0);

/* Reset first dot and set second dot of the first dot display */
FlipDisc.Dot(1, 0, 1);

```

Function allows you to control one, two or three dots of the selected display. The first argument is the relative number "moduleNumber" of the display in the series of all displays. For example, if we have a combination of DOTS, SEG, DOTS, then the second DOTS display will have a relative number of 2 even though there is a SEG display between the DOTS displays.
 - moduleNumber - relative number of the DOTS display
 - dot1, dot2, dot3 - display dots counting from top to bottom 1-3

------------------------------------------------------------------------------------------- 

1️⃣1️⃣
```c++
FlipDisc.ToFlip3(moduleNumber, discNumber, discStatus);

/* Example function call. Reset the second disc, counting from the left 
of the first display, counting from the left */
FlipDisc.ToFlip3(1, 2, 0);
```

Function allows you to control a selected disc in a selected FLIP3 display. You can control only one disc of the selected display at a time. The first argument moduleNumber is the relative number of the display in the series of all displays. For example, if we have a combination of FLIP3, SEG, FLIP3, then the second FLIP3 display will have a relative number of 2 even though there is a SEG display between the FLIP3 displays.  
 - moduleNumber - relative number of the FLIP3 display
 - discNumber - display disc number counting from left to right 1-3
 - discStatus - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 
1️⃣2️⃣
```c++
void FlipDisc.Flip3(moduleNumber, disc1 = 0xFF, disc2 = 0xFF, disc3 = 0xFF);

/* Example function call. Set the first and third disc and reset second disc 
of the second display, counting from the left */
FlipDisc.Flip3(2, 1, 0, 1);

/* Set first disc of the first display */
FlipDisc.Flip3(1, 1);

/* Set first disc and reset second disc of the first display */
FlipDisc.Flip3(1, 1, 0);
```

The function allows you to control one, two or three discs of the selected display. The first argument is the relative number "moduleNumber" of the display in the series of all displays. For example, if we have a combination of FLIP3, SEG, FLIP3, then the second FLIP3 display will have a relative number of 2 even though there is a SEG display between the FLIP3 displays.
 - moduleNumber - relative number of the FLIP3 display
 - dot1, dot2, dot3 - display discs counting from left to right 1-3

------------------------------------------------------------------------------------------- 
1️⃣3️⃣
```c++
FlipDisc.ToFlip7(moduleNumber, discNumber, discStatus);

/* Example function call. Set the fifth disc, counting from the left 
of the second display, counting from the left */
FlipDisc.ToFlip7(2, 5, 1);

/* Reset the third disc, counting from the left of the first display, counting from the left */
FlipDisc.ToFlip7(1, 3, 0);
```

Function allows you to control a selected disc in a selected FLIP7 display. You can control only one disc of the selected display at a time. The first argument moduleNumber is the relative number of the display in the series of all displays. For example, if we have a combination of FLIP7, SEG, FLIP7, then the second FLIP7 display will have a relative number of 2 even though there is a SEG display between the FLIP7 displays.  
 - moduleNumber - relative number of the FLIP7 display
 - discNumber - display disc number counting from left to right 1-7
 - discStatus - reset disc "0" or set disc "1"

------------------------------------------------------------------------------------------- 
1️⃣4️⃣
```c++
FlipDisc.Flip7(moduleNumber, disc1 = 0xFF, disc2 = 0xFF, disc3 = 0xFF, 
                    disc4 = 0xFF, disc5 = 0xFF, disc6 = 0xFF, disc7 = 0xFF);
                    
/* Example function call. Reset the second and seventh disc counting from the left 
and set rest of the discs of the first display, counting from the left */
FlipDisc.Flip7(1, 1, 0, 1, 1, 1, 1, 0);
```

The function allows you to control up to seven discs of the selected display. The first argument is the relative number "moduleNumber" of the display in the series of all displays. For example, if we have a combination of FLIP7, SEG, FLIP7, then the second FLIP7 display will have a relative number of 2 even though there is a SEG display between the FLIP7 displays.
 - moduleNumber - relative number of the FLIP7 display
 - disc1, disc2, disc3, disc4, disc5, disc6, disc7 - display discs counting from left to right 1-7

------------------------------------------------------------------------------------------- 


## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/check.png) Supported Displays & Modules      

- [dedicated Arduino controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/)
- [7-segment flip-disc display](https://flipo.io/project/flip-disc-7-segment-display/)
- [2-dot flip-disc display](https://flipo.io/project/flip-disc-2x1-display/)
- [3-dot flip-disc display](https://flipo.io/project/flip-disc-3x1-display/)
- [1x3 flip-disc display](https://flipo.io/project/flip-disc-1x3-display/)
- [1x7 flip-disc display](https://flipo.io/project/flip-disc-1x7-display/)
- [flip-disc power supply module](https://flipo.io/project/flip-disc-power-supply/)  

  


<p align="center">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-arduino-controller.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-7-segment-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-2x1-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-3x1-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x3-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x7-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-power-supply-module.jpg">
</p>  

