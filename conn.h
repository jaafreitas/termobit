#pragma once

#include <Arduino.h>
#include "src/PubSubClient/PubSubClient.h"

#define CONN_NOTIFY void (*notify)(String, String, bool)

// String sensor, float valor
#define CONN_NOTIFY_SENSOR_FLOAT void (*notify)(String, float, bool)
#define CONN_NOTIFY_SENSOR_STRING void (*notify)(String, String, bool)

class Conn {
  public:
    Conn(String hostname);
    void loop();
    void notify_sensor(String sensor, float value, bool alarm);
    void notify_sensor(String sensor, String value, bool alarm);
    void notify(String topic, String payload, bool retained = false);
  private:
    String _hostname;
    PubSubClient* _PubSubClient;
    void connect();
    String fullTopic(String topic);
};
