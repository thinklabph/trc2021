#define PWMA 5
#define PWMB 6
#define STANDBY_PIN 3

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(STANDBY_PIN, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Pins 22, 23 - Motor A Conrtols
  // Pins 24, 25 - Motor B Controls
  DDRA = DDRA | 0b00001111; //set PORT A 0-3 to output
  PORTA = 0b00000000;       //set PORT A to LOW
  
  digitalWrite(STANDBY_PIN, HIGH);
  Serial.println("Done Initializing!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Rotating Clockwise!");
  rotate_CW();
  //accelerate from zero to maximum speed
  for (int i = 0; i <= 255; i++)
  {
    Serial.println(i);
    analogWrite(PWMA, i);
    analogWrite(PWMB, i);
    delay(50);
  }
  //decelerate from maximum to zero
  for (int i = 255; i >= 0; --i)
  {
    Serial.println(i);
    analogWrite(PWMA, i);
    analogWrite(PWMB, i);
    delay(50);
  }
  //short brake motor
  Serial.println("Break!");
  stop_motor();
  delay(2000);

  //accelerate from zero to maximum speed
  Serial.println("Rotating Counterclockwise!");
  rotate_CCW();
  for (int i = 0; i <= 255; i++)
  {
    Serial.println(i);
    analogWrite(PWMA, i);
    analogWrite(PWMB, i);
    delay(50);
  }
  //decelerate from maximum to zero
  for (int i = 255; i >= 0; --i)
  {
    Serial.println(i);
    analogWrite(PWMA, i);
    analogWrite(PWMB, i);
    delay(50);
  }
  //stop all motors
  Serial.println("Stop!");
  stop_motor();
  delay(2000);
}

void rotate_CW()
{
  //rotate clockwise
  PORTA = 0b00001010;
}

void rotate_CCW()
{
  //rotate counterclockwise
  PORTA = 0b00000101;
}

void break_motor()
{
  //break
  PORTA = 0b00000000;
}

void stop_motor()
{
  //stop
  PORTA = 0b00001111;
}