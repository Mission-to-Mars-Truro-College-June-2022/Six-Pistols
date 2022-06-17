#include <NewPing.h>

#define MAX_DISTANCE 100

// RIP olly, didn't turn up.
  

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

// initialise the ultrasound 
NewPing son_forward(FORWARD_TRIGGER, FORWARD_ECHO, MAX_DISTANCE);
NewPing son_down(DOWN_TRIGGER, DOWN_ECHO, MAX_DISTANCE);


/* go function to make the rover move.
 * positive speed makes that motor move forward
 * negative makes it go backwards.
 *  
 */
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

  // ping the ultrasound initially just to make sure it's initialised
  son_down.ping_cm();
  son_forward.ping_cm();

  // setup the motor pins in the correct mode.
  for (int pin = FORWARD_RIGHT; pin <= BACKWARD_LEFT; pin++) 
  { 
    pinMode(pin, OUTPUT); // pin mode pin output - RIP dan monday 13th june 2022
    digitalWrite(pin, LOW); // uh set them to low cause why not
  }  
  
}

const int QUARTER_TURN_RIGHT = 690; 
const int QUARTER_TURN_LEFT = 640; 
const int LEFT_MAX = 255;
const int RIGHT_MAX = 240;
const int TURN_MAX = 255;

void loop() 
{
  int forward_check = son_forward.ping_cm();
  if (forward_check < 25 && forward_check != 0)
  {
    // left turn when about to hit wall
    go(-LEFT_MAX, -RIGHT_MAX, 200);
    go(-TURN_MAX, TURN_MAX, QUARTER_TURN_LEFT + 150);
    delay(500);
  }
  else
  {
    // checks wall to the side.
    go(TURN_MAX, -TURN_MAX, QUARTER_TURN_RIGHT);
    delay(100);
    // after turning, ping in front to detect whether we're by a wall or not.
    int ultra = son_forward.ping_cm();
    
    // reverses this turn so we are straight again
    go(-TURN_MAX, TURN_MAX, QUARTER_TURN_LEFT);
    delay(100);
    if (ultra <= 10 && ultra != 0) // if we are too close to the wall, correct us. 
    {
      go(-LEFT_MAX, -RIGHT_MAX, 500);
      go(-TURN_MAX, TURN_MAX, QUARTER_TURN_LEFT/4);
    }
    else if (ultra >= 50 || ultra == 0) // if there is no wall to the right of us.
    {
      // no wall in front so we should turn right after moving into open space
      go(LEFT_MAX, RIGHT_MAX, 700);
      go(TURN_MAX, -TURN_MAX, QUARTER_TURN_RIGHT); // sheeeeesh
      go(LEFT_MAX, RIGHT_MAX, 400);
      delay(100);
    }
    else go(LEFT_MAX, RIGHT_MAX, 400); // go forward
    
  }

}
