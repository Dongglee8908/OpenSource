#include "MultiLed.h"
#include "MultiServo.h"

Flash Red(2, 1000, 1000);
Smooth Green(3, 500, 500, 1, 1);
FlashCount Yellow(4, 1000, 100, 100, 2);
Sweep SG90(9, 1000, 1000, 15, 1);

void setup() {
  SG90.begin();
}

void loop() {
  // don't put the delay function in the loop
  Red.Update();
  Green.Update();
  Yellow.Update();
  SG90.Update();
}
