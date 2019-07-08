#include "alarm.h"
#include "settings.h"

unsigned long lastAlarmTriggered = 0;

void setupAlarm() {
  pinMode(ALARM_BUZZER_PIN, OUTPUT);
  digitalWrite(ALARM_BUZZER_PIN, LOW);

  pinMode(STATUS_PIN, OUTPUT);  
  digitalWrite(STATUS_PIN, LOW);
}

void alarm(bool value) {
  if (value) {
    lastAlarmTriggered = millis();
  }

  if (millis() - lastAlarmTriggered < ALARM_MINIMUM_TIME) {
    digitalWrite(ALARM_BUZZER_PIN, HIGH);
  } else {
    digitalWrite(ALARM_BUZZER_PIN, LOW);
  }
}
