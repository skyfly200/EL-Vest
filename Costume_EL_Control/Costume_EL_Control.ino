/*
  Lighted Costume - EL Wire - Code v0.1
  Started 10/28/2014 11:53 PM

  Purpose: Control a Halloween costumes lights. This part of the code will control the
  EL Sequencer board. It will interface with another microcontroler for commands. 
  The code will run 2 strands of chasing EL Wire, varying the chasing speed on command.
  
  Notes:
  
*/ 

#include <Wire.h>

// Class for managing chasing el wires
class ChasingWire
{
  byte strandPin[3];
  byte strandI;
  boolean wireState;
  boolean cycleDir;
  long cycleRate;
  long lastCycle;
  
  // constructor - takes an array of three pins for the three chanels, a boolean for
  // initial On for strand, a boolaen for direction and a long for rate
  public:
  ChasingWire(byte pin1, byte pin2, byte pin3, boolean initState, boolean dir, long rate)
  {
    strandPin[0] = pin1;
    strandPin[1] = pin2;
    strandPin[2] = pin3;
    strandI = 0;
    wireState = initState;
    cycleDir = dir;
    cycleRate = rate;
    lastCycle = 0;
    
    for(int i=0; i<3; i++)
      pinMode(strandPin[i], OUTPUT);
  }
  
  void setRate(long rate)
  {
    cycleRate = rate;
  }
  
  long getRate()
  {
    return cycleRate;
  }
  
  void setDir(boolean dir)
  {
    cycleDir = dir;
  }
  
  boolean getDir()
  {
    return cycleDir;
  }
  
  // sitch strand to advance wire in set direction
  void cycleWire()
  {
    int prev = strandI;
    if (cycleDir)
    {
      if (strandI < 2) strandI++;
      else strandI = 0;
    }
    else
    {
      if (strandI > 0) strandI--;
      else strandI = 2;
    }
    digitalWrite(strandPin[prev], LOW);
    digitalWrite(strandPin[strandI], HIGH);
    lastCycle = millis();
  }
  
  void wireOff()
  {
    wireState = false;
    for (int j=0; j < 3; j++)
      digitalWrite(strandPin[j], LOW);
  }
  
  void wireOn()
  {
    wireState = true;
  }
  
  boolean getState()
  {
    return wireState;
  }
  
  void Update()
  {
  // cycle at desired speed
  if (wireState && (millis() - lastCycle >= cycleRate))
    cycleWire();
  }
}

// chasing el wire instances
ChasingWire wire1(2, 3, 4, true, true, 500);
ChasingWire wire2(5, 6, 7, true, true, 800);

// global array of wire instances
ChasingWire wires[] = {wire1, wire2};

void setup() {                
  // status LED on pin 13 
  pinMode(13, OUTPUT);    
  
  Wire.begin(1);                // join i2c bus with address #1
  Wire.onReceive(receiveEvent); // register event for bus
  
}

void loop() 
{
  wire1.Update();
  wire2.Update();
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  char ctrlId;
  char value[(Wire.available() - 1)];
  int i = 0;
  
  if (Wire.available())
    char ctrlId = Wire.read(); // read first byte as transmition type id
  while(Wire.available()) // loop through all bytes
  {
    value[i] = Wire.read(); // receive byte as a character
    i++;
  }
  
}

//void masterCtrl(char ctrlId, char value[])
//{
//  switch (ctrlId)
//  {
//    case 68: // direction change
//      cycleDir[value[0]] = value[1];
//      break;
//    case 81: // all off
//      elState[0] = false;
//      elState[1] = false;
//      break;
//    case 82: // rate change
//      cycleRate[value[0]] = ((value[1] << 24) + (value[2] << 16) + (value[3] << 8) + value[4]);
//      break;
//    case 83: // state change
//      elState[value[0]] = value[1];
//      break;
//  }
//}
