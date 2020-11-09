// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN           10


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
#define NUMPIXELS2      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(100, 6, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//#if defined (__AVR_ATtiny85__)
 // if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
  // End of trinket special code
  //pixels.setBrightness(255);
  pixels.begin(); // This initializes the NeoPixel library.
  //pixels.setBrightness(255);
  pixels.show();
 
  
 
}
int color1a;
int color1b;
int color1c;
int color2a;
int color2b;
int color2c;

void loop() {
 
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  
  color1a = 255;
  color1b = 20;
  color1c = 147;
  color2a = 200;
  color2b = 0;
  color2c = 150;

  /*
  pixels.setPixelColor(1, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(2, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(3, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(4, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(5, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(6, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(7, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(8, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(9, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(10, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(11, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(12, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(13, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(14, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(15, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(16, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(17, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(18, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(19, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(20, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(21, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(22, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(23, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(24, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(25, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(26, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(27, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(28, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(29, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(30, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(31, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(32, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(33, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(34, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(35, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(36, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(37, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(38, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(39, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(40, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(41, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(42, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(43, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(44, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(45, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(46, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.setPixelColor(47, pixels.Color(color1a,color1b,color1c)); // Deep Pink
  pixels.setPixelColor(48, pixels.Color(color2a,color2b,color2c)); // Deep Pink
  pixels.show(); 
  */
  

  
  for(int i=0;i<NUMPIXELS;i++){
  
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(color2a,color2b,color2c)); // Deep Pink
    
    pixels.show(); // This sends the updated pixel color to the hardware.
    
    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  
  
}
