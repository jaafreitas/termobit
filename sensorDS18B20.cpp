#include "sensorDS18B20.h"
#include "settings.h"
#include "conn.h"
#include "debug.h"
#include "src/OneWire/OneWire.h"
#include "src/DallasTemperature/DallasTemperature.h"

OneWire oneWire(SENSOR_DS18B20_PIN);
DallasTemperature sensors(&oneWire);

uint8_t thermometerFounds = 0;

void setupSensorDS18B20ByIndex(uint8_t index) {
  DeviceAddress thermometer;
  if (sensors.getAddress(thermometer, index)) {
    sensors.setResolution(thermometer, SENSOR_DS18B20_PRECISION);
    sensors.setHighAlarmTemp(thermometer, SENSOR_DS18B20_ALARM_TEMPERATURE_HIGH);
    sensors.setLowAlarmTemp(thermometer, SENSOR_DS18B20_ALARM_TEMPERATURE_LOW);
  }
}

void setupSensorDS18B20() {
  sensors.begin();

  thermometerFounds = sensors.getDeviceCount();
  debugMsg("DS18B20 devices found: %d\n", thermometerFounds);  

  for (uint8_t index = 0; index < thermometerFounds; index++) {
    setupSensorDS18B20ByIndex(index);
  }
}

void loopSensorDS18B20(Conn* conn) {
  static unsigned long lastSensorRead = 0;
  
  if (millis() - lastSensorRead > SENSOR_DS18B20_NOTIFY_INTERVAL) {
    lastSensorRead = millis();    
    
    sensors.requestTemperatures();  
    for (uint8_t index = 0; index < thermometerFounds; index++) {
      DeviceAddress thermometer;
      if (sensors.getAddress(thermometer, index)) {
        float temp = sensors.getTempCByIndex(index);
        String sensor = SENSOR_DS18B20_NAME + String("/") + String(index);
        conn->notify_sensor(sensor, temp, sensors.hasAlarm(thermometer));
      }
    }
  }
}
