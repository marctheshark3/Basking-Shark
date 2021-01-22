/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID      "pd3d" //"The Morty - est Morty"
#define WLAN_PASS      "n3w.pas." // "Margaritarick"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "marctheshark"
#define AIO_KEY         "ffc7ff71f4eb46e4bebf2c92876ad35c"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#include <Wire.h>
#include <SparkFun_VL6180X.h>
#define VL6180X_ADDRESS 0x29
#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32



VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);


Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );

float Variable1;
float Variable2;

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell", MQTT_QOS_1);
Adafruit_MQTT_Publish distance = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/distance",MQTT_QOS_1);
const char WILL_FEED[] PROGMEM = AIO_USERNAME "/feeds/willfeed";
Adafruit_MQTT_Publish lastwill = Adafruit_MQTT_Publish(&mqtt, WILL_FEED, MQTT_QOS_1);
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff",MQTT_QOS_1);

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  Serial.begin(115200);
  delay(10);
  Wire.begin();

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

   tft.println(); tft.println();
  tft.print("Connecting to ");
  tft.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  tft.println("WiFi connected");
  tft.println("IP address: "); tft.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
  

   if(sensor.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
    tft.println("FAILED TO INITALIZE"); //Initialize device and check for errors
   
  }; 
  sensor.VL6180xDefautSettings(); //Load default settings to get started.
  
    delay(1000); // delay 1s
   if ( !ss.begin() )
  {
    Serial.println( "seesaw couldn't be found!" );
    while( 1 );
  }

  Serial.print( "seesaw started .... \tVersion: " );
  Serial.println( ss.getVersion(), HEX );

  ss.tftReset();   // reset the display
  
  tft.initR( INITR_MINI160x80 );                          // initialize a ST7735S chip, mini display
  tft.fillScreen(ST7735_BLACK);  // Fill screen with black

  Serial.println( "TFT initialized" );

  tft.setTextWrap(true);
  tft.setRotation(1);
  tft.fillScreen( ST77XX_BLACK );
  tft.setCursor(0, 0);  // Set position (x,y)
  
  mqtt.will(WILL_FEED, "Power OFF"); 
  
}

float x=0;
float y=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
  lastwill.publish("Power ON");  // make sure we publish ON first thing after connecting
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  

  Adafruit_MQTT_Subscribe *subscription;
  
  while ((subscription = mqtt.readSubscription(6000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      if (String((char *)onoffbutton.lastread) == "LED ON"){
        digitalWrite(A0, HIGH);
      }
      if (String((char *)onoffbutton.lastread) == "LED OFF"){
        digitalWrite(A0, LOW);
      }
      
    }
  }

  // Now we can publish stuff!
  x = sensor.getAmbientLight(GAIN_1);
  y = sensor.getDistance();
  Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.println("");
  
  Serial.print("...");
  photocell.publish(x);
  distance.publish(y);
  Serial.print(F("\nSending distance val "));
  Serial.print(y);
  Serial.println("");
  
  
   tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0

   tft.setCursor(0,0); 
   Variable1 = sensor.getAmbientLight(GAIN_1);
   Variable2 = sensor.getDistance();
  
   //flux readings
   tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
   tft.setTextSize(2);
   tft.println("Flux Scan"); tft.print(Variable1);
   // distance readings 
   tft.setCursor(0,32); 
   tft.setTextColor(ST7735_GREEN, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
   tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
   tft.print("Distance Scan"); tft.print(Variable2);
   
 if(Variable1 < 10)  // If Variable1 is less than 10...
  {
    // Fill the other digit with background color:
    tft.fillRect(45, 15, 10 * 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(Variable1 < 100)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(60, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(Variable1 < 1000)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(70, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  }
  if(Variable1 < 10000)  // If Variable1 is less than 100...
  {
    // Fill the other digit with background color:
    tft.fillRect(90, 15, 9* 15, 18, ST7735_BLACK);  // Draw filled rectangle (x,y,width,height,color)
  

 }
  

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
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
