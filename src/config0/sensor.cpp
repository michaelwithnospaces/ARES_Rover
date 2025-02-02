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

// Creates a telemetry packet in a 49-char buffer
void Sensor::createPacket(char* buffer) 
{
    // Pad to 49 bytes
    snprintf(buffer, 49,
        "P:%d\n"
        "U:%.1f\n"
        "W:%.1f\n"
        "V:%.2f\n"
        "T:%.1f\n"
        "H:%.1f\n"
        "Pr:%.1f\n",
        "                                                ",
        // 48 empty bits (almost 49, leaving space for \0)
        // padding at the end, if there's no space, it will get trimmed
        getProximity(),
        getUVIndex(),
        getWindSpeed(),
        getBatteryVoltage(),
        getTemperature()
    );
}
