#ifndef sensor_h
#define sensor_h

// Include Sensors
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_Sensor.h>

#include "CircularArray.h";

class Sensor {
public:
    // Constructor
    Sensor();

    // Initialization method
    void begin();

    // Sensor getters
    float getBeaconDistance();
    float* getProximity();
    float getHeading();
    float getWindSpeed();
    float getBatteryVoltage();
    float getTemperature();

    CircularArray<float> beaconDistance;
    CircularArray<float> proximityL;
    CircularArray<float> proximityR;
    CircularArray<float> heading;

    // Data packet creation
    void createPacket(char* buffer);

};

#endif // SENSOR_MANAGER_H

