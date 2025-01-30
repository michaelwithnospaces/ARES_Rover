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
    float getUVIndex();
    float getWindSpeed();
    float getBatteryVoltage();
    float getTemperature();
    float getHumidity();
    float getPressure();

    // Data packet creation
    void createPacket(char* buffer, size_t bufferSize);

};

#endif // SENSOR_MANAGER_H

