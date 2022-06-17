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

  
  
}

const double LIGHT_SENSITIVITY = 0.95;
int highest_value = 0;
int highest_value_ms = 0;


void loop() 
{
  
  int left_ldr;
  int mid_ldr;
  int right_ldr;

  /*
  Serial.print(left_ldr);
  Serial.print(", ");
  Serial.print(mid_ldr);
  Serial.print(", ");
  Serial.print(right_ldr);

  int lowest = min(min(left_ldr, mid_ldr), right_ldr);
  int mean = (left_ldr + mid_ldr + right_ldr) / 3;
  */

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
  /*
  do
  {
    go(255, 230, 50);
  } while(son_forward.ping_cm() >= 12);
  */
  go(255, 230, 1000);
  
  

  /*
  if (left_ldr < mean * LIGHT_SENSITIVITY) 
  {
    Serial.println("LEFY");
    go(-255, 230, 50);
  }
  else if (right_ldr < mean * LIGHT_SENSITIVITY) 
  {
    Serial.println("ROGUIHT");
    go(255, -230, 50);
  }
  else if (son_forward.ping_cm() >= 25)
  {
    
    
    Serial.println("FORWAWREDE");
    go(128, 115, 50);
  }
  else
  {
    Serial.println("SEJEEARCHING");
    go(255, -230, 100);
  }
  

  
  /*
  int down_ping = son_down.ping_cm();
  if (down_ping > 13
  )
  {
    go(-230, -255, 500);
    exit(0);
  }
  else go(255, 230, 50);

  /*
  go(255, 230, 50);

  
  int pinged = sonar.ping_cm();
  Serial.println(pinged);
  
  if (pinged <= 20 && pinged != 0) go(-255, 255, 840);
  else go(255, 230, 50);
  */
}
