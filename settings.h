#pragma once

#include <Arduino.h>

#define DEBUG

#define HOSTNAME_PREFIX "termobit"

#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"

#define MQTT_CONNECTION_RETRY 60000

#define MQTT_SERVER "MQTT_SERVER"
#define MQTT_PORT 1883

#define NTP_SERVER "NTP_SERVER"
#define NTP_PORT 123
#define NTP_LOCALPORT 2390
#define NTP_INTERVAL 1 * 60 * 60 * 1000 // Every 1 hour (in milliseconds)
#define TZ_OFFSET (-3 * 60 * 60) // in seconds.

#define SENSOR_STATUS_OPEN "open"
#define SENSOR_STATUS_CLOSED "closed"

#define SENSOR_DOOR_NAME "door"
#define SENSOR_DOOR_PIN D1
#define SENSOR_DOOR_NOTIFY_INTERVAL 1000 // Every second.
#define SENSOR_DOOR_ALARM_NOTIFY_AFTER 10000

#define SENSOR_BOX_NAME "box"
#define SENSOR_BOX_PIN D2
#define SENSOR_BOX_NOTIFY_INTERVAL 1000 // Every second.
#define SENSOR_BOX_ALARM_NOTIFY_AFTER 0

#define SENSOR_DS18B20_NAME "ds18b20"
#define SENSOR_DS18B20_PIN D3
#define SENSOR_DS18B20_PRECISION 12
#define SENSOR_DS18B20_ALARM_TEMPERATURE_LOW 20
#define SENSOR_DS18B20_ALARM_TEMPERATURE_HIGH 28
#define SENSOR_DS18B20_NOTIFY_INTERVAL 1000 // Every second.

#define ALARM_PIN D4
#define ALARM_MINIMUM_TIME 2000
