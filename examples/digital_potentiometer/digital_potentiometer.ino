#include <Arduino.h>
#include <Wire.h>
#include "WireHelper.h"

void setup()
{
	
}

int val;
void loop() 
{
  WireHelper::write(44, 0, val);
  
  // The below code is verbatim from 
  // https://github.com/arduino/Arduino/blob/master/libraries/Wire/examples/digital_potentiometer/digital_potentiometer.ino
  val++;        // increment value
  if(val == 64) // if reached 64th position (max)
  {
    val = 0;    // start over from lowest value
  }
  delay(500);
}
