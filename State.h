/*
  File: State.h
  Kitchen Scale sketch
  Author: Brian C. Burnett
  GitHub repo: https://github.com/bcburnett/kitchenscale04252021
  Questions: https://github.com/bcburnett/kitchenscale04252021/discussions

  This application is in the Public Domain.
  All information is provided in good faith, however I make no representation
  or warranty of any kind, express or implied, regarding the accuracy, adequacy,
  validity, reliability, availability or completeness of this application.
*/ 

#pragma once
#include<Arduino.h>
#include<map>
#include"bcbawsstate.h"
#include"bcbbmxstate.h"
#include"scaleState.h"
//set initial state

class State : public BcbAwsState , public BcbBmxState, public ScaleState {
  public:
  
// begin ScaleState functions
    float weight();
    float weight(float value);
// end ScaleState functions

// begin BcbBmxState functions
    // setter and getter for humidity
    float humidity();
    float humidity(float value);

    // setter and getter for pressure
    float pressure();
    float pressure(float value);

    // setter and getter for pressure64
    double pressure64();
    double pressure64(double value);

    // setter and getter for temperature
    float temperature();
    float temperature(float value);

// end BcbBmxState functions


// begin BcbAwsState functions
    // setter and getter for the uploading filename
    String filename();
    String filename(String value);


     // setter and getter for websocket command
    String command();
    String command(String value);

       
    // should the browser reload the website
    bool reload();
    bool reload(bool value);


    // return a stringifyed json representation of the state
    String getJSON();

// end BcbAwsState functions

// garden pump control functions
        void dew ();


    // is an OTA update in progress
    bool setOta (bool value);
    bool getOta ();

  private:
    // container for the state
    std::map<String, String> jsonMap;
    //OTA is handeled seperately
    bool ota = false;
};
