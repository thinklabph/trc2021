#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SCREEN_ADDRESS 0x3C // LCD I2C Address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.setTextColor(WHITE);
  
  
}

void loop() {
  display.setTextSize(1);
  
  display.clearDisplay();
  display.setCursor(0,0);

  display.println(1);
  display.println(2);
  display.println(3);
  display.println(4);
  display.println(5);
  display.println(6);
  display.println(7);
  display.println(8);
  display.println(9);
  display.println(10);

  display.display();

  delay(3000);

  display.setTextSize(2);

  display.clearDisplay();
  display.setCursor(0,0);

  display.println(1);
  display.println(2);
  display.println(3);
  display.println(4);
  display.println(5);
  display.println(6);
  display.println(7);
  display.println(8);
  display.println(9);
  display.println(10);

  display.display();
  
  delay(3000);
}
