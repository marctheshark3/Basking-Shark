#include "DHT.h"
#include <SPI.h>


#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#define DHTPIN A0 
#define DHTTYPE DHT11 
#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32

Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );


float temperature = 0.0;
float humidity = 0.0;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(115200);
 dht.read();
 delay(100);

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

  tft.setRotation( 1 );

  tft.fillScreen( ST77XX_RED );
  delay( 100 );
  tft.fillScreen( ST77XX_GREEN );
  delay( 100 );
  tft.fillScreen( ST77XX_BLUE );
  delay( 100 );
  tft.fillScreen( ST77XX_BLACK );
}

void loop() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  tft.print("The measured temperature is: ");
  tft.println(temperature);
  tft.println("");
  tft.print("The humidity is measured to be:");
  tft.print(humidity); tft.print("% in the current env");
  delay(1000);
  tft.fillScreen( ST77XX_BLACK );
  tft.setCursor(0,0);

  

}
