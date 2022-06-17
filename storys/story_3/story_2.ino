/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  
  
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

enum MotorPins
{
  ENABLE_RIGHT = 9,
  ENABLE_LEFT = 10,
  FORWARD_RIGHT = 7,
  BACKWARD_RIGHT = 8,
  FORWARD_LEFT = 11,
  BACKWARD_LEFT = 12
}; // the motor pins

// the setup function runs when you press the board
void setup() 
{
  for (int pin = ENABLE_RIGHT; pin < BACKWARD_LEFT; pin++) 
  { 
    pinMode(pin, OUTPUT); // pin mode pin output 
  }

  digitalWrite(ENABLE_RIGHT, HIGH); // digital write enable right high
  digitalWrite(ENABLE_LEFT, HIGH); // digital write enable left high
}

// the loop function runs
void loop() 
{
  
  digitalWrite(BACKWARD_RIGHT, HIGH);
  digitalWrite(BACKWARD_LEFT, HIGH);
  delay(1000);
  digitalWrite(BACKWARD_RIGHT, LOW); // turn off
  digitalWrite(BACKWARD_LEFT, LOW);
  delay(1000);
  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(FORWARD_LEFT, HIGH);
  delay(1000);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(FORWARD_LEFT, LOW);
                         // a second
}
