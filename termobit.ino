#include <Esp.h>
#include "settings.h"
#include "debug.h"
#include "version.h"
#include "conn.h"
#include "ntp.h"
#include "alarm.h"
#include "sensorButton.h"
#include "sensorDS18B20.h"

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
  setupSensorDS18B20();
}

void loop() {
  conn->loop();
  
  loopNTPClient(conn);
  loopSensorButton(conn);
  loopSensorDS18B20(conn);
}
