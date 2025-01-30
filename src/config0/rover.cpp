#include "Arduino.h"
#include "rover.h"

Rover::Rover()
{
    state = 0;
    obstacleDetected = false;
}

void Rover::setState(int newState)
{
    this->state = newState;
}

int Rover::getState()
{
    return this->state;
}

void Rover::traversal()
{
    // TODO
}

void Rover::obstacleAvoidance()
{
    // TODO
}

void Rover::sensorCollection()
{
    sensor.createPacket(telemetryBuffer, sizeof(telemetryBuffer));
}

void Rover::sensorTransmission()
{
    Serial.print(telemetryBuffer);
}

void Rover::detectBeacon()
{
    // TODO
}

void Rover::turn()
{
    // TODO : Tyler
}