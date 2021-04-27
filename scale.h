#include<Arduino.h>
#include "HX711.h"
#include"scaleState.h"
class Scale {
  public:

    void scaleSetup (ScaleState * istate);
    float getWeight();


    uint8_t dataPin = 15;
    uint8_t clockPin = 2;
    HX711 scale;
    float calibration_factor = 223.00;
    float oldWeight;
    ScaleState * state;
};


void Scale::scaleSetup (ScaleState * istate) {
  state = istate;
  scale.begin(dataPin, clockPin);
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  //Get a baseline reading
  //  long zero_factor = 16926;


};


// Common weight retrieval routine
float Scale::getWeight() {
  //Adjust to this calibration factor
  scale.set_scale(calibration_factor);

  // Read an average of X readings
  Serial.println("Reading weight");
  float weight = scale.get_units(10);

  // An intermediate weight value that we round according to some rules
  int netWeight = 0;

  // Make scale more sensitive at lower end
  // Weight > X then just round to nearest integer
  if (weight >= 5.0) {
    netWeight = (weight * 10.0);
    weight = (int) (0.5 + (netWeight / 10.0));
  }
  // Weight < Y then call it zero
  else if (weight > -0.02 && weight <= 0.02) {
    weight = 0;
  }
  // Any other weight will have 1 dec. place of precision
  else {
    netWeight = (weight * 10.0);
    weight = (netWeight / 10.0);
  }
  Serial.println(weight);
  state->weight(weight);
  return weight;
}
