#ifndef sensor_h
#define sensor_h

// Include Sensors
#include <Wire.h>

#include "CircularArray.h";

class Sensor {
public:
    // Constructor
    Sensor();

    // Initialization method
    void begin();

    // Sensor getters
    int getProximity();
    float getHeading();
    float getWindSpeed();
    float getBatteryVoltage();
    float getTemperature();

    CircularArray<int> proximity;
    CircularArray<float> heading;

    // Data packet creation
    void createPacket(char* buffer);

};

#endif // SENSOR_MANAGER_H

