#include "FlipDisc.h"

void setup() {  
  FlipDisc.Init(SEG,DOTS,SEG);
  delay(1000);
}

void loop() 
{
  FlipDisc.Dot(1,0,0,0);
  FlipDisc.Seg(3,7);
  delay(1000);
  FlipDisc.Dot(1,1,0,0);
  FlipDisc.Seg(8,5);
  delay(1000); 
  FlipDisc.Dot(1,1,1,0);
  FlipDisc.Seg(4,9);
  delay(1000);
  FlipDisc.Dot(1,1,1,1);
  FlipDisc.Seg(3,1);
  delay(1000);  
}
