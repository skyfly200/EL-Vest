/*
  Lighted Costume - EL Wire - Code v0.1
  Started 10/28/2014 11:53 PM

  Purpose: Control a Halloween costumes lights. This part of the code will control the
  leds and the EL Sequencer and will process the butoon presses and audio input. It will interface with another microcontroler for commands. 
  The code will run 2 strands of chasing EL Wire, varying the chasing speed on command.
  
  Notes:
  
*/ 

#include <Wire.h>

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  
}
