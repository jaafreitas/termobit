#include <Esp.h>
#include "settings.h"
#include "debug.h"
#include "version.h"
#include "conn.h"
#include "ntp.h"

Conn* conn;
String hostname;

void setup() {
  setupDebug();

  hostname = String(HOSTNAME_PREFIX) + String(ESP.getChipId());

  debugMsg("\n***** %s *****\n", title(hostname));

  conn = new Conn(hostname);
  setupNTPClient();
}

void loop() {
  loopNTPClient([](String topic, String payload, bool retained) {
    conn->notify(topic, payload, retained);
  });

  conn->loop();
}
