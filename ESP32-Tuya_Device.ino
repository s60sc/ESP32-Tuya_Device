// App to control a tuya device with a bespoke app by replacing
// the on board wifi module with a pin compatible ESP32-C3
//
// Either the Tuya MCU or the ESP can be selected as controller.
// The controller manages the daily schedule and temperature settings.

// s60sc 2022

#include "appGlobals.h"

static bool startedUp = false;

void setup() {
  logSetup();
  // prep SD card storage & load saved user configuration
  if (startStorage()) loadConfig();
  
#ifdef DEV_ONLY
  devSetup();
#endif
  // connect wifi or start config AP if router details not available
  startWifi(); 
  
  startWebServer();
  if (strlen(startupFailure)) LOG_ERR("%s", startupFailure);
  else {
    prepUarts();
    delay(5000);
    startedUp = true;
    checkMemory();
  }
}

void loop() {
  startedUp ? heartBeat() : delay(1000);
}
