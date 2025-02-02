#include "Arduino.h"
#include "rover.h"

Rover rover;

/*
  State Manager: (subject to change)
    - Detect direction of beacon    (beacon)        0
    - Traversal                     (traversal)     1
    - Object avoidance              (avoidance)     2 
<<<<<<< HEAD
    - Sensor collection             (collection)    3
    - End mission                   (end)           4
  */
=======
    - Sensor collection start       (collection)    3
    - Sensor data transmission      (transmission)  4
    - End mission                   (end)           5
*/
>>>>>>> cc009f1171e75a212b921c558284b31d9747990b

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
    rover.sensorTransmission();

  case 4:
    break;

  }
}