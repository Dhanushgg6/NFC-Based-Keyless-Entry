#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 5;
const int buttonPin = 0;  // BOOT button on ESP32

void setup() {
    pinMode(buttonPin, INPUT);
    myServo.attach(servoPin);
    myServo.write(0); // Start at 0 degrees
}

void loop() {
    if (digitalRead(buttonPin) == LOW) {  // BOOT button is pressed (LOW)
        myServo.write(90);  // Move to 90°
    } else {
        myServo.write(0);  // Move back to 0°
    }
    delay(50); // Debounce delay
}