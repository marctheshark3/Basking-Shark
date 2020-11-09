#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>                              // Hardware-specific library
#include "Adafruit_miniTFTWing.h"

#include <Wire.h>

#include <SparkFun_VL6180X.h>

/*const float GAIN_1    = 1.01;  // Actual ALS Gain of 1.01
const float GAIN_1_25 = 1.28;  // Actual ALS Gain of 1.28
const float GAIN_1_67 = 1.72;  // Actual ALS Gain of 1.72
const float GAIN_2_5  = 2.6;   // Actual ALS Gain of 2.60
const float GAIN_5    = 5.21;  // Actual ALS Gain of 5.21
const float GAIN_10   = 10.32; // Actual ALS Gain of 10.32
const float GAIN_20   = 20;    // Actual ALS Gain of 20
const float GAIN_40   = 40;    // Actual ALS Gain of 40
*/
#define VL6180X_ADDRESS 0x29

#define TFT_RST  -1                                       // we use the seesaw for resetting to save a pin
#define TFT_CS   14
#define TFT_DC   32


Adafruit_miniTFTWing  ss;
Adafruit_ST7735       tft = Adafruit_ST7735( TFT_CS,  TFT_DC, TFT_RST );
#include <Fonts/FreeSerif18pt7b.h>

float Variable1;
float Variable2;

VL6180xIdentification identification;
VL6180x sensor(VL6180X_ADDRESS);

void setup() {

  Serial.begin(115200); //Start Serial at 115200bps
  Wire.begin(); //Start I2C library
  delay(100); // delay .1s

  sensor.getIdentification(&identification); // Retrieve manufacture info from device memory
  printIdentification(&identification); // Helper function to print all the Module information

    if(sensor.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
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
  
}

void loop() {

  //Get Ambient Light level and report in LUX
  Serial.print("Ambient Light Level (Lux) = ");
  
  //Input GAIN for light levels, 
  // GAIN_20     // Actual ALS Gain of 20
  // GAIN_10     // Actual ALS Gain of 10.32
  // GAIN_5      // Actual ALS Gain of 5.21
  // GAIN_2_5    // Actual ALS Gain of 2.60
  // GAIN_1_67   // Actual ALS Gain of 1.72
  // GAIN_1_25   // Actual ALS Gain of 1.28
  // GAIN_1      // Actual ALS Gain of 1.01
  // GAIN_40     // Actual ALS Gain of 40
  
  Serial.println( sensor.getAmbientLight(GAIN_1) );

  //Get Distance and report in mm
  Serial.print("Distance measured (mm) = ");
  Serial.println( sensor.getDistance() ); 

  //tft.println(sensor.getDistance());
  delay(500);  

 // display section
 tft.setTextSize(0);  // Set text size. We are using custom font so you should always set text size as 0

 tft.setCursor(0,0);

 
 Variable1 = sensor.getAmbientLight(GAIN_1);
 Variable2 = sensor.getDistance();

 //flux readings
 tft.setTextColor(ST7735_MAGENTA, ST7735_BLACK);  // Set color of text. First is the color of text and after is color of background
 tft.setTextSize(2);
 tft.setCursor(0,0);
 tft.println("Flux Scan"); tft.print(Variable1);

 tft.setCursor(0,32);
 // distance readings 
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
 
 

  
};

void printIdentification(struct VL6180xIdentification *temp){
  Serial.print("Model ID = ");
  Serial.println(temp->idModel);

  Serial.print("Model Rev = ");
  Serial.print(temp->idModelRevMajor);
  Serial.print(".");
  Serial.println(temp->idModelRevMinor);

  Serial.print("Module Rev = ");
  Serial.print(temp->idModuleRevMajor);
  Serial.print(".");
  Serial.println(temp->idModuleRevMinor);  

  Serial.print("Manufacture Date = ");
  Serial.print((temp->idDate >> 3) & 0x001F);
  Serial.print("/");
  Serial.print((temp->idDate >> 8) & 0x000F);
  Serial.print("/1");
  Serial.print((temp->idDate >> 12) & 0x000F);
  Serial.print(" Phase: ");
  Serial.println(temp->idDate & 0x0007);

  Serial.print("Manufacture Time (s)= ");
  Serial.println(temp->idTime * 2);
  Serial.println();
  Serial.println();
}
