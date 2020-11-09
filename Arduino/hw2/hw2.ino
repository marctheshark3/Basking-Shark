

#include <dht_nonblocking.h>

/* Uncomment according to your sensortype. */
#define DHT_SENSOR_TYPE DHT_TYPE_11
//#define DHT_SENSOR_TYPE DHT_TYPE_21
//#define DHT_SENSOR_TYPE DHT_TYPE_22

static const int DHT_SENSOR_PIN = A0;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );


void setup( )
{
  Serial.begin( 115200);
}
/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}



//menu beginning 
char menu;
char subMenu;
bool runOnce = true;
bool menuState = true;


void topMenu() {
   
  if (runOnce == true) {
    Serial.println ("                     Main Menu: Would you like to measure Temperature or Humidity?                           ");
    Serial.println (" A) Temperature!  B) Humidity! ");  
    runOnce = false;
    menuState = true;
  }      
}

void loop() {
  float temperature;
  float humidity;
 
   topMenu();   
   while (Serial.available() == 0) {}    
   if( measure_environment( &temperature, &humidity ) == true )
  {
   if (menuState == true) {
    
    char menu = Serial.read(); 
    if (menu == 'a') {       
      Serial.println ("Measuring Temperature!");
      Serial.print( temperature, 1 );
      Serial.print( " deg. C" );
      Serial.print(" \n ");
      topMenu();
     
   
    }
    else if (menu == 'b') {       
      Serial.println ("Measuring Humidity!");
      Serial.print( " H =" );
      Serial.print( humidity, 1 );
      Serial.println( "%" );
      Serial.print(" \n ");
      topMenu();
   
    }
  }} 
} 
