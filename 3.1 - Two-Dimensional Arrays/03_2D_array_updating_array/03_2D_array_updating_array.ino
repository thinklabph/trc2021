int pinLedArray[5] = {2, 3, 4, 5, 6};

int arr[2][3] = {
  {1, 2, 3}, 
  {4, 5, 6}
};

void setup() {

  Serial.begin(115200);

  int num = arr[1][2];
  Serial.println(num);

  arr[1][2] = 100;

  num = arr[1][2];
  Serial.println(num);
  
}

void loop() {

}
