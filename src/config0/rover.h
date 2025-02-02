#ifndef rover_h
#define rover_h

#include "sensor.h"

class Rover
{
    private:
        int state;
        bool obstacleDetected;
        
        int beaconAngle;
        float beaconDistance;

        Sensor sensor;  // Sensor object
        char telemetryBuffer[49];  // Buffer to store telemetry data

    public:
        Rover();

        void setState(int newState);
        int getState();

        void detectBeacon();
        void traversal();
        void obstacleAvoidance();
        void sensorCollection();
        void sensorTransmission();
        void turn();
};

#endif