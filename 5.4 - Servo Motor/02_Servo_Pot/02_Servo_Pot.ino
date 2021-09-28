#include <Servo.h>

#define DELAY_TIME 15
#define SERVO_PIN 9
#define COUNTER_WIDTH_MIN 500   //0 angle
#define COUNTER_WIDTH_MAX 2500  //270 angle

Servo myservo; // create servo object to control a servo

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  Serial.println("Done Initialization");
}

void loop()
{
  // put your main code here, to run repeatedly:
  int analogValue = analogRead(A0);

  int servoAngle = map(analogValue, 0, 1023, 0, 270);

  setServoAngle(servoAngle);

  Serial.print(analogValue);
  Serial.print(" ");
  Serial.println(servoAngle);

  delay(DELAY_TIME);
}

void setServoAngle(int _angle)
{
  if (_angle < 0)
    _angle = 0;
  else if (_angle > 270)
    _angle = 270;

  int pulseWidth = map(_angle, 0, 270, COUNTER_WIDTH_MIN, COUNTER_WIDTH_MAX);
  // Serial.println(pulseWidth);
  myservo.writeMicroseconds(pulseWidth);
}