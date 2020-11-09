
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


/************************* WiFi Access Point *********************************/
#define WLAN_SSID      "The Morty - est Morty"
#define WLAN_PASS       "Margaritarick" 
//#define WLAN_SSID       "pd3d"
//#define WLAN_PASS       "n3w.pas."

const char *ssid = "ESPecially not your network";
const char *password = "ilovemycactus";

 
/************************* MQTT Setup *********************************/

#define MQTT_SERVER     "192.168.0.15"                 // URL to the RPi running MQTT
#define MQTT_SERVERPORT 1883                              // MQTT service port
#define MQTT_USERNAME   ""
#define MQTT_PASSWORD   ""



// Create an ESP-32 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt( &client, MQTT_SERVER, MQTT_SERVERPORT );

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish   soil1   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor1/message" );
Adafruit_MQTT_Publish   soil2   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor2/message" );
Adafruit_MQTT_Publish   soil3   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor3/message" );

Adafruit_MQTT_Publish   soil_val1   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor1/sensor_val" );
Adafruit_MQTT_Publish   soil_val2   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor2/sensor_val" );
Adafruit_MQTT_Publish   soil_val3   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor3/sensor_val" );

Adafruit_MQTT_Publish   temperture  = Adafruit_MQTT_Publish( &mqtt, "/feeds/temp" );
Adafruit_MQTT_Publish   humidity   = Adafruit_MQTT_Publish( &mqtt, "/feeds/humidity" );
Adafruit_MQTT_Publish   heat_index   = Adafruit_MQTT_Publish( &mqtt, "/feeds/heat" );

Adafruit_MQTT_Publish   light   = Adafruit_MQTT_Publish( &mqtt, "/feeds/light" );

Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe( &mqtt, "/feeds/onoff" );

#include "Adafruit_seesaw.h"

int photocellPin = A2 ;     // the cell and 10K pulldown are connected to a0
 
void setup() {
  Serial.begin(115200);
  
  
  // open serial port, set the baud rate to 9600 bps
  // Connect to WiFi access point.
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  

  
  
}
 
void loop() {
  Serial.println("light");
  Serial.println(analogRead(photocellPin));
  int photocellReading = analogRead(photocellPin);  
  Serial.println(photocellReading);

}
