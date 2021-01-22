/**
 The code is to be used on individual sensors so they push to the same topic

 think of a way how the ssid and pass can be entered or given from another device
 */
 
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFiManager.h>
WiFiManager wifiManager;

#include <PubSubClient.h>

#define WLAN_SSID      "PikesPeakHighFi"
#define WLAN_PASS       ""

#define MQTT_SERVER     "192.168.86.65"                 // URL to the RPi running MQTT
#define MQTT_SERVERPORT 1883                              // MQTT service port
#define MQTT_USERNAME   "marctheshark"
#define MQTT_PASSWORD   "cactusforall"

WiFiClient client;
Adafruit_MQTT_Client mqtt( &client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish( &mqtt, "/shark/plant_data/sensor_b/temp");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish( &mqtt, "/shark/plant_data/sensor_b/humidity");
Adafruit_MQTT_Publish heat_index = Adafruit_MQTT_Publish( &mqtt, "/shark/plant_data/sensor_b/heat");
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish( &mqtt, "/shark/plant_data/sensor_b/light");
Adafruit_MQTT_Publish soil = Adafruit_MQTT_Publish( &mqtt, "/shark/plant_data/sensor_b/soil");

Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe( &mqtt, "/shark/plant_data/sensor_b/led", MQTT_QOS_1 );
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe( &mqtt, "/shark/sensor_b/onoff" );


/************************* DHT *********************************/
#include "DHT.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  dht.begin();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("Trying to connect to: ");
  Serial.println(MQTT_SERVER);
  MQTT_connect();
 
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  /*
  int photocellPin = A1;
  int photocellReading;

  photocellReading = analogRead(photocellPin);
  Serial.println(photocellReading);
*/
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float heat = dht.computeHeatIndex(t, h);

  Serial.print(F("Humidity: "));
  Serial.print(h);

  Serial.print(F("%  Temperature: "));
  Serial.print(t);

  Serial.print(F("°F  Heat index: "));
  Serial.print(heat);
  Serial.println(F("°F"));

  temperature.publish(t);
  humidity.publish(h);
  heat_index.publish(heat);

  delay(5000);
  
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
