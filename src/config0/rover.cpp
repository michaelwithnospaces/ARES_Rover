#include "Arduino.h"
#include "rover.h"

Rover::Rover()
{
    state = 0;
    obstacleDetected = false;
    hasHeading = false;
    atDest = false;
    dataIter = 0;
    reqIter = 5;
}

void Rover::setState(int newState)
{
    this->state = newState;
}

int Rover::getState()
{
    return this->state;
}

void Rover::detectBeacon()
{
    // TODO
    if(hasHeading) state = 1;
    if(obstacleDetected) state = 1;
}

void Rover::traversal()
{
    // TODO
    if(obstacleDetected) state = 1;
    if(atDest) state = 3;
}

void Rover::obstacleAvoidance()
{
    // TODO
    if(!obstacleDetected){
        if(hasHeading) state = 1;
        else state = 0;
    }
}

void Rover::sensorCollection()
{
    sensor.createPacket(telemetryBuffer, sizeof(telemetryBuffer));
    sensorTransmission();
    
}

void Rover::sensorTransmission()
{
    Serial.print(telemetryBuffer);
    
    // need some way to tell how long we have been collecting data
    // maybe divide the required data collection time by how long it takes
    // to perform each data collection/transmission iteration
    // then keep a counter with how many data iterations have been completed
    // switch states once this number of iterations have been completed
    // probably should overshoot the time to ensure requirement is met
    dataIter++;
    if(dataIter >= reqIter) state = 4;
}

void Rover::turn()
{
    // TODO : Tyler
}

// for state machine testing only
void Rover::setConditions(bool obst, bool heading, bool loc){
    obstacleDetected = obst;
    hasHeading = heading;
    atDest = loc;
}