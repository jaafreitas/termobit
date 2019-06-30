#include "alarm.h"
#include "settings.h"

void setupAlarm() {
  pinMode(ALARM_PIN, OUTPUT);

  // HIGH means OFF to the LED_BUILTIN on ESP-12E.
  digitalWrite(ALARM_PIN, HIGH);
}

void alarm(bool value) {
  if (value) {
    digitalWrite(ALARM_PIN, LOW);
    tone(ALARM_PIN, 440);    
  } else {
    noTone(ALARM_PIN);
    digitalWrite(ALARM_PIN, HIGH);
  }
}
