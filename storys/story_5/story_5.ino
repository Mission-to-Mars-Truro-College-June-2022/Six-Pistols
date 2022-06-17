


enum MotorPins
{
  FORWARD_RIGHT = 7,
  BACKWARD_RIGHT = 8,
  ENABLE_RIGHT = 9,
  ENABLE_LEFT = 10,
  FORWARD_LEFT = 11,
  BACKWARD_LEFT = 12
}; // the motor pins

enum FeedbackPins
{
  LEFT_FEEDBACK = 3,
  RIGHT_FEEDBACK = 2
};


volatile int leftCount = 0;
volatile int rightCount = 0;

// the setup function runs when you press the board
void setup() 
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK), incrementLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK), incrementRight, RISING);
  
  for (int pin = FORWARD_RIGHT; pin <= BACKWARD_LEFT; pin++) 
  { 
    pinMode(pin, OUTPUT); // pin mode pin output 
    digitalWrite(pin, LOW);
  }
  for(int i = 0; i < 4; i++)
  {
    go(255, 228, 1500);
    go(-255, 228, 750);  
  }
  
}

void incrementLeft()
{
  leftCount++;
}
void incrementRight()
{
  rightCount++;
}

void go(int left, int right, int ms)
{
  Serial.print("left ");
  Serial.print(left);
  Serial.print(" : right ");
  Serial.println(right);
  
  digitalWrite((left < 0) ? BACKWARD_LEFT : FORWARD_LEFT, HIGH);
  digitalWrite((right < 0) ? BACKWARD_RIGHT : FORWARD_RIGHT, HIGH);
  analogWrite(ENABLE_LEFT, abs(left));
  analogWrite(ENABLE_RIGHT, abs(right));
  delay(ms);
  analogWrite(ENABLE_LEFT, 0);
  analogWrite(ENABLE_RIGHT, 0);
  digitalWrite((left < 0) ? BACKWARD_LEFT : FORWARD_LEFT, LOW);
  digitalWrite((right < 0) ? BACKWARD_RIGHT : FORWARD_RIGHT, LOW);
}



// the loop function runs
void loop() 
{

  
  
}
