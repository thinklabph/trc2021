#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define DATA_PIN 51
#define CLK_PIN 52
#define CS_PIN 53

#define DELAYTIME 1000

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN);

void setup() {
  Serial.begin(115200);

  mx.begin();
  mx.clear();

}

void loop() {

  mx.setPoint(0, 0, true);

  delay(DELAYTIME);

  mx.setPoint(0, 0, false);

  delay(DELAYTIME);

}
