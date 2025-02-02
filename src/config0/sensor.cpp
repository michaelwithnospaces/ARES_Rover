#include "sensor.h"

Sensor::Sensor() {}

void Sensor::begin() {}

int Sensor::getProximity() {}

float Sensor::getHeading() {}

float Sensor::getWindSpeed() {}

float Sensor::getBatteryVoltage() {}

float Sensor::getTemperature() {}

// Creates a telemetry packet in a 49-char buffer
void Sensor::createPacket(char* buffer) 
{
    // Pad to 42 bytes
    snprintf(buffer, 42,
        "P:%d\n"
        "H:%.1f\n"
        "W:%.1f\n"
        "V:%.2f\n"
        "T:%.1f\n"
        "                                         ",
        // 41 empty bits (almost 42, leaving space for \0)
        // padding at the end, if there's no space, it will get trimmed
        getProximity(),
        getHeading(),
        getWindSpeed(),
        getBatteryVoltage(),
        getTemperature()
    );
}
