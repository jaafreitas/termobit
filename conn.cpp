#include <ESP8266WiFi.h>
#include "settings.h"
#include "debug.h"
#include "conn.h"
#include "version.h"

WiFiClient wifiClient;

extern String uptime;

long lastMQTTReconnectAttempt = -10000;

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
          notify("version", version, true);
          if (uptime.length() > 0) {
            notify("uptime", uptime, true);
          }

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

void Conn::notify(String topic, String payload, bool retained) {
  debugMsg("-> %s: %s\n", fullTopic(topic).c_str(), payload.c_str());
  this->_PubSubClient->publish(fullTopic(topic).c_str(), payload.c_str(), retained);
}