...work in progress...:

# Arduino FlipDisc Library v1.0.0
https://github.com/marcinsaj/FlipDisc  
The MIT License  
Marcin Saj 15 Jan 2023  

## Introduction  

## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/about.png) Examples - Code & Diagrams 
 The following example sketches are included with the **FlipDisc** library:


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
## ![](https://github.com/marcinsaj/FlipDisc/blob/main/extras/check.png) Supported displays
- 7-segment flip-disc display - https://flipo.io/project/flip-disc-7-segment-display/
- 2-dot flip-disc display - https://flipo.io/project/flip-disc-2x1-display/
- 3-dot flip-disc display - https://flipo.io/project/flip-disc-3x1-display/
- 1x3 flip-disc display - https://flipo.io/project/flip-disc-1x3-display/
- 1x7 flip-disc display - https://flipo.io/project/flip-disc-1x7-display/


<p align="center">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-7-segment-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-2x1-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-3x1-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x3-display.jpg">
  <img src="https://github.com/marcinsaj/FlipDisc/blob/main/extras/flip-disc-1x7-display.jpg">
</p>
