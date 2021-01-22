#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;
const int AirValue = 3400;   //you need to replace this value with Value_1
const int WaterValue = 660;  //you need to replace this value with Value_2
int intervals = (AirValue - WaterValue)/3;   
int soilMoistureValue1 = 0;
int soilMoistureValue2 = 0;
int soilMoistureValue3 = 0;
void setup() {
  Serial.begin(115200);

  Serial.println("seesaw Soil Sensor example!");
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  delay(1000);

  soilMoistureValue1 = analogRead(A0);
  Serial.println("Planter 1");
  if(soilMoistureValue1 > WaterValue && soilMoistureValue1 < (WaterValue + intervals))
{
  Serial.println("Very Wet");
}
else if(soilMoistureValue1 > (WaterValue + intervals) && soilMoistureValue1 < (AirValue - intervals))
{
  Serial.println("Wet");
}
else if(soilMoistureValue1 < AirValue && soilMoistureValue1 > (AirValue - intervals))
{
  Serial.println("Dry");
}
delay(1000);

soilMoistureValue2 = analogRead(A2);
Serial.println("Planter 2");
  if(soilMoistureValue2 > WaterValue && soilMoistureValue2 < (WaterValue + intervals))
{
  Serial.println("Very Wet");
}
else if(soilMoistureValue2 > (WaterValue + intervals) && soilMoistureValue2 < (AirValue - intervals))
{
  Serial.println("Wet");
}
else if(soilMoistureValue2 < AirValue && soilMoistureValue2 > (AirValue - intervals))
{
  Serial.println("Dry");
}
delay(1000);
soilMoistureValue3 = analogRead(A3);
Serial.println("Planter 3");
  if(soilMoistureValue3 > WaterValue && soilMoistureValue3 < (WaterValue + intervals))
{
  Serial.println("Very Wet");
}
else if(soilMoistureValue3 > (WaterValue + intervals) && soilMoistureValue3 < (AirValue - intervals))
{
  Serial.println("Wet");
}
else if(soilMoistureValue3 < AirValue && soilMoistureValue3 > (AirValue - intervals))
{
  Serial.println("Dry");
}
delay(1000);
}
