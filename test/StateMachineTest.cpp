// #include "Arduino.h"
#include "rover.h"
#include <Arduino.h>

Rover rover;

bool end;
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
  std::cout << "terminate? (0 = no, 1 = yes): "
  std::cin >> end;
  if(end) break;
  
  obst, heading, loc = false;
  Serial.print("set bool value for obstDetected (0 = false, 1 = true): ");
  obst = Serial.read();
  Serial.print("set bool value for hasHeading (0 = false, 1 = true): ");
  heading = Serial.read();
  Serial.print("set bool value for atDest (0 = false, 1 = true): ");
  loc = Serial.read();

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
  
  Serial.println("Current State: " + rover.getState());
}

int main(){
    setup();
    loop();
    Serial.print("Complete");
}