#include "alarm.h"
#include "settings.h"

unsigned long lastAlarmTriggered = 0;

void setupAlarm() {
  pinMode(ALARM_PIN, OUTPUT);

  // HIGH means OFF to the LED_BUILTIN on ESP-12E.
  digitalWrite(ALARM_PIN, HIGH);
}

void alarm(bool value) {
  if (value) {
    lastAlarmTriggered = millis();
  }

  if (millis() - lastAlarmTriggered < ALARM_MINIMUM_TIME) {
    tone(ALARM_PIN, 440);    
  } else {
    noTone(ALARM_PIN);
    digitalWrite(ALARM_PIN, HIGH);
  }
}
