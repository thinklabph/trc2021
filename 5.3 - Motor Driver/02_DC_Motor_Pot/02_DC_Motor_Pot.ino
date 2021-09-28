#define PWMA 5
#define PWMB 6
#define STANDBY_PIN 3
#define POT_PIN A0

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
  rotate_CW();
  Serial.println("Done Initializing!");
}

void loop()
{
  // put your main code here, to run repeatedly:
  int potValue = analogRead(POT_PIN);
  
  int pwmValue = map(potValue, 0, 1023, 0, 255);

  analogWrite(PWMA, pwmValue);
  analogWrite(PWMB, pwmValue);
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