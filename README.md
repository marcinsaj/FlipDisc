...work in progress...:  
...work in progress...:  
...work in progress...:  


# Arduino FlipDisc Library v1.0.0
https://github.com/marcinsaj/FlipDisc  
The MIT License  
Marcin Saj 15 Jan 2023  
  
Dear Maker!   
you are dealing with a very large project and not everything can be clear, because it is difficult to provide such extensive documentation about the library itself, several displays and side modules, display methods and many example program codes. If you need help or have any comments, please contact me: <mailto:marcin@flipo.io>  


-------------------------------------------------------------------------------------------  

 
## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/about.png) Introduction  

Arduino library for flip-disc displays.
This library is intended for use with the displays designed by www.Flipo.io - Marcin Saj.  

The library allows you to easily control displays connected in series. You can connect up to 8 different displays in any order. Example codes and diagrams on how to connect the displays with the Arduino and the [Pulse Shaper Power Supply](https://flipo.io/project/flip-disc-power-supply/) module can be found below and on the project website: www.Flipo.io  
  
All the functions responsible for controlling the displays are described in example codes and in the library files [FlipDisc.ccp](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.cpp) & [FlipDisc.h](https://github.com/marcinsaj/FlipDisc/blob/main/src/FlipDisc.h)

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

All diagrams below include the Arduino UNO as a reference. We can use any Arduino board to control the displays. ⚠️ Remember that for proper operation, each of the display connection configurations and the library itself requires the connection of the [Pulse Shaper Power Supply](https://flipo.io/project/flip-disc-power-supply/) module.  
  
In order to simplify the control of the displays, a [dedicated controller](https://flipo.io/project/arduino-controller-for-flip-disc-displays/) was designed as the Arduino Shield for the Arduino Nano Every and Nano 33 IoT boards. The controller has a built-in pulse shaper power module and several other features.
  
Therefore, the user has two options:
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

:seven: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/07-1x2dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram]() :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-3dots-flip-disc-psps-module.png"></p>  

:eight: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/08-1x3dots-flip-disc-arduino-psps.ino) &nbsp; [Download diagram]() :small_red_triangle_down:

-------------------------------------------------------------------  

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x3-flip-disc-psps-module.png"></p>  

:nine: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/09-1x1x3-flip-disc-arduino-psps.ino) &nbsp; [Download diagram]() :small_red_triangle_down:

-------------------------------------------------------------------    

<p><img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/arduino-1x7-flip-disc-psps-module.png"></p>  

:one::zero: [Show me code](https://github.com/marcinsaj/FlipDisc/blob/main/examples/10-1x1x7-flip-disc-arduino-psps.ino) &nbsp; [Download diagram]() :small_red_triangle_down:

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
```c++
#define EN_PIN  'Set your pin'  // Start & End SPI transfer data
#define CH_PIN  'Set your pin'  // Charging PSPS module - turn ON/OFF
#define PL_PIN  'Set your pin'  // Release the current pulse - turn ON/OFF
```  
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

