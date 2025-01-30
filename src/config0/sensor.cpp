#include "sensor.h"

Sensor::Sensor() {}

void Sensor::begin() {}

int Sensor::getProximity() {}

float Sensor::getUVIndex() {}

float Sensor::getWindSpeed() {}

float Sensor::getBatteryVoltage() {}

float Sensor::getTemperature() {}

float Sensor::getHumidity() {}

float Sensor::getPressure() {}

// Creates a telemetry packet in a char buffer
void Sensor::createPacket(char* buffer, size_t bufferSize) 
{
    snprintf(buffer, bufferSize,
        "P:%d\n"
        "U:%.1f\n"
        "W:%.1f\n"
        "V:%.2f\n"
        "T:%.1f\n"
        "H:%.1f\n"
        "Pr:%.1f\n",
        getProximity(),
        getUVIndex(),
        getWindSpeed(),
        getBatteryVoltage(),
        getTemperature(),
        getHumidity(),
        getPressure()
    );
}
