// Demo for getting individual unified sensor data from the LPS2X series

#include <Adafruit_LPS2X.h>

// Use LPS25 or LPS22 here
Adafruit_LPS22 lps;
Adafruit_Sensor *lps_temp, *lps_pressure;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit LPS2X test!");

  if (!lps.begin_I2C()) {
    Serial.println("Failed to find LPS2X chip");
    while (1) {
      delay(10);
    }
  }

  Serial.println("LPS2X Found!");
  lps_temp = lps.getTemperatureSensor();
  lps_temp->printSensorDetails();

  lps_pressure = lps.getPressureSensor();
  lps_pressure->printSensorDetails();
}

void loop() {
  //  /* Get a new normalized sensor event */
  sensors_event_t pressure_ev;
  sensors_event_t temp_ev;
  lps_temp->getEvent(&temp_ev);
  lps_pressure->getEvent(&pressure_ev);

  double pres = pressure_ev.pressure;
  double temp = temp_ev.temperature;

  Serial.println(String(temp) + ", " + String(pres));
  delay(10);
}