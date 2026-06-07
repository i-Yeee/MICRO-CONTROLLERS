#include <Arduino.h>

// put function declarations here:
int lED = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(lED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(lED, HIGH);
  delay(1000);

  digitalWrite(lED, LOW);
  delay(1000);
}

// put function definitions here:
