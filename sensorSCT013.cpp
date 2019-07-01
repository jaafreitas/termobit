#include "sensorSCT013.h"
#include "settings.h"
#include "conn.h"
#include "debug.h"
#include "src/EmonLib/EmonLib.h"

EnergyMonitor emon;

void setupSensorSCT013() {
  emon.current(SENSOR_SCT013_PIN, SENSOR_SCT013_TURNRATIO/SENSOR_SCT013_RESISTANCE);
}

void loopSensorSCT013(Conn* conn) {
  static unsigned long lastSensorRead = 0;
  
  if (millis() - lastSensorRead > SENSOR_SCT013_NOTIFY_INTERVAL) {
    lastSensorRead = millis();
    
    double Irms = emon.calcIrms(1480);
    conn->notify_sensor(SENSOR_SCT013_NAME, Irms);
  }
}
