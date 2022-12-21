// App to control a tuya device with a bespoke app by replacing
// the on board wifi module with a pin compatible ESP32-C3
//
// s60sc 2022

#include "globals.h"

void setup() {
  logSetup();
  startStorage();
  loadConfig();
#ifdef DEV_ONLY
  devSetup();
#endif
  // connect wifi or start config AP if router details not available
  startWifi(); 
  startWebServer();
  prepUarts();
  delay(5000);
  LOG_INF(APP_NAME " v" APP_VER " ready ...");
}

void loop() {
  heartBeat();
}
