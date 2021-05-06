# Esp-32 Kitchen Scale c++ code

## Classes:
    1. kitchenscale04252021.ino
    2. scale.h
    3. scalestate.h
    4. bcbaws.h/cpp
    5. bcbawsstate.h
    6. bcbbmx.h/cpp
    7. bcbbmxstate.h
    8. state.h/cpp

### kitchenscale04252021.ino

    Main Sketch, instantiates instances 
    of the other required classes, maintains 
    the program timing

### scale.h


    class Scale {

    public:

    // functions
    void scaleSetup (ScaleState * istate);
    float getWeight();
    void tare();

    // variables
    uint8_t dataPin = 15;
    uint8_t clockPin = 2;
    HX711 scale;
    float calibration_factor = 223.00;
    float oldWeight;
    ScaleState * state;
}


