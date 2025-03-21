#include <Wire.h>
#include <Adafruit_PN532.h>
#include <Preferences.h> // For storing UID in ESP32 flash memory

#define SDA_PIN 21
#define SCL_PIN 22
#define RELAY_PIN 23  // GPIO pin connected to relay module

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
Preferences preferences;

String authorizedUID = "4d39b42"; // Replace with your NFC tag UID

void setup() {
    Serial.begin(115200);
    nfc.begin();
    nfc.SAMConfig(); // Configure NFC module for read mode

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Ensure the lock starts in the locked state

    Serial.println("NFC Keyless Entry System Ready...");
}

void loop() {
    uint8_t uid[7];  
    uint8_t uidLength;

    if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
        String scannedUID = "";
        for (uint8_t i = 0; i < uidLength; i++) {
            // Format UID to ensure it is always in lowercase
            scannedUID += String(uid[i], HEX);
        }

        // Ensure the UID is in lowercase
        scannedUID.toLowerCase();

        Serial.print("Detected UID: ");
        Serial.println(scannedUID);

        if (scannedUID.equalsIgnoreCase(authorizedUID)) {
            Serial.println("✅ Access Granted! Unlocking...");
            unlockVehicle();
        } else {
            Serial.println("❌ Access Denied!");
        }
        delay(3000); // Wait before scanning again
    }
}

void unlockVehicle() {
    digitalWrite(RELAY_PIN, HIGH); // Activate relay (Unlock vehicle)
    Serial.println("🔓 Vehicle Unlocked!");

    delay(5000); // Keep unlocked for 5 seconds

    digitalWrite(RELAY_PIN, LOW); // Deactivate relay (Lock vehicle)
    Serial.println("🔒 Vehicle Locked.");
}