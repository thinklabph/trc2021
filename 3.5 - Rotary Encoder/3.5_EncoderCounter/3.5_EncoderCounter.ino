/* Rotary Encoder Sample Code by ThinkLab */

#define CLK 4
#define DT 3
#define SW 2

int counter = 0;
int currentStateCLK;              // gets the current state of the CLK pin
int lastStateCLK;                 // stores the previous state of the CLK pin
String currentDir = "";
unsigned long lastButtonPress = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
  lastStateCLK = digitalRead(CLK); // Read the initial state of CLK
}

void loop() {
  currentStateCLK = digitalRead(CLK);   // Read the current state of CLK

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 0) {
    // currentStateCLK != lastStateCLK | if last and current state of CLK are different, then pulse occurred
    // currentStateCLK == 1 | React to only 1 state change to avoid double count

    if (digitalRead(DT) != currentStateCLK) { // If the DT state is different than the CLK state then
      counter ++;                             // Encoder is rotating CW so increment
      currentDir = "CW";
    } 
    else {                                  // Encoder is rotating CCW so decrement
      counter --;
      currentDir = "CCW";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  lastStateCLK = currentStateCLK;             // Remember last CLK state

  int btnState = digitalRead(SW);             // Read the button state

  if (btnState == LOW) {                      //If we detect LOW signal, button is pressed

    if (millis() - lastButtonPress > 50) {    //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      Serial.println("Button pressed!");
    }
    lastButtonPress = millis();               // Remember last button press event
  }
  delay(1);                                   // Put in a slight delay to help debounce the reading
}
