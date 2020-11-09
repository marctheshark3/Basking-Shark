#include <SD.h>
#include "Adafruit_EPD.h"

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* DHT *********************************/
#include "DHT.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define DHTPIN A1
#define LEDpin 21
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5 //1hour         /* Time ESP32 will go to sleep (in seconds) */


RTC_DATA_ATTR int bootCount = 0;



const int AirValue = 3400;   //you need to replace this value with Value_1
const int WaterValue = 660;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;   
float soilMoistureValue1 = 0;
float soilMoistureValue2 = 0;
float soilMoistureValue3 = 0;

void setup() {
  
  Serial.begin(115200); 
  dht.begin();
  
}
void loop() {
  
  digitalWrite(LEDpin, HIGH);
  int photocellPin = A2;
  int photocellReading;
  Serial.println("Light");
  photocellReading = analogRead(photocellPin);  
  Serial.println(photocellReading);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  
  soilMoistureValue1 = analogRead(A7);
  soilMoistureValue2 = analogRead(A9);
  //soilMoistureValue3 = analogRead(A4);
 
  
  if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
 
  
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
    
  Serial.print(hif);
  Serial.println(F("°F"));


  Serial.println(soilMoistureValue1);
  Serial.println(soilMoistureValue2);
  //Serial.println(soilMoistureValue3);
  delay(2000);
  
  


  // Draw some text
  /*
  epd.clearBuffer();
  epd.setCursor(10, 10);
  epd.setTextColor(EPD_BLACK);
  epd.print("Soil Value for Planter 1"); 
  epd.print(soilMoistureValue1);
  epd.setCursor(50, 70);
  epd.setTextColor(EPD_RED);
  epd.print("Soil Value for Planter 2"); 
  epd.print(soilMoistureValue2);
  epd.display();
  */
 ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  //print_wakeup_reason();

  /*
  First we configure the wake up source
  We set our ESP32 to wake up every 5 seconds
 
  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  //esp_deep_sleep_start();
  Serial.println("This will never be printed"); 
   */

  
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}
