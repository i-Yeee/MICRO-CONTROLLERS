#include <Arduino.h>

// Define the single GPIO pin for your LED
const int ledPin = 15;

// Use a single hardware PWM channel
#define PWM_CHAN 0

// Define the analog input pin for the potentiometer
const int potPin = 1; 

// PWM Settings
const int freq = 1000;     // 1 kHz frequency
const int resolution = 12; // 12-bit resolution (0 - 4095)

void setup() {
  Serial.begin(115200);

  // Configure the single PWM channel
  ledcSetup(PWM_CHAN, freq, resolution);

  // Attach your physical LED pin to that channel
  ledcAttachPin(ledPin, PWM_CHAN);
}

void loop() {
  static int filteredVal = 0;
  int rawVal = analogRead(potPin);

  // Exponential Moving Average filter to smooth out any electrical jitter
  filteredVal = (filteredVal * 3 + rawVal) / 4; 

  // Write the filtered duty cycle to the single PWM channel
  ledcWrite(PWM_CHAN, filteredVal);

  Serial.printf("Raw ADC: %d | Filtered PWM: %d\n", rawVal, filteredVal);
  delay(20); 
}