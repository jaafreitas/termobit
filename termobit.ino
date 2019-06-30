#include <Esp.h>
#include "settings.h"
#include "debug.h"
#include "version.h"
#include "conn.h"
#include "ntp.h"
#include "alarm.h"
#include "sensorButton.h"

Conn* conn;
String hostname;

void setup() {
  setupDebug();

  hostname = String(HOSTNAME_PREFIX) + String(ESP.getChipId());

  debugMsg("\n***** %s *****\n", title(hostname));

  conn = new Conn(hostname);
  setupNTPClient();
  setupAlarm();
  setupSensorButton();
}

void loop() {
  conn->loop();
  
  loopNTPClient(conn);
  loopSensorButton(conn);
}
