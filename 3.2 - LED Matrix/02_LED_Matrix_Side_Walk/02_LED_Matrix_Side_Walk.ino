#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW

#define DATA_PIN 51
#define CLK_PIN 52
#define CS_PIN 53

#define DELAYTIME 50

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN);

void setup() {
  Serial.begin(115200);

  mx.begin();
  mx.clear();

}

void loop() {

  for (int x = 0; x <= 7; x++) {
    mx.setPoint(x, 0, true);  
    delay(DELAYTIME);
    mx.clear();
  }

  for (int y = 0; y <= 7; y++) {
    mx.setPoint(7, y, true);
    delay(DELAYTIME);
    mx.clear();
  }

  for (int x = 7; x >= 0; x--) {
    mx.setPoint(x, 7, true);  
    delay(DELAYTIME);
    mx.clear();
  }

  for (int y = 7; y >=0; y--) {
    mx.setPoint(0, y, true);
    delay(DELAYTIME);
    mx.clear();
  }
}
