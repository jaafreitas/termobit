#pragma once

#include <Arduino.h>

#define DEBUG

static const char* HOSTNAME_PREFIX = "termobit";

static const char* WIFI_SSID = "WIFI_SSID";
static const char* WIFI_PASSWORD = "WIFI_PASSWORD";
static const uint8_t WIFI_CONNECTION_RETRIES = 20;

static const unsigned long MQTT_CONNECTION_RETRY = 60000;

static const char* MQTT_SERVER = "MQTT_SERVER";
static const uint16_t MQTT_PORT = 1883;
static const char* MQTT_USER = "";
static const char* MQTT_PASSWORD = "";
static const char* MQTT_TOPIC_PREFIX = "";

static const char* NTP_SERVER = "NTP_SERVER";
static const uint16_t NTP_PORT = 123;
static const uint16_t NTP_LOCALPORT = 2390;
static const unsigned long NTP_INTERVAL = 1 * 60 * 60 * 1000; // Every 1 hour (in milliseconds)
static const unsigned long TZ_OFFSET = (-3 * 60 * 60); // in seconds.

static const char* SENSOR_STATUS_OPEN = "open";
static const char* SENSOR_STATUS_CLOSED = "closed";

static const char* SENSOR_TEMPERATURE = "temperature";
static const float SENSOR_TEMPERATURE_ALARM_LOW = 2.0;
static const float SENSOR_TEMPERATURE_ALARM_HIGH = 6.0;
static const float SENSOR_TEMPERATURE_VARIATION_PERCENTAGE = 10;

static const char* SENSOR_DOOR_NAME = "door";
static const uint8_t SENSOR_DOOR_PIN = D1;
static const unsigned long SENSOR_DOOR_NOTIFY_INTERVAL = 1000; // Every second.
static const unsigned long SENSOR_DOOR_ALARM_NOTIFY_AFTER = 10000;

static const char* SENSOR_BOX_NAME = "box";
static const uint8_t SENSOR_BOX_PIN = D2;
static const unsigned long SENSOR_BOX_NOTIFY_INTERVAL = 1000; // Every second.
static const unsigned long SENSOR_BOX_ALARM_NOTIFY_AFTER = 0;

static const char* SENSOR_DS18B20_NAME = "ds18b20";
static const uint8_t SENSOR_DS18B20_PIN = D3;
static const uint8_t SENSOR_DS18B20_PRECISION = 12;
static const unsigned long SENSOR_DS18B20_NOTIFY_INTERVAL = 1000; // Every second.

static const char* SENSOR_SCT013_NAME = "sct013";
static const uint8_t SENSOR_SCT013_PIN = A0;
static const unsigned long SENSOR_SCT013_NOTIFY_INTERVAL = 1000; // Every second.
// http://webmeteobox.ru/docs/SCT013-030V.pdf
static const float SENSOR_SCT013_TURNRATIO = 1800.0;
static const float SENSOR_SCT013_RESISTANCE = 62.0;

static const uint8_t ALARM_BUZZER_PIN = D3;
static const unsigned long ALARM_MINIMUM_TIME = 2000;
static const uint8_t STATUS_PIN = D4; // LED_BUILTIN

static const char* RELE_NAME = "fridge";
static const uint8_t RELE_PIN = D5;

static const char* STATUS_ON = "on";
static const char* STATUS_OFF = "off";
