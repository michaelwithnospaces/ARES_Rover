#ifndef sensor_h
#define sensor_h

// Include Sensors
#include <Wire.h>

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

    // Data packet creation
    void createPacket(char* buffer);

};

#endif // SENSOR_MANAGER_H

