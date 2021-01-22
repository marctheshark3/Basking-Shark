#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#include "DHT.h"

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32

#define DHTPIN A1
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

int photocellPin = 32 ;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider


float temperature = 0.0;
float newtemp = 0.0;
float humidity = 0.0;

int fsrPin = A0; //A1     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider

Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );

void setup()
{
  Serial.begin( 115200 );
  pinMode(14, OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(14, HIGH);
  digitalWrite(13,LOW);
  dht.read();
  
  

/*
  while ( !Serial )  delay( 10 );                         // Wait until serial console is opened
//*/

  if ( !ss.begin() )
  {
    Serial.println( "seesaw couldn't be found!" );
    while( 1 );
  }

  Serial.print( "seesaw started .... \tVersion: " );
  Serial.println( ss.getVersion(), HEX );

  ss.tftReset();   // reset the display
  ss.setBacklight( TFTWING_BACKLIGHT_ON );                // turn off the backlight

  tft.initR( INITR_MINI160x80 );                          // initialize a ST7735S chip, mini display
  Serial.println( "TFT initialized" );
  
  tft.setTextWrap(true);
  tft.setRotation(1);
  tft.fillScreen( ST77XX_BLACK );
}

char menu;
char subMenu;
bool runOnce = true;
bool menuState = true;


void topMenu() 
{
  
  if (runOnce == true) {
    
    tft.println("Booting Up.....");
    delay(500);
   
    tft.println ("Would you like to measure Temperature or Humidity?");
    tft.println (" A) Temperature!  B) Humidity! ");  
    runOnce = false;
    menuState = true;
  }
       
}


  
void loop() {
  
  topMenu();
  fsrReading = analogRead(fsrPin); 
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.println(temperature);
  Serial.println(humidity);
  Serial.println("humidity");
 
  
  uint32_t buttons = ss.readButtons();
  uint16_t color;

 
  if ((fsrReading > 1000)){
    delay(1000);
    tft.println("Touch Engaged");
    digitalWrite(14, LOW);
    digitalWrite(13,HIGH);
    delay( 5000);
    tft.fillScreen( ST77XX_BLACK );
    tft.setCursor(0,0);
    runOnce = true;
    
  }

  else if (!(buttons & TFTWING_BUTTON_A)){
    tft.fillScreen( ST77XX_BLACK );
    tft.setCursor(0,0);
    delay(1000);
    tft.println("");
    tft.setTextWrap(true);
    tft.println ("Would you like Farenheit or Celcuis?");
    tft.println(" Left for F or Right for C");
  }
    // submenu for Units of Temperature
    else if (!(buttons & TFTWING_BUTTON_RIGHT)){
      newtemp = (temperature *9/5) + 32;
      
      tft.println(" Obtaining Temperature in Farenheit");
      delay( 2000);
      tft.print("The Temperature is:"); tft.print( newtemp, 1 );  tft.print( " deg. F" ); tft.print(" \n ");
      delay(5000);
 
      runOnce = true;
      tft.fillScreen( ST77XX_BLACK );
      tft.setCursor(0,0);
      
      
    }

    else if (!(buttons & TFTWING_BUTTON_LEFT)){
      
      tft.println(" Obtaining Temperature in Celcius");
      delay( 2000);
      tft.print("The Temperature is:"); tft.print( temperature, 1 );  tft.print( " deg. C" ); tft.print(" \n ");
      delay(5000);
 
      runOnce = true;
      tft.fillScreen( ST77XX_BLACK );
      tft.setCursor(0,0);
      
    }
  
  
  else if (!( buttons & TFTWING_BUTTON_B ) )
  {
     delay(1000);
    tft.println("");
    tft.println ("Measuring Humidity!");
    delay( 2000);
    tft.print("Current Env has "); tft.print( humidity, 1 ); tft.print( " % Humidity" );
    tft.print(" \n ");
    delay(5000);
    
    runOnce = true;
    tft.fillScreen( ST77XX_BLACK );
    tft.setCursor(0,0);
    
   
  }
  
    topMenu(); 
  }







  
  
