#include "model.h"
#include <LSM6DS3.h>
#include <Wire.h>

#define RED_LED   LED_BUILTIN
#define GREEN_LED 17
#define BLUE_LED  23

const int NUM_FEATURES = 1206;
float sensor_data[NUM_FEATURES];

Eloquent::ML::Port::RandomForest model;
LSM6DS3 myIMU(I2C_MODE, 0x6A);

void collectData() {
    Serial.println("Collecting data...");
    for (int i = 0; i < 201; i++) {
        float accX = myIMU.readFloatAccelX();
        float accY = myIMU.readFloatAccelY();
        float accZ = myIMU.readFloatAccelZ();
        float gyroX = myIMU.readFloatGyroX();
        float gyroY = myIMU.readFloatGyroY();
        float gyroZ = myIMU.readFloatGyroZ();

        sensor_data[i * 6 + 0] = accX;
        sensor_data[i * 6 + 1] = accY;
        sensor_data[i * 6 + 2] = accZ;
        sensor_data[i * 6 + 3] = gyroX;
        sensor_data[i * 6 + 4] = gyroY;
        sensor_data[i * 6 + 5] = gyroZ;

        delay(20); // ~50Hz sampling
    }
}

void showState(int prediction) {
    // Reset all LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    if (prediction == 0) {
        Serial.println("State: Normal");
        digitalWrite(GREEN_LED, HIGH); // Activity in normal State
    } else if (prediction == 1) {
        Serial.println("State: Accident");
        digitalWrite(RED_LED, HIGH); // Activity after accident State
    } else if (prediction == 2) {
        Serial.println("State: Hit");
        digitalWrite(BLUE_LED, HIGH);  // Activity after Hit State
    } else {
        Serial.println("State: Unknown");
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    while (!Serial);
    if (myIMU.begin() != 0) {
        Serial.println("Failed to initialize IMU!");
        while (1);
    }
    Serial.println("IMU initialized successfully!");
}

void loop() {
    collectData();
    int prediction = model.predict(sensor_data);
    showState(prediction);
    delay(20);
}
