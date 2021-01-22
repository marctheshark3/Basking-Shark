#include <Stepper.h>

#define STEPS 200

// will need to change 
int pina = 4;
int pinb = 5;
int pinc = 6;
int pind = 7;
Stepper stepper(STEPS, pina,pinb,pinc,pind);

//setting up the variables for the timer
unsigned long feeding_time = 100;
unsigned long closing_time = 2400;

//Sleep settings
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */


void setup() {
  // put your setup code here, to run once:
  Serial.begin(112500);
  Serial.println("Stepper Test");
  //intializing the setup of the rpms to 30
  stepper.setSpeed(60);


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Forward");
  stepper.step(STEPS);
  Serial.println("Backward");
  stepper.step(-STEPS);

  //timer 
  unsigned long millis_now = millis();

  if ( millis_now == feeding_time){
    //start the stepper motor for some many seconds
    // will need to verify that this command is timed.
    stepper.step(STEPS);
  }
  // feeding time number two! 
  else if ( millis_now  == feeding_time *2 ){
    //start the stepper motor for some many seconds
    // will need to verify that this command is timed.
    stepper.step(STEPS);
    
}
  else ( millis_now  == closing_time){
    //restart the esp32 to restart millis
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
    
};
}
