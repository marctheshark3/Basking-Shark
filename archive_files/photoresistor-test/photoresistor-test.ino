/* Photocell simple testing sketch. 
 
Connect one end of the photocell to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground 
Connect LED from pin 11 through a resistor to ground 
For more information see http://learn.adafruit.com/photocells */
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"
#include "DHT.h"

#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32

Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );


int fsrPin = A1;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider


int photocellPin = A12 ;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int LEDpin = 14;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        // 
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(115200); 

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
 
void loop(void) {
  
  Serial.print("Analog reading = ");
  fsrReading = analogRead(fsrPin);
  Serial.println(photocellReading);     // the raw analog reading
  
  if ((fsrReading > 1000)){
    delay(1000);
    tft.println("Touch Engaged");
    digitalWrite(14, HIGH);
    delay( 5000);
    
    
  }
  photocellReading = analogRead(photocellPin);  
 
  
  
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  digitalWrite(14, HIGH);
 
  delay(100);
}
