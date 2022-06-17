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

const int CHECK_TIME = 50;
const int ADJUST = 2;
const int MAX_SPEED = 255;

const int QUARTER_TURN = 840; // the thing worked at 720

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
  for(int i = 0; i < 3; i++)
  {
    go(255, 228, 1750);
    go(-255, 228, QUARTER_TURN);
  }
    go(255, 228, 2500);
    for(int i = 0; i < 2; i++)
  {
    go(255, 228, 1750);
    go(255, -228, QUARTER_TURN);
  }
  go(255, 228, 2250);
  go(255, -228, QUARTER_TURN - 55);
  go(255, 228, 1500);

  delay(1000);

  go(-228, -255, 1500);
  go(-228, 255, QUARTER_TURN - 55);
  go(-228, -255, 2350);
  for(int i = 0; i < 2; i++)
  {
    go(-228, 255, QUARTER_TURN);
    go(-228, -255, 1750);
  }
  go(-228, -255, 2500);
  for(int i = 0; i < 2; i++)
  {
    go(228, -255, QUARTER_TURN + 60);
    go(-228, -255, 2000);
  }
  go(228, -255, QUARTER_TURN + 100);
  go(-228, -255, 1700);
  
  
  
  
  
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

void snake()
{
  digitalWrite(FORWARD_RIGHT, HIGH);
  digitalWrite(FORWARD_LEFT, HIGH);
  digitalWrite(ENABLE_RIGHT, HIGH);
  digitalWrite(ENABLE_LEFT, HIGH);
  delay(1999);
  analogWrite(ENABLE_LEFT, 64);
  analogWrite(ENABLE_RIGHT, 255);
  delay(3000);
  analogWrite(ENABLE_LEFT, 255);
  analogWrite(ENABLE_RIGHT, 64);
  delay(3000);
  analogWrite(ENABLE_LEFT, 64);
  analogWrite(ENABLE_RIGHT, 255);
  delay(3000);
  analogWrite(ENABLE_LEFT, 255);
  analogWrite(ENABLE_RIGHT, 64);
  delay(2000);
  digitalWrite(FORWARD_RIGHT, LOW);
  digitalWrite(FORWARD_LEFT, LOW);
  digitalWrite(ENABLE_RIGHT, LOW);
  digitalWrite(ENABLE_LEFT, LOW);
  delay(2000);
}


// the loop function runs
void loop() 
{
  /*
  if (millis() > 10000) 
  {
    for (int pin = FORWARD_RIGHT; pin <= BACKWARD_LEFT; pin++) 
    {  
      digitalWrite(pin, LOW);
    }
    return;
  }
  
  int dist = leftCount - rightCount;
  go(MAX_SPEED - abs(max(0, dist * ADJUST)), MAX_SPEED - abs(min(0, dist * ADJUST)), CHECK_TIME);
  */
}
