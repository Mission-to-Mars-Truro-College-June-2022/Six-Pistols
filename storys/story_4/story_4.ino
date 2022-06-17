enum MotorPins
{
  FORWARD_RIGHT = 7,
  BACKWARD_RIGHT = 8,
  ENABLE_RIGHT = 9,
  ENABLE_LEFT = 10,
  FORWARD_LEFT = 11,
  BACKWARD_LEFT = 12
}; // the motor pins

// the setup function runs when you press the board
void setup() 
{
  for (int pin = FORWARD_RIGHT; pin <= BACKWARD_LEFT; pin++) 
  { 
    pinMode(pin, OUTPUT); // pin mode pin output 
    digitalWrite(pin, LOW);
  }

  digitalWrite(ENABLE_RIGHT, HIGH); // digital write enable right high
  digitalWrite(ENABLE_LEFT, HIGH); // digital write enable left high
}

// the loop function runs
void loop() 
{
  
  digitalWrite(BACKWARD_RIGHT, HIGH);
  digitalWrite(BACKWARD_LEFT, HIGH);
  delay(1000); // this is true
  digitalWrite(BACKWARD_RIGHT, LOW); // turn off
  digitalWrite(BACKWARD_LEFT, LOW);
  delay(1000); // this is right
  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(FORWARD_LEFT, HIGH);
  delay(1000);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(FORWARD_LEFT, LOW);
  delay(1000);
                         // a second
}
