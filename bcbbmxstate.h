/*
  File: bcbbmxstate.h
  Author: Brian C. Burnett
* bmx sensor class

  This application is in the Public Domain.
  All information is provided in good faith, however I make no representation
  or warranty of any kind, express or implied, regarding the accuracy, adequacy,
  validity, reliability, availability or completeness of this application.
*/
#pragma once

class BcbBmxState {
  public:
    // setter and getter for humidity
    virtual float humidity();
    virtual float humidity(float value);

    // setter and getter for pressure
    virtual float pressure();
    virtual float pressure(float value);

    // setter and getter for pressure64
    virtual double pressure64();
    virtual double pressure64(double value);

    // setter and getter for temperature
    virtual float temperature();
    virtual float temperature(float value);

};
