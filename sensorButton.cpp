#include "sensorButton.h"
#include "settings.h"

void setupSensorButton() {
  pinMode(SENSOR_DOOR_PIN, INPUT_PULLUP);
}


void loopSensorButton(Conn* conn) {
  bool doorOpen = digitalRead(SENSOR_DOOR_PIN);
  
  static unsigned long lastRead = 0;
  static unsigned long lastAlarm = 0;
  static bool doorOpenLastStatus = false;
  
  // The door has just been closed.
  if (doorOpenLastStatus and !doorOpen) {
    conn->notify_sensor("door", "closed", false);
    delay(10);
  }
  
  doorOpenLastStatus = doorOpen;
  if (doorOpen) {
    if (millis() - lastRead > SENSOR_DOOR_NOTIFY_INTERVAL) {
      lastRead = millis();
      bool alarm = millis() - lastAlarm > SENSOR_DOOR_ALARM_NOTIFY_AFTER;
      conn->notify_sensor("door", "open", alarm);
    }
    
  } else {
    lastAlarm = millis();
  }
}
