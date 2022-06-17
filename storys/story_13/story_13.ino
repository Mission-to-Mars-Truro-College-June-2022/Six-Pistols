#include <NewPing.h>

#define MAX_DISTANCE 200

 
  

enum Sonic
{
  FORWARD_TRIGGER = 4,
  FORWARD_ECHO = 5,
  DOWN_TRIGGER = 13,
  DOWN_ECHO = 17
};

enum LDRPins
{
  RIGHT_LDR = 2,
  MIDDLE_LDR = 6,
  LEFT_LDR = 7
};



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

NewPing son_forward(FORWARD_TRIGGER, FORWARD_ECHO, MAX_DISTANCE);
NewPing son_down(DOWN_TRIGGER, DOWN_ECHO, MAX_DISTANCE);

const int QUARTER_TURN = 825; 

void go(int left, int right, int ms)
{
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

void setup() 
{
  Serial.begin(115200);
  son_down.ping_cm();
  son_forward.ping_cm();

  for (int pin = FORWARD_RIGHT; pin <= BACKWARD_LEFT; pin++) 
  { 
    pinMode(pin, OUTPUT); // pin mode pin output 
    digitalWrite(pin, LOW);
  }

    
  int left_ldr;
  int mid_ldr;
  int right_ldr;



  int mean;
  int lowest = 9999;
  int lowest_time = 0;

  for (int i = 0; i < (QUARTER_TURN * 4); i += 5)
  {
    go(-255, +255, 5);
    left_ldr = analogRead(LEFT_LDR);
    mid_ldr = analogRead(MIDDLE_LDR);
    right_ldr = analogRead(RIGHT_LDR);
    mean = (left_ldr + mid_ldr + right_ldr) / 3;

    if (mean < lowest)
    {
      lowest = mean;
      lowest_time = i;
    }
  }
  
  go(255, -255, (QUARTER_TURN * 4) - lowest_time);

  go(255, 230, 1000);
  
  
}

const double CORRECTION = 2.7;
const double LIGHT_SENSITIVITY = 0.95;
const double MAX_SPEED_MULTIPLIER = 0.75;

int highest_value = 0;
int highest_value_ms = 0;


void loop() 
{
  if (son_down.ping_cm() > 14) 
  {
    go(-255, -230, 500);
    exit(0);
  }

  if (son_forward.ping_cm() <= 6) return;
  
  int left_ldr = analogRead(LEFT_LDR);
  int mid_ldr = analogRead(MIDDLE_LDR);
  int right_ldr = analogRead(RIGHT_LDR); // am integer

  int mean = (mid_ldr + left_ldr + right_ldr) / 3; // calculate the mean value of the light values

  /* if a high intensity light is detected on the left ldr, we reduce the left motor speed in order 
   * to steer left and vice-versa for a high intensity on the right side.
   *  
   */
  int left_speed = min(255 * 0.75, 255 * pow(((double)left_ldr / mean), CORRECTION) * MAX_SPEED_MULTIPLIER);
  int right_speed = min(230 * 0.75, 230 * pow(((double)right_ldr / mean), CORRECTION) * MAX_SPEED_MULTIPLIER);

  Serial.print("left_speed: ");
  Serial.print(left_speed);
  Serial.print("right speed: ");
  Serial.println(right_speed);
  

  go(left_speed, right_speed, 50);
}
