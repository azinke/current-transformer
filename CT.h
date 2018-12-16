/**
 *  @summary: current transformers sensor library
 *  @author: AMOUSSOU Zinsou Kenneth
 *  @date: 16-12-2018
 *  @version: 1.0
 */
#ifndef H_CT
#define H_CT

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// units
#define A   1
#define mA  2
#define MAX 3
#define MIN 4

// TODO: Add a method to set the reference voltage
#define VREF    5


class CT{
    public:
        CT(uint16_t turns, uint16_t shunt, uint8_t calibre, uint8_t pin=A0);
        float getRawData();     // read raw data out of the sensor
        float read(uint8_t uint); // read Root Mean Square data
        float getMax(uint8_t unit);
        float getMin(uint8_t unit);
        float calibrate(); 
        float getOffset();
    private:
        float _offset;      // offset of the ciruit with no-current
        uint8_t _calibre;   // the sensor's caliber/gauge
        uint16_t _n;        // number of turns
        uint16_t _shunt;    // shunt resistor's value
        uint8_t _input;      // input pin the sensor is connected on
};

#endif
