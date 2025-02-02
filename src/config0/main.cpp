#include "Arduino.h"
#include "rover.h"

Rover rover;
int state = 0;
/*
  State Manager: (subject to change)
    - Detect direction of beacon    (beacon)        0
    - Traversal                     (traversal)     1
    - Object avoidance              (avoidance)     2 
    - Sensor collection start       (collection)    3
    - Sensor data transmission      (transmission)  4
    - End mission                   (end)           5
*/

void setup()
{
  // initialize motors and servos for driving
  rover.setState(0);
}

void loop()
{
  switch (rover.getState())
  {
  case 0: // detect beacon
    rover.detectBeacon();

  case 1: // enter traversal
    rover.traversal();

  case 2: // obstacle avoidance stage
    rover.obstacleAvoidance();

  case 3:
    rover.sensorCollection();
    rover.setState(5);

  case 4:
    rover.sensorTransmission();
    rover.setState(5);

  case 5:
    break;
  }
}