void setup ()
{
pinMode (A0, OUTPUT); // define the digital output interface 13 feet
}
void loop () {
digitalWrite (A0, HIGH); // open the laser head 
delay(500);
digitalWrite (A0, LOW); // open the laser head 
delay(500);
 
}
