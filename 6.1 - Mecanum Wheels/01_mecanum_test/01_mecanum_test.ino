#include <TimerOne.h>

#define RUN_DELAY 2000
#define SET_PWM 60  //0 to 100

#define STNDBY1 36
#define STNDBY2 37

enum Direction
{
  Forward,
  Backward,
  Left,
  Right,
  Forward_Left,
  Forward_Right,
  Backward_Left,
  Backward_Right,
  CW_Center_Center,
  CCW_Center_Center,
  CW_Back_Center,
  CCW_Back_Center,
  CW_Front_Center,
  CCW_Front_Center,
  CW_Center_Left,
  CCW_Center_Left,
  CW_Center_Right,
  CCW_Center_Right,
  Stop
};

unsigned int _pwmvalue = 0;
static bool stopmotor = true;
static int pwmcounter = 0;
bool test_directions = true;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  setupMecanum();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (test_directions)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    // Forward or Backwards
    run(Forward, RUN_DELAY);
    run(Backward, RUN_DELAY);

    // Left or Right
    run(Left, RUN_DELAY);
    run(Right, RUN_DELAY);

    // Forward-Left or Forward-Right
    run(Forward_Left, RUN_DELAY);
    run(Forward_Right, RUN_DELAY);

    // Backward-Left or Backward-Right
    run(Backward_Left, RUN_DELAY);
    run(Backward_Right, RUN_DELAY);

    // Clockwise or Counterclockwise-Center-Center
    run(CW_Center_Center, RUN_DELAY);
    run(CCW_Center_Center, RUN_DELAY);

    // Clockwise or Counterclockwise-Center-Left
    run(CW_Center_Left, RUN_DELAY);
    run(CCW_Center_Left, RUN_DELAY);

    // Clockwise or Counterclockwise-Center-Right
    run(CW_Center_Right, RUN_DELAY);
    run(CCW_Center_Right, RUN_DELAY);

    // Stop All Motors
    run(Stop, 0);
    
    stopMotors();
    
    test_directions = false;
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setupMecanum()
{
  pinMode(STNDBY1, OUTPUT);
  pinMode(STNDBY2, OUTPUT);

  DDRA = DDRA | 0b11111111; //set PORTA to output
  DDRL = DDRL | 0x0F;       //set PORTL to output (Pins 46,47,48,49)

  // DDRA |= 0xFF;
  PORTA = 0b00000000; //set PORT A to LOW
  PORTL &= ~0x0F;     //reverses value of PORTL
  initMotorPwm();

  setMotorPWM(SET_PWM);
}

/*mechanum wheels direction*/
void setMotorDir(Direction _cmd)
{
  switch (_cmd)
  {
  case Forward:
    PORTA = 0xAA;
    break;
  case Backward:
    PORTA = 0x55;
    break;
  case Left:
    PORTA = 0x99;
    break;
  case Right:
    PORTA = 0x66;
    break;
  case Forward_Left:
    PORTA = 0x88;
    break;
  case Forward_Right:
    PORTA = 0x22;
    break;
  case Backward_Left:
    PORTA = 0x44;
    break;
  case Backward_Right:
    PORTA = 0x11;
    break;
  case CW_Center_Center:
    PORTA = 0x69;
    break;
  case CCW_Center_Center:
    PORTA = 0x96;
    break;
  case CW_Back_Center:
    PORTA = 0x5F;
    break;
  case CCW_Back_Center:
    PORTA = 0xAF;
    break;
  case CW_Front_Center:
    PORTA = 0xF5;
    break;
  case CCW_Front_Center:
    PORTA = 0xFA;
    break;
  case CW_Center_Left:
    PORTA = 0x7D;
    break;
  case CCW_Center_Left:
    PORTA = 0xBE;
    break;
  case CW_Center_Right:
    PORTA = 0xEB;
    break;
  case CCW_Center_Right:
    PORTA = 0xD7;
    break;

  case Stop:
    PORTA = 0xFF;
    break;
  default:
    break;
  }
}

void initMotorPwm(void)
{
  Timer1.initialize(100); // 1000us interval for each % of duty cycle
  Timer1.attachInterrupt(MotorPwmHandler);
  Timer1.stop();
}

void prepMotors(void)
{
  stopmotor = false;

  PORTL |= 0x0F;

  // reset pwm
  pwmcounter = 0;
  stopmotor = false;

  // initialize timer
  initMotorPwm();

  // turn on stndbay pins
  // to do: port manipulation
  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
}

void stopMotors(void)
{
  Timer1.stop();
  setMotorDir(Stop);
  delay(200);
  digitalWrite(STNDBY1, LOW);
  digitalWrite(STNDBY2, LOW);
}

void runMotors(void)
{
  pwmcounter = 0;
  digitalWrite(STNDBY1, HIGH);
  digitalWrite(STNDBY2, HIGH);
  Timer1.start();
}

// Handle interrupt every 10% duty cycle
// Initially, PWM pins are high
void MotorPwmHandler(void)
{
  // Evaluate counter
  if (pwmcounter > _pwmvalue)
  {
    PORTL &= ~0x0F; // digital low of pwm
  }
  pwmcounter++;

  // reset pwm counter on overflow
  if (pwmcounter >= 100)
  {
    pwmcounter = 0;
    PORTL |= 0x0F; // digital high of pwm
  }
}

void setMotorPWM(int pwm)
{
  _pwmvalue = pwm;
}

void run(Direction direction, uint16_t duration)
{
  setMotorDir(direction);

  runMotors();

  if (duration > 0)
  {
    delay(duration);
    stopMotors();
  }
}
