#pragma once

#include <Arduino.h>
#include "src/PubSubClient/PubSubClient.h"

#define CONN_NOTIFY void (*notify)(String, String, bool)

class Conn {
  public:
    Conn(String hostname);
    void loop();
    void notify(String topic, String payload, bool retained = false);
  private:
    String _hostname;
    PubSubClient* _PubSubClient;
    void connect();
    String fullTopic(String topic);
};
