/*
  File: kitchenscale04252021.ino
  Kitchen Scale sketch
  Author: Brian C. Burnett
  GitHub repo: https://github.com/bcburnett/kitchenscale04252021
  Questions: https://github.com/bcburnett/kitchenscale04252021/discussions

  This application is in the Public Domain.
  All information is provided in good faith, however I make no representation
  or warranty of any kind, express or implied, regarding the accuracy, adequacy,
  validity, reliability, availability or completeness of this application.
*/

#include <Arduino.h>
#include "State.h" // holds application state
#include "time.h"  // setting the rtc
#include "WiFiCred1.h" // wifi credentials
#include <ArduinoOTA.h> // OTA update server
#include <ESPmDNS.h> // needed by OTA
#include <WiFi.h>  // WiFi library
#include <WiFiUdp.h> // needed by OTA
#include "bcbaws.h" // Asynchronous web server wrapper for espasyncwebserver and websockets
#include"bcbBmx.h" // Weather sensor class
#include"scale.h" // scale loadsensor class
#include <Wire.h>

#define ARDUINO_RUNNING_CORE 1 // core to bind our task to

State state; // instantiate state class
BcbAws aws;  // instantiate web server class
BcbBmx bmx; //  instantiate weather sensor class
Scale scale; // instantiate scale class

// internal rtc variables
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000;
const int daylightOffset_sec = 3600;

bool wifiavail = false;

SemaphoreHandle_t state_lock = xSemaphoreCreateMutex();


// define functions
void doSensorMeasurement(void *pvParameters);
void initWiFi();
void initTime();
void setup();
void loop();
void checkForIndex();
String printLocalTime();
String printLocalHour();


// localtime from internal rtc
String printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return ("");
  }
  return (asctime(&timeinfo));
}


String printLocalHour() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return ("");
  }
  return (String(asctime(&timeinfo)).substring(11, 16) + " ");
}


void setup() {
  Serial.begin(115200);
  vTaskDelay(500);

  // set initial program state
  initWiFi(); // connect to wifi
  initTime(); // connect to ntp servers and set rtc
  Wire.begin();
  bmx.bmxInit(& state); // initialize the bmx sensor
  scale.scaleSetup(&state);
  aws.BcbAwsInit(&state); // initialize the webserver and start listening for connections


  ArduinoOTA // OTA setup
  .onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
    SPIFFS.end();// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS
    aws.ws.enable(false);// Disable client connections
    aws.ws.textAll("{\"message\":\"OTA Update Started\"");// Advertise to connected clients what's going on
    aws.ws.closeAll();// Close them
    state.setOta(true); // prevent updates to clients while updating
  });
  ArduinoOTA.begin();

//  xTaskCreatePinnedToCore(               // update the connected web clients 
//    UpdateClients,                       // function name
//    "updateClients",                     // name for humans
//    2048,                                // This stack size can be checked & adjusted by reading the Stack Highwater
//    NULL,                                // task input parameter
//    2,                                   // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//    NULL,                                // task handle
//    ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(               // read sensors
    doSensorMeasurement,                 // function name
    "doSensorMeasurement",               // name for humans
    2048,                                // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,                                // task input parameter
    2,                                   // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    NULL,                                // task handle
    ARDUINO_RUNNING_CORE);

}

void loop() {
  if (!state.getOta()) {
    ArduinoOTA.handle(); // check if an update is available
    if (WiFi.status() != WL_CONNECTED) // check if wifi is still connected, if not, reconnect
      initWiFi();
  }
  vTaskDelay(60);
}


void UpdateClients(void *pvParameters) { // handle websocket  display
  (void)pvParameters;
  for (;;) {
    if (!state.getOta()) {
      if (xSemaphoreTake(state_lock, 125)) {
        aws.notifyClients(); // send state to the client as a json string
        xSemaphoreGive(state_lock);
      }
    }
    vTaskDelay(250); // update clients every minute
  }
}

void doSensorMeasurement(void *pvParameters) { // handle websocket  display
  (void)pvParameters;
  for (;;) {
    if (!state.getOta()) {
        bmx.doSensorMeasurement();
        if(state.command() == "tare"){
          state.command("");
          scale.tare();
        }
        scale.getWeight();
        aws.notifyClients();
    }
    vTaskDelay(1000); // update clients every minute
  }
}

void initWiFi() {
  Serial.println("connecting to wifi");
  // connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("connecting to wifi failed");
    delay(500);
    initWiFi();
  }
  Serial.println("wifi connected");
  wifiavail = true;
}

void initTime() {
  // set the clock from ntp server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
}
