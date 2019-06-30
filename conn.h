#pragma once

#include <Arduino.h>
#include "src/PubSubClient/PubSubClient.h"

class Conn {
  public:
    Conn(String hostname);
    void loop();
    void notify_sensor(String sensor, float value, bool alarm);
    void notify_sensor(String sensor, String value, bool alarm);
    void notify_topic(String topic, String payload, bool retained = false);
  private:
    String _hostname;
    PubSubClient* _PubSubClient;
    void connect();
    String fullTopic(String topic);
};
