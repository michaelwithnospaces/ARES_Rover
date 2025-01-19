#include "Arduino.h"
#include "rover.h"

Rover rover;
int state = 0;
/*
  State Manager: (subject to change)
    - Detect direction of beacon    (beacon)        0
    - Traversal                     (traversal)     1
    - Object avoidance              (avoidance)     2
    - Reached destination           (destination)   3   
    - Sensor collection start       (collection)    4
    - Sensor data transmission      (transmission)  5
    - End mission                   (end)           6
  */

void setup()
{
  // initialize motors and servos for driving
  rover.setState(4);
}

void loop()
{
  switch (rover.getState())
  {
  case 0: // detect beacon

    rover.detectBeacon();
    rover.setState(1);

  case 1: // enter traversal
    rover.traversal();

  case 2: // obstacle avoidance stage
    rover.obstacleAvoidance();

  case 3:
    Serial.println("Reached destination.");
    rover.setState(4);

  case 4:
    rover.sensorCollection();
    rover.setState(5);

  case 5:
    rover.sensorTransmission();
    rover.setState(1);

  case 6:
    break;
  }

  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);

  delay(1000);
}