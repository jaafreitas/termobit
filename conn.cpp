#include <ESP8266WiFi.h>
#include "settings.h"
#include "debug.h"
#include "conn.h"
#include "version.h"
#include "alarm.h"

WiFiClient wifiClient;

extern String uptime;

long lastMQTTReconnectAttempt = -MQTT_CONNECTION_RETRY;

void setupWiFi(const char* hostname) {
  debugMsg("Starting WiFi Setup...\n", hostname);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);
  WiFi.disconnect();

  debugMsg("Connecting %s to SSID %s", hostname, WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    debugMsg(".");
  }
  debugMsg(" Ok.\n");

  debugMsg("IP address set to %s\n", WiFi.localIP().toString().c_str());
}

Conn::Conn(String hostname) {
  this->_hostname = hostname;

  setupWiFi(this->_hostname.c_str());

  this->_PubSubClient = new PubSubClient(wifiClient);
  this->_PubSubClient->setServer(MQTT_SERVER, MQTT_PORT);
}

void Conn::connect() {
  if (!this->_PubSubClient->connected()) {
      if (millis() - lastMQTTReconnectAttempt > MQTT_CONNECTION_RETRY) {
        lastMQTTReconnectAttempt = millis();
        debugMsg("Attempting MQTT connection to %s...", MQTT_SERVER);
        if (this->_PubSubClient->connect(this->_hostname.c_str())) {
          debugMsg(" Ok.\n");

          // Once connected, publish announcements...
          notify_topic("version", version, true);
        } else {
          debugMsg(" ERROR: %d. Trying again later.\n", this->_PubSubClient->state());
        }
      }
  }
};

void Conn::loop() {
  this->connect();
  this->_PubSubClient->loop();
}

String Conn::fullTopic(String topic) {
  return "station/" + this->_hostname + "/" + topic;
}

void Conn::notify_topic(String topic, String payload, bool retained) {
  debugMsg("-> %s: %s\n", fullTopic(topic).c_str(), payload.c_str());
  this->_PubSubClient->publish(fullTopic(topic).c_str(), payload.c_str(), retained);
}

void Conn::notify_alarm(String sensor, bool alarmIsTriggered) {
  alarm(alarmIsTriggered);
  notify_topic("alarm/" + sensor, alarmIsTriggered ? STATUS_ON: STATUS_OFF, false);
}

void Conn::notify_sensor(String sensor, String value) {
  notify_topic("sensor/" + sensor, value, false);
}

void Conn::notify_sensor(String sensor, String value, bool alarmIsTriggered) {
  notify_sensor(sensor, value);
  notify_alarm(sensor, alarmIsTriggered);
}

void Conn::notify_sensor(String sensor, float value) {
  static char payload[5];
  dtostrf(value, 5, 2, payload);

  notify_sensor(sensor, String(payload));
}

void Conn::notify_sensor(String sensor, float value, bool alarmIsTriggered) {
  notify_sensor(sensor, value);
  notify_alarm(sensor, alarmIsTriggered);
}
