#ifndef rover_h
#define rover_h

#include "sensor.h"

class Rover
{
    private:
        int state;
        bool obstacleDetected;
        
        // for testing, some may be permanent
        bool hasHeading;
        bool atDest;
        int dataIter;
        int reqIter;    // ensures data is collected for the required amount of time, > (required time of data collection) / (time per data collection/transmission iteration)

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
        
        // for state machine testing only
        void setConditions(bool obst, bool heading, bool loc);
};

#endif