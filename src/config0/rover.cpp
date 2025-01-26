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
    // TODO
}

void Rover::sensorTransmission()
{
    // TODO
}

void Rover::detectBeacon()
{
    // TODO
}

void Rover::turn()
{
    // TODO : Tyler
}