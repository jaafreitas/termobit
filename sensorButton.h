#pragma once

#include <Arduino.h>
#include "conn.h"

void setupSensorButton();

void loopSensorButton( CONN_NOTIFY_SENSOR_STRING );
