#ifndef rover_h
#define rover_h

class Rover
{
    private:
        int state;
        bool obstacleDetected;
        
        int beaconAngle;
        float beaconDistance;
    public:
        Rover();

        void setState(int newState);
        int getState();

        void detectBeacon();
        void traversal();
        void obstacleAvoidance();
        void sensorCollection();
        void sensorTransmission();
};

#endif