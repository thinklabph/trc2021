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

int lightPoints[4][2] = {
  {0, 0},
  {6, 3},
  {4, 5},
  {2, 4}
};

void loop() {

  for (int i = 0; i < 4; i++) {
    
    int x = lightPoints[i][0];
    int y = lightPoints[i][1];

    mx.setPoint(x, y, true);

    delay(DELAYTIME);

    mx.clear();
  }

}
