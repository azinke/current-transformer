/**
    @author: AMOUSSOU Z. Kenneth
    @date: 16-12-2018
    @version: 1.0
    @note: not tested yet on the sensor 
**/
#include <CT.h>

CT currentSensor(1800, 200, 5, A0);

void setup(){
    Serial.begin(9600);
    // calibrate the sensor to compute offset value
    // currentSensor.calibrate();
}

void loop(){
    Serial.print("Raw data : ");
    Serial.print(currentSensor.getRawData());
    Serial.print(", Current: ");
    Serial.print(currentSensor.read(mA));
    Serial.print(" , Max: ");
    Serial.print(currentSensor.read(MAX));
    Serial.print(" , Min: ");
    Serial.println(currentSensor.read(MIN));
    delay(1000);
}
