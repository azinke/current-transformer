/**
 * @author: AMOUSSOU Zinsou Kenneth
 * @date: 16-12-2018
 * @version: 1.0
 */
#include "CT.h"

/**
 *  @summary: constructor of the library
 */
CT::CT(uint16_t turns, uint16_t shunt ,uint8_t calibre, uint8_t pin){
    _n = turns;
    _calibre = calibre;
    _input = pin;
    _shunt = shunt;
    _offset = 512.0;    // default offset value
}

/**
 *  @function: calibrate
 *  @summary: do the calibration job of the sensor
 *  @parameters: none
 *  @return: 
 *      float: offset
 *  @requirement: the sensor should not be in-circuit during 
 *                calibration
 */
float CT::calibrate(){
    uint16_t i = 0;
    float _buffer = 0;
    for(i = 0; i <= 200; i++){
        _buffer += analogRead(_input);
        delayMicroseconds(10);
    }
    _offset = _buffer/i;
    return _offset;
}

/**
 *  @function: getRawData
 *  @summary: read raw data from the sensor
 *  @parameters: none
 *  @return: 
 *      float: data
 *  @profiling:
 *      duration: ~1ms
 */
float CT::getRawData(){
    uint8_t i = 0;
    float _buffer = 0;
    for(i = 0; i < 100; i++){
        _buffer += analogRead(_input);
        delayMicroseconds(10);
    }
    return _buffer/i;
}

/**
 *  @function: read
 *  @summary: read root-Mean-Square data from the sensor
 *  @parameters:
 *      uint: the unit of the returned current
 *  @return: 
 *      float: RMS value
 *  @profiling:
 *      duration: ~100ms
 */
float CT::read(uint8_t unit){
    uint8_t i = 0;
    float minValue = _offset;
    float maxValue = _offset;
    float _buffer = 0;
    long start = millis();
    while(millis() - start < 100){
        _buffer = getRawData();
        if(_buffer > maxValue) maxValue = _buffer;
        if(_buffer < minValue) minValue = _buffer;
    }

    _buffer = (maxValue - minValue)/2.0;
    if(unit == MAX) _buffer = maxValue - _offset;
    if(unit == MIN) _buffer = _offset - minValue;
    _buffer = _buffer * VREF/1023.0;    // voltage
    _buffer /= _shunt;  // compute current through the shunt
    _buffer *= 0.70711; // RMS current through the shunt
    _buffer *= _n;
    if(unit == mA) return _buffer * 1000.0;
    else return _buffer;
}

/**
 *  @function: getMax
 *  @summary: read the max value of the current
 *  @parameters:
 *      unit: unit of the result
 *            mA: for milliAmps
 *            default unit: Amps
 *  @return: 
 *      float: max value in Amps
 */
float CT::getMax(uint8_t unit){
    if(unit == mA) return (read(MAX) * 1000.0);
    return read(MAX);    
}

/**
 *  @function: getMin
 *  @summary: read the min value of the current
 *  @parameters:
 *      unit: unit of the result
 *            mA: for milliAmps
 *            default unit: Amps
 *  @return: 
 *      float: min value in Amps
 */
float CT::getMin(uint8_t unit){
    if(unit == mA) return (read(MIN) * 1000.0);
    return read(MIN);    
}


/**
 *  @function: getOffset
 *  @summary: read the offset value of the sensor
 *  @parameters: none
 *  @return: 
 *      float: offset value
 */
float CT::getOffset(){
    return _offset;
}

