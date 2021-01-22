#include <WiFi.h>
#include "time.h";

void setup() {
  Serial.begin(112500);
  //WiFi.begin("Lighthouse-5G","60669700");
  configTime(0,0,"pool.ntp.org","time.nist.gov");
  setenv("TZ","GMT0BST,M3.5.0/01,M10.5.0/02",1);

}

void loop() {
  Serial.println(get_time());

}

String get_time(){
  time_t now;
  time(&now);
  char time_output[30];
  strftime(time_output,30,"%r",localtime(&now));
  return String(time_output);
}
