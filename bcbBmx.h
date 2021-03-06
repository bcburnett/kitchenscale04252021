/*
* File: bcbBmx.h
* Author: Brian C. Burnett
* bmx sensor class
*    
* This application is in the Public Domain.
* All information is provided in good faith, however I make no representation 
* or warranty of any kind, express or implied, regarding the accuracy, adequacy, 
* validity, reliability, availability or completeness of this application.
*/
#pragma once

#include "State.h"
#include <BMx280I2C.h>
#include"bcbbmxstate.h"

#define BMX_ADDRESS 0x76
class BcbBmx {
  
  public:
    BcbBmx();
    void bmxInit(BcbBmxState * istate);
    void doSensorMeasurement();

  private:
    BMx280I2C bmx280 = BMx280I2C(BMX_ADDRESS);
    BcbBmxState * state;
};
