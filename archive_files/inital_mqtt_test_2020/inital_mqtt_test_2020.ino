#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define LEDpin A1
#define BASE_STEP      0              // ...it's actually '1', 
#define SERVO_STEPS 8888              // number of servo steps
#define ROTATION     180              // servo rotational range
#define RESOLUTION    16              // 16-bit timer resolution
#define LED_CHANNEL    1              // channel 1
#define FREQUENCY     50              // 50 Hz PWM
#define SERVO_PIN     A0              // servo signal-connection pin

#define WLAN_SSID      "TaveRidge"
#define WLAN_PASS       "4uXdoggy!"

const char *ssid = "ESPecially not your network";
const char *password = "ilovemycactus";


//#define MQTT_SERVER     "10.0.0.91"  //Local 
#define MQTT_SERVER     "10.0.0.72"                 // URL to the RPi running MQTT
#define MQTT_SERVERPORT 1883                              // MQTT service port
#define MQTT_USERNAME   ""
#define MQTT_PASSWORD   ""

WiFiClient client;
Adafruit_MQTT_Client mqtt( &client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

Adafruit_MQTT_Publish test = Adafruit_MQTT_Publish( &mqtt, "topic/test");

Adafruit_MQTT_Subscribe pull = Adafruit_MQTT_Subscribe( &mqtt, "topic/sendit/", MQTT_QOS_1 );
Adafruit_MQTT_Subscribe all_pull = Adafruit_MQTT_Subscribe( &mqtt, "topic",  MQTT_QOS_1);




void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, LOW);
  ledcSetup( LED_CHANNEL, FREQUENCY, RESOLUTION );
  ledcAttachPin( SERVO_PIN, LED_CHANNEL );
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
  Serial.println(" ");
  mqtt.subscribe(&pull);
  mqtt.subscribe(&all_pull);
  


  
}

void loop() {
  Serial.print("looping ");
  Serial.print("");
  digitalWrite(LEDpin, LOW);
  // put your main code here, to run repeatedly:
  if ( Serial.available() > 0 )       // set servo to serial iput value
  {
    
    servoPos( Serial.parseInt() );
    test.publish("test push");
    
  }
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(5000))){
    Serial.print("listening   ");
    if (subscription == &pull){
      Serial.print("pulling  ");
      int servo = atoi((char *)pull.lastread);
      servoPos(servo);
      test.publish("pull from subscribing works");
      test.publish(servo);
      Serial.print(servo);
      digitalWrite(LEDpin, HIGH);
      
    }
    if (subscription == &all_pull){
       int servo = atoi((char *)pull.lastread);
       Serial.print("pulling");
       Serial.print((char *)all_pull.lastread);
       servoPos(180);
    }

  }
  Serial.print("after   ");
}
void sweep( int t )
{
   for ( int i = BASE_STEP ; i <= SERVO_STEPS ; i += 100 )
   {
      ledcWrite( LED_CHANNEL, i );
      delay( t );
   }
   for ( int i = SERVO_STEPS ; i >= BASE_STEP ; i -= 100 )
   {
      ledcWrite( LED_CHANNEL, i );
      delay( t );
   }
}

void servoPos( int p )
{
  int value = (float)SERVO_STEPS / (float)ROTATION * (float)p;
  ledcWrite( LED_CHANNEL, value );

  if ( p > 0 )
  {
    Serial.print( "input: " ); Serial.println( p );
    Serial.print( "servo: " ); Serial.println( value );
    Serial.println();
  }
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
