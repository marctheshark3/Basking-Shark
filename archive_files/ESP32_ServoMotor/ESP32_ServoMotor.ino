#define BASE_STEP      0              // ...it's actually '1', 
#define SERVO_STEPS 8888              // number of servo steps
#define ROTATION     180              // servo rotational range
#define RESOLUTION    16              // 16-bit timer resolution
#define LED_CHANNEL    1              // channel 1
#define FREQUENCY     50              // 50 Hz PWM
#define SERVO_PIN     A0              // servo signal-connection pin

void setup()
{
   Serial.begin( 115200 );
   ledcSetup( LED_CHANNEL, FREQUENCY, RESOLUTION );
   ledcAttachPin( SERVO_PIN, LED_CHANNEL );

   delay( 500 );                      // set servo to different positions
   servoPos(  90 ); delay( 2000 );
   servoPos(   1 ); delay( 2000 );
   servoPos(  45 ); delay( 2000 );
   servoPos(  90 ); delay( 2000 );
   servoPos( 135 ); delay( 2000 );
   servoPos( 180 ); delay( 2000 );

   delay( 500 );                      // sweep servo CCW and CW
   sweep( 25 );
}


void loop()
{
  if ( Serial.available() > 0 )       // set servo to serial iput value
  {
    
    servoPos( Serial.parseInt() );
  }
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
