#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/
#define WLAN_SSID      "The Morty - est Morty"
#define WLAN_PASS       "Margaritarick" 
//#define WLAN_SSID       "pd3d"
//#define WLAN_PASS       "n3w.pas."

/************************* MQTT Setup *********************************/


#define MQTT_SERVER     "192.168.0.15"                 // URL to the RPi running MQTT
#define MQTT_SERVERPORT 1883                               // MQTT service port
#define MQTT_USERNAME   ""
#define MQTT_PASSWORD   ""


// Create an ESP-32 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt( &client, MQTT_SERVER, MQTT_SERVERPORT );

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish   soil1   = Adafruit_MQTT_Publish( &mqtt, "/feeds/soil_sensor/1" );
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe( &mqtt, "/feeds/onoff" );

#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
const int AirValue = 3400;   //you need to replace this value with Value_1
const int WaterValue = 660;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;   
int soilMoistureValue = 0;
void setup() {
  Serial.begin(115200); // open serial port, set the baud rate to 9600 bps
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  mqtt.subscribe(&onoffbutton);
}
void loop() {
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))){
    Serial.print("Performing");
    if (subscription == &onoffbutton){
      Serial.print("READ");
      delay(30000);
    }
  }
    soilMoistureValue = analogRead(A3);  //put Sensor insert into soil
    
 if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
{
  Serial.println("Very Wet");
  soil1.publish("Very Wet");
}
else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
{
  Serial.println("Wet");
  soil1.publish(" Wet");
}
else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
{
  Serial.println("Dry");
  soil1.publish("Dry");
}
delay(100);

    


}


void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
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
