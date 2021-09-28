#include <Servo.h>

#define LIFTER_PIN 7
#define LIFTER_ANGLE 100   //90 degrees max
#define LIFTER_SPEED  5  //milliseconds
#define DELAY 3000

enum LiftState{
  Up,
  Down
};

Servo myservo; // create servo object to control a servo

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  myservo.attach(LIFTER_PIN);
  Serial.println("Done Initialization");
}

void loop()
{
  // put your main code here, to run repeatedly:
  lift(Up, LIFTER_ANGLE, LIFTER_SPEED);
  delay(DELAY);
  lift(Down, LIFTER_ANGLE, LIFTER_SPEED);
  delay(DELAY);
}

void lift(LiftState state, int _angle, int _speed)
{
  int COUNTER_WIDTH_MIN = 500;   //0 angle
  int COUNTER_WIDTH_MAX = 2500;  //270 angle

  if (_angle < 0)
    _angle = 0;
  else if (_angle > 270)
    _angle = 270;

  int pulseWidth = map(_angle, 0, 270, COUNTER_WIDTH_MIN, COUNTER_WIDTH_MAX);
  Serial.println(pulseWidth);
  
  if (state == Up)
  {
    for (int pos = COUNTER_WIDTH_MIN; pos <= pulseWidth; pos += 1)
    {
      myservo.writeMicroseconds(pos);
      delay(_speed);  //increment delay in milliseconds
    }
  }
  else if (state == Down)
  {
    for (int pos = pulseWidth; pos >= COUNTER_WIDTH_MIN; pos -= 1)
    {
      myservo.writeMicroseconds(pos);
      delay(_speed);  //increment delay in milliseconds
    }
  }
}
