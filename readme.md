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

### scalestate.h

    class ScaleState{
    public:
      // setter and getter for weight
    virtual float weight();
    virtual float weight(float value);
    };

### bcbaws.h/cpp

    class BcbAws {
    public:
        BcbAws(); // blank constructor
        AsyncWebSocket ws = AsyncWebSocket("/ws"); // websocket server
        void BcbAwsInit(BcbAwsState * istate); // class initialization with refrence to state
        void notifyClients(); // notify clients with a json representation of state

    private:
        AsyncWebServer server = AsyncWebServer(80); // web server
        void handleWebSocketMessage(void *arg, uint8_t *data, size_t len); // invoked on websocket message received
        void parseCommand(String command); // parse received commands from websockets
        void checkForIndex(); // check if index.htm exists, if not, create it and populate with the contents of defaulthtml.h
        BcbAwsState* state;
    };


### bcbawsstate.h

    class BcbAwsState{
    public:
        // setter and getter for the uploading filename
        virtual String filename();
        virtual String filename(String value);
        
        virtual String command();
        virtual String command(String value);
        
        // should the browser reload the website
        virtual bool reload();
        virtual bool reload(bool value);

        // return a stringifyed json representation of the state
        virtual String getJSON();
    };

### bcbbmx.h/cpp


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

### BcbBmxState.h

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

### state.h

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