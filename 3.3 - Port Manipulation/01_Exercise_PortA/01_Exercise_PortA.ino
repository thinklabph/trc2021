int delay_time = 1000;

void setup()
{
  DDRA = DDRA | 0b11111111; //set pin 22 to 29 to OUTPUT

  PORTA = 0b11111111;
  delay(delay_time);
  PORTA = ~PORTA;
  delay(delay_time);
}

void loop()
{
  PORTA = 0b10101010;
  delay(delay_time);
  PORTA |= (1 << PA7);
  delay(delay_time);
  PORTA |= (1 << PA7) | (1 << PA6);
  delay(delay_time);
  PORTA ^= (1 << PA7) | (1 << PA6);
  delay(delay_time);
  PORTA |= (1 << PA7) | (1 << PA6) | (1 << PA0) | (1 << PA3);
  delay(delay_time);
  PORTA = ~PORTA;
  delay(delay_time);
}
