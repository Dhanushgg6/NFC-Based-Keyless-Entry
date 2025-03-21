#include <Wire.h>
#include <Adafruit_PN532.h>
#include <ESP32Servo.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define SERVO_PIN 5  // Using same pin as your working code

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
Servo myServo;

String authorizedUID = "4D:39:B4:2"; // Replace with your NFC tag UID

void setup() {
    Serial.begin(115200);
    nfc.begin();
    nfc.SAMConfig();  

    myServo.attach(SERVO_PIN);
    myServo.write(0); // Start at locked position

    Serial.println("NFC Keyless Entry System Ready...");
}

void loop() {
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};  
    uint8_t uidLength;

    if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
        String scannedUID = "";
        for (uint8_t i = 0; i < uidLength; i++) {
            if (i > 0) scannedUID += ":";
            scannedUID += String(uid[i], HEX);
        }
        scannedUID.toUpperCase();

        Serial.print("Detected UID: ");
        Serial.println(scannedUID);

        if (scannedUID.equalsIgnoreCase(authorizedUID)) {
            Serial.println("✅ Access Granted! Unlocking...");
            unlockVehicle();
        } else {
            Serial.println("❌ Access Denied!");
        }
        delay(3000);
    }
}

void unlockVehicle() {
    myServo.write(90); // Unlock position
    Serial.println("🔓 Vehicle Unlocked!");

    delay(5000); // Keep unlocked for 5 seconds

    myServo.write(0); // Lock position
    Serial.println("🔒 Vehicle Locked.");
}
