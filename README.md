# termobit
Transform your fridge in a internet of things device.

## Documentation
### Before deploy
#### Check the wifi network
* WIFI_SSID "ssid"
* WIFI_PASSWORD "password"

#### Check the MQTT server
Example:
* MQTT_SERVER "test.mosquitto.org"
* MQTT_PORT 1883

#### Check the NTP server
Example:
* NTP_SERVER "a.st1.ntp.br"
* NTP_PORT 123
* NTP_LOCALPORT 2390
* NTP_INTERVAL 1 * 60 * 60 * 1000 // Every 1 hour (in milliseconds)
* TZ_OFFSET (-3 * 60 * 60) // in seconds.

### Avaliable MQTT topics

#### station/+/version
Example: 2019.06.23.1429

#### station/+/uptime
Example: 2019-06-23T14:29:23

#### station/+/datetime
Example: 2019-06-23T15:29:23
