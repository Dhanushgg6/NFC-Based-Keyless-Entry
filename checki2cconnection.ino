#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Serial.println("Scanning for I2C devices...");

    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print("✅ I2C Device Found at Address: 0x");
            Serial.println(address, HEX);
        }
    }
}

void loop() {}
