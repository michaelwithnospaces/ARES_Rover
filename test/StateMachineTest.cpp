#include "Arduino.h"
#include "rover.h"
#include <iostream>
using namespace std;

Rover rover;
bool obst;
bool heading;
bool loc;

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
  obst, heading, loc = false;
  std::cout << "set bool value for obstDetected (0 = false, 1 = true): ";
  std::cin >> obst;
  std::cout << "set bool value for hasHeading (0 = false, 1 = true): ";
  std::cin >> heading;
  std::cout << "set bool value for atDest (0 = false, 1 = true): ";
  std::cin >> loc;

  rover.setConditions(obst, heading, loc);
  
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
  
  std::cout << "Current State: " << rover.getState();
}