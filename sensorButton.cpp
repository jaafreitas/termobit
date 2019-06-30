#include "sensorButton.h"
#include "settings.h"

unsigned long lastDoorRead = 0;
unsigned long lastDoorAlarm = 0;
bool doorOpenLastStatus = false;

unsigned long lastBoxRead = 0;
unsigned long lastBoxAlarm = 0;
bool doorBoxLastStatus = false;

void setupSensorButton() {
  pinMode(SENSOR_DOOR_PIN, INPUT_PULLUP);
  pinMode(SENSOR_BOX_PIN, INPUT_PULLUP);
}

void loopSensorButton(Conn* conn, uint8_t pin, String sensor, 
  unsigned long &lastSensorRead, unsigned long &lastSensorAlarm, bool &sensorOpenLastStatus,
  unsigned long sensorNotifyInterval, unsigned long sensorAlarmNotifyAfter) {
      
  bool sensorOpen = digitalRead(pin);
  
  // The sensor has just been closed.
  if (sensorOpenLastStatus and !sensorOpen) {
    conn->notify_sensor(sensor, SENSOR_STATUS_CLOSED, false);
    // "blink without delay"
    delay(50);
  }
  
  sensorOpenLastStatus = sensorOpen;
  if (sensorOpen) {
    if (millis() - lastSensorRead > sensorNotifyInterval) {
      lastSensorRead = millis();
      bool alarm = millis() - lastSensorAlarm >= sensorAlarmNotifyAfter;
      conn->notify_sensor(sensor, SENSOR_STATUS_OPEN, alarm);
    }
    
  } else {
    lastSensorAlarm = millis();
  }
}

void loopSensorButton(Conn* conn) {
  loopSensorButton(conn, SENSOR_DOOR_PIN, SENSOR_DOOR_NAME, lastDoorRead, lastDoorAlarm, doorOpenLastStatus, 
    SENSOR_DOOR_NOTIFY_INTERVAL, SENSOR_DOOR_ALARM_NOTIFY_AFTER);
    
  loopSensorButton(conn, SENSOR_BOX_PIN, SENSOR_BOX_NAME, lastBoxRead, lastBoxAlarm, doorBoxLastStatus, 
    SENSOR_BOX_NOTIFY_INTERVAL, SENSOR_BOX_ALARM_NOTIFY_AFTER);
}
