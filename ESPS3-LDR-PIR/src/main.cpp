#include <Arduino.h>

// Pin Definitions
const int LDR_PIN = 4;       // Analog pin for Light Dependent Resistor
const int PIR_PIN = 5;       // Digital pin for PIR Motion Sensor
const int LED_PIN = 6;       // Digital pin for the LED light

// Thresholds & Calibration
const int DARKNESS_THRESHOLD = 1500; // Adjust this value based on your room's ambient light (0-4095)
const unsigned long LIGHT_ON_DURATION = 10000; // Time the light stays on in milliseconds (10 seconds)

// Variable Tracking
unsigned long motionTimer = 0;
bool isLightOn = false;

void setup() {
    Serial.begin(115200);
    
    pinMode(PIR_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    
    // Ensure LED starts OFF
    digitalWrite(LED_PIN, LOW);
    
    Serial.println("--- System Initialized ---");
}

void loop() {
    // Read the LDR value (ESP32-S3 ADC resolution is 12-bit: 0 to 4095)
    // Higher value usually means more light, lower means darker (depending on wiring)
    // If wired with LDR to 3V3 and Resistor to GND: Lower voltage = Darker
    int lightLevel = analogRead(LDR_PIN);
    
    // Read the PIR motion sensor (HIGH = Motion, LOW = No Motion)
    int motionDetected = digitalRead(PIR_PIN);

    // Debugging printouts to the Serial Monitor
    Serial.printf("Light Level: %d | Motion: %s\n", lightLevel, motionDetected ? "DETECTED" : "NONE");

    // Check if it is dark enough
    if (lightLevel < DARKNESS_THRESHOLD) {
        
        // If it's dark AND motion is currently detected, turn on/reset the timer
        if (motionDetected == HIGH) {
            digitalWrite(LED_PIN, HIGH);
            if (!isLightOn) {
                Serial.println("=> Dark and Motion detected! Turning light ON.");
                isLightOn = true;
            }
            // Constantly refresh the timer as long as there is movement
            motionTimer = millis(); 
        }
    }

    // If the light is on, check if the duration has expired
    if (isLightOn) {
        if (millis() - motionTimer >= LIGHT_ON_DURATION) {
            digitalWrite(LED_PIN, LOW);
            isLightOn = false;
            Serial.println("=> No recent motion. Turning light OFF.");
        }
    }

    delay(200); // Small delay to avoid flooding the serial monitor
}