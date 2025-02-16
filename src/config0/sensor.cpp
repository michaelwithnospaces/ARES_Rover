#include "sensor.h"
#include "Adafruit_BME280.h"
#include "Arduino.h"

#define analogRVPin 1
#define analogTMPPin 0

Adafruit_BME280 bme;
Sensor::Sensor(): proximityL(10), proximityR(10), heading(10), beaconDistance(10) {}

void Sensor::begin() {}

float Sensor::getBeaconDistance() {
    beaconDistance.push(0); // TODO: replace with actual sensor reading
}

/** return pointer to array with [left, right proximity] */
float* Sensor::getProximity() {
    proximityL.push(0); // TODO: replace with actual sensor reading
    proximityR.push(0); // TODO: replace with actual sensor reading
}

float Sensor::getHeading() {
    heading.push(0); // TODO: replace with actual sensor reading
}

float Sensor::getWindSpeed() {
    const float noWindAdjustment =  .2; // calibrates sensor at eqillibrium
    
    int TMP_Therm_ADunits;  //temp termistor value from wind sensor
    float RV_Wind_ADunits;  //RV output from wind sensor 
    float RV_Wind_Volts, zeroWind_ADunits, noWindvolts, WindSpeed_MPH;
    unsigned long lastMillis;
    int TempCtimes100;
    TMP_Therm_ADunits = analogRead(analogTMPPin);
    RV_Wind_ADunits = analogRead(analogRVPin);
    RV_Wind_Volts = (RV_Wind_ADunits *  0.0048828125);

    TempCtimes100 = (0.005 *((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;  

    zeroWind_ADunits = -0.0006*((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;  //  13.0C  553  482.39

    noWindvolts = (zeroWind_ADunits * 0.0048828125) - noWindAdjustment;

    WindSpeed_MPH =  pow(((RV_Wind_Volts - noWindvolts) /.2300) , 2.7265); //wind speed in mph

    return(WindSpeed_MPH);
}

float Sensor::getBatteryVoltage() {}

float Sensor::getTemperature() {
    bme.readTemperature();

}

// Creates a telemetry packet in a 49-char buffer
void Sensor::createPacket(char* buffer) 
{
    float* prox = getProximity();

    // Pad to 42 bytes
    snprintf(buffer, 42,
        "P:%d,%d\n"
        "D:%.1f\n"
        "H:%.1f\n"
        "W:%.1f\n"
        "V:%.2f\n"
        "T:%.1f\n"
        "                                         ",
        // 41 empty bits (almost 42, leaving space for \0)
        // padding at the end, if there's no space, it will get trimmed
        getProximity()[0],
        getProximity()[1],
        getBeaconDistance(),
        getHeading(),
        getWindSpeed(),
        getBatteryVoltage(),
        getTemperature()
    );
}
