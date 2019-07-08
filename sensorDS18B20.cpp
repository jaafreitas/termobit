#include "sensorDS18B20.h"
#include "settings.h"
#include "conn.h"
#include "debug.h"
#include "src/OneWire/OneWire.h"
#include "src/DallasTemperature/DallasTemperature.h"

OneWire oneWire(SENSOR_DS18B20_PIN);
DallasTemperature sensors(&oneWire);

uint8_t thermometerFounds = 0;
String releStatus = STATUS_OFF;

void setupSensorDS18B20ByIndex(uint8_t index) {
  DeviceAddress thermometer;
  if (sensors.getAddress(thermometer, index)) {
    sensors.setResolution(thermometer, SENSOR_DS18B20_PRECISION);
  }
}

void setupSensorDS18B20() {
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH);
  
  sensors.begin();

  thermometerFounds = sensors.getDeviceCount();
  debugMsg("DS18B20 devices found: %d\n", thermometerFounds);  

  for (uint8_t index = 0; index < thermometerFounds; index++) {
    setupSensorDS18B20ByIndex(index);
  }
}

bool checkAlarm(float temp) {
  // returns true if temp is beyond the limits
  return (temp > SENSOR_TEMPERATURE_ALARM_HIGH) or (temp < SENSOR_TEMPERATURE_ALARM_LOW);
}

void loopSensorDS18B20(Conn* conn) {
  static unsigned long lastSensorRead = 0;
  
  if (millis() - lastSensorRead > SENSOR_DS18B20_NOTIFY_INTERVAL) {
    lastSensorRead = millis();    
    
    sensors.requestTemperatures();  
    float averageTemp = 0.0;
    for (uint8_t index = 0; index < thermometerFounds; index++) {
      DeviceAddress thermometer;
      if (sensors.getAddress(thermometer, index)) {
        float temp = sensors.getTempCByIndex(index) - SENSOR_TEMPERATURE_OFFSET;
        averageTemp += temp;
        String sensor = SENSOR_DS18B20_NAME + String("/") + String(index);
        conn->notify_sensor(sensor, temp, checkAlarm(temp));
      }
    }
    averageTemp /= thermometerFounds;
    conn->notify_sensor(SENSOR_TEMPERATURE, averageTemp, checkAlarm(averageTemp));


    float targetTemperature = (SENSOR_TEMPERATURE_ALARM_LOW + SENSOR_TEMPERATURE_ALARM_HIGH) / 2.0;
//    debugMsg("targetTemperature: %f\n", targetTemperature);
    
    float maxHighTemperature = min(targetTemperature * (1 + SENSOR_TEMPERATURE_VARIATION_PERCENTAGE / 100.0), (double)SENSOR_TEMPERATURE_ALARM_HIGH);
//    debugMsg("maxHighTemp: %f\n", maxHighTemperature);
    if (averageTemp >= maxHighTemperature) {
      releStatus = STATUS_ON;
      digitalWrite(RELE_PIN, LOW);
    }

    float minLowTemperature = max(targetTemperature * (1 - SENSOR_TEMPERATURE_VARIATION_PERCENTAGE / 100.0), (double)SENSOR_TEMPERATURE_ALARM_LOW);
//    debugMsg("minLowTemp: %f\n", minLowTemperature);
    if (averageTemp <= minLowTemperature) {
      releStatus = STATUS_OFF;
      digitalWrite(RELE_PIN, HIGH);
    }
    conn->notify_topic(RELE_NAME, releStatus, false);
    
  }
}
