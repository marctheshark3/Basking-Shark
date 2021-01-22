#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#include <Wire.h>
#include <SparkFun_VL6180X.h>

// Temperature stuff
#include "DHT.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define DHTPIN A1
#define DHTTYPE DHT11 

#define VL6180X_ADDRESS 0x29

#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32
#define WLAN_SSID      "The Morty - est Morty"//"pd3d"
#define WLAN_PASS       "Margaritarick" //"n3w.pas."
//#define WLAN_SSID     "pd3d" // "The Morty - est Morty"//
//#define WLAN_PASS      "n3w.pas."// "Margaritarick" //
#define MQTT_SERVER     "broker.hivemq.com"                 // URL to the RPi running MQTT
#define MQTT_SERVERPORT 1883                                // MQTT service port
#define MQTT_USERNAME   ""
#define MQTT_PASSWORD   ""


VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);


DHT dht(DHTPIN, DHTTYPE);

Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );

WiFiClient client;

Adafruit_MQTT_Client mqtt( &client, MQTT_SERVER, MQTT_SERVERPORT );

/****************************** Feeds ***************************************/

Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish( &mqtt, "ids6938/student/marc/sensor/temperature",MQTT_QOS_1);
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish( &mqtt, "ids6938/student/marc/sensor/humidity" ,MQTT_QOS_1);
Adafruit_MQTT_Publish proximity = Adafruit_MQTT_Publish( &mqtt, "ids6938/student/marc/sensor/proximity" ,MQTT_QOS_1);
Adafruit_MQTT_Publish lux = Adafruit_MQTT_Publish( &mqtt, "ids6938/student/marc/sensor/lux",MQTT_QOS_1 );

Adafruit_MQTT_Subscribe onoff = Adafruit_MQTT_Subscribe( &mqtt, "ids6938/student/marc/control/light" ,MQTT_QOS_1);
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe( &mqtt, "ids6938/student/marc/control/light2" ,MQTT_QOS_1);

Adafruit_MQTT_Subscribe markus_proxi = Adafruit_MQTT_Subscribe( &mqtt, "ids6938/student/marcus/sensor/proximity" ,MQTT_QOS_1);
Adafruit_MQTT_Subscribe kamryx_proxi = Adafruit_MQTT_Subscribe( &mqtt, "ids6938/student/kamryx/sensor/proximity" ,MQTT_QOS_1);
Adafruit_MQTT_Subscribe kamryx_light = Adafruit_MQTT_Subscribe( &mqtt, "ids6938/student/kamryx/control/buttonone" ,MQTT_QOS_1);

/*************************** Sketch Code ************************************/

float dist = 0;
float light = 0;
int i = 0;
float newdist = 0;
float newlight = 0;
float temp_val = 0;
float humid_val = 0;
float newtemp = 0;
float newhumid = 0;
void setup()
{
  Serial.begin( 115200 );
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  Serial.print( "Connecting to " );
  Serial.println( WLAN_SSID );

  WiFi.begin( WLAN_SSID, WLAN_PASS );
  
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay( 500 );
    Serial.print( "." );
  }
  mqtt.subscribe(&onoff);
  Serial.println();

  Serial.println( "WiFi connected" );
  Serial.println( "IP address: " );
  Serial.println( WiFi.localIP() );
  
  if(sensor.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
    tft.println("FAILED TO INITALIZE"); //Initialize device and check for errors
   
  } 
  sensor.VL6180xDefautSettings(); //Load default settings to get started.
  
    delay(1000); // delay 1s
   if ( !ss.begin() )
  {
    Serial.println( "seesaw couldn't be found!" );
    while( 1 );
  }

  Serial.print( "seesaw started .... \tVersion: " );
  Serial.println( ss.getVersion(), HEX );
  dht.read();
  ss.tftReset();   // reset the display
  
  tft.initR( INITR_MINI160x80 );                          // initialize a ST7735S chip, mini display
  tft.fillScreen(ST7735_BLACK);  // Fill screen with black

  Serial.println( "TFT initialized" );
  
  tft.setTextWrap(true);
  tft.setRotation(1);
  tft.fillScreen( ST77XX_BLACK );
  tft.setCursor(0, 0);  // Set position (x,y)
  tft.println( "TFT initialized" );

  
  //mqtt.subscribe(&led);
  

}

void loop() {
  
  Serial.println(F("Before subb"));
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))){
    Serial.print("Performing");
    if (subscription == &onoff){
      Serial.println("onoff");
      Serial.println((char *)onoff.lastread);
      uint16_t onoffval = atoi((char *)onoff.lastread);
      Serial.println(onoffval);
      if (onoffval == 1){
        digitalWrite(A0, HIGH);
        
      }
      if (onoffval == 0){
        digitalWrite(A0, LOW);
      }      
    }
    }
   
  Serial.println(F("AFTER subb"));
  newdist = dist;
  
  
  light = sensor.getAmbientLight(GAIN_1);
  dist = sensor.getDistance();
  
  
  Serial.println("\nSending photocell val ");
  Serial.println(light);
  Serial.println("");
  
  //lux.publish(light);
  
  //proximity.publish(432);
  Serial.println("\nSending distance val ");
  Serial.println(dist);
  Serial.println("");
  
  temp_val = dht.readTemperature();
  humid_val = dht.readHumidity();

  Serial.print("Temperature and Humidity:"); Serial.print(temp_val); Serial.print(" and "); Serial.print(humid_val); Serial.println(""); 

  lux.publish(light);
  humidity.publish(humid_val);
  //temphumid.publish(humid_val);
  temperature.publish(temp_val);
  //temphumid.publish(temp_val);
  proximity.publish(dist);
 
 
   tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0

   tft.setCursor(0,0); 
   
   //flux readings
   tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
   tft.setTextSize(2);
   tft.println("Flux Scan"); tft.print(light);
   // distance readings 
   tft.setCursor(0,32); 
   tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
   tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
   tft.print("Distance Scan"); tft.print(dist);

   
   lite(light);
  
   
    
}


void lite(float light){
  if(light < 10)  // If Variable1 is less than 10...
  {
    // Fill the other digit with background color:
    tft.fillRect(45, 15, 10 * 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(light < 100)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(60, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(light < 1000)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(70, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(light < 10000)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(90, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  
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
