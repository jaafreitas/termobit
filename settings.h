#pragma once

#include <Arduino.h>

#define DEBUG

#define HOSTNAME_PREFIX "termobit"

#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"

#define MQTT_CONNECTION_RETRY 10000

#define MQTT_SERVER "MQTT_SERVER"
#define MQTT_PORT 1883

#define NTP_SERVER "NTP_SERVER"
#define NTP_PORT 123
#define NTP_LOCALPORT 2390
#define NTP_INTERVAL 1 * 60 * 60 * 1000 // Every 1 hour (in milliseconds)
#define TZ_OFFSET (-3 * 60 * 60) // in seconds.

#define SENSOR_DOOR_PIN D1
#define SENSOR_DOOR_NOTIFY_INTERVAL 1000 // Every second.
#define SENSOR_DOOR_ALARM_NOTIFY 15000

#define ALARM_PIN D4
