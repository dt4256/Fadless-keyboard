#include <Arduino.h>

// Pin definitions
const int POT_PIN = 34;  // Use ADC1 pin (32-39) for ESP32 - GPIO34 is recommended as it has no internal pull-up/pull-down

// Variables for reading
int potValue = 0;        // Raw ADC value (0-4095 for 12-bit ADC)
float voltage = 0.0;     // Calculated voltage
int percentage = 0;      // Percentage value (0-100%)

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    
    // Configure the potentiometer pin as input
    pinMode(POT_PIN, INPUT);
    
    // Wait for serial connection (optional, for debugging)
    while (!Serial) {
        delay(10);
    }
    
    Serial.println("ESP32 Potentiometer Reader Initialized");
    Serial.println("Raw Value | Voltage | Percentage");
    Serial.println("----------|---------|-----------");
}

void loop() {
    // Read the raw ADC value from the potentiometer
    // ESP32 ADC is 12-bit, so the range is 0-4095
    potValue = analogRead(POT_PIN);
    
    // Calculate the corresponding voltage
    // ESP32 ADC reference voltage is typically 3.3V
    // Raw value 0 = 0V, 4095 = 3.3V (theoretical max)
    voltage = (potValue / 4095.0) * 3.3;
    
    // Calculate percentage (0-100%)
    percentage = (potValue / 4095.0) * 100;
    
    // Print the values to the Serial Monitor
    Serial.printf("%9d | %7.2f | %8d%%\n", potValue, voltage, percentage);
    
    // Optional: Add a small delay to make the output readable
    delay(500);
}