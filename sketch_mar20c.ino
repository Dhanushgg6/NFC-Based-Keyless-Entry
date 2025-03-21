#include <Wire.h>
#include <Adafruit_PN532.h>

#define SDA_PIN 21  // ESP32 I2C SDA Pin
#define SCL_PIN 22  // ESP32 I2C SCL Pin

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

void setup() {
    Serial.begin(115200);
    Serial.println("🔍 Checking NFC Module...");

    nfc.begin();
    nfc.SAMConfig();  // Configure NFC module for read mode

    Serial.println("✅ NFC Module Initialized!");
}

void loop() {
    Serial.println("🔍 Scanning for NFC Tag...");
    
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0};  
    uint8_t uidLength;

    if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
        Serial.println("✅ NFC Tag Detected!");
        
        Serial.print("🔹 UID: ");
        for (uint8_t i = 0; i < uidLength; i++) {
            Serial.print(uid[i], HEX);
            Serial.print(i < uidLength - 1 ? ":" : "\n");  // Print UID with colons
        }
        
        delay(2000);  // Wait before scanning again
    } else {
        Serial.println("❌ No NFC Tag Found.");
    }
    
    delay(1000); // Scan every second
}
