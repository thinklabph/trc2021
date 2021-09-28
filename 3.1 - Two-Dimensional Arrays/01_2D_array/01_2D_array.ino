int pinLedArray[5] = {2, 3, 4, 5, 6};

void setup() {

  Serial.begin(115200);

  int num = pinLedArray[4];

  Serial.println(num);
  
}

void loop() {

}
