#include "Maker_LED_Matrix.h" //Attaching the Maker LED Matrix library to our program
//Making a class object made in our library, and as an argument in the constructor we supply the data of which version of display we have (Maker Display 2 or Maker display 4)
//It is necessary only to comment the version of display we have:
//Maker_LED_Matrix matrix(MAKER_LED_MATRIX_2);
//Maker_LED_Matrix matrix(MAKER_LED_MATRIX_4);
void setup() {
Serial.begin(9600); //Start serial communication with 9600 baud
matrix.begin(&matrix); //Initialization of our library. As an argument, the address of our object is sent from the library. This is very important and has to be done, otherwise moving the photo on the display will not be possible!
matrix.brightness(25, 1); //Adjust the new display brightness. Set the font brightness to 25 of 255 and backgrounds to 1 of 255 (this will create an effect of the background brightness, if you do not want that, set it to zero).
//Display the message with a pause of 75 milliseconds between the steps and with a step of 2 pixels, and repeat the message 3 times.
//If the message needs to be constantly repeated, the last argument should be -1, and if we want it to be static, we must write zero.
matrix.message("Hello world! This is the message that will be displayed exactly 3 times.", 75, 2, 3);
delay(60000); //Make a pause long enough for the message to have enough time to display 3 times after which the display will remain empty.
//Send a new message with a pause of 100 milliseconds between the steps, with a step of 3 pixels and rotate it infinitely (until the new message deletes it).
matrix.message("This is a Maker LED Display made by the e-radionica team! :)", 100, 3, -1);
//Now follow how many times has this message displayed and wait for it to display exactly two times after which it continues with the program.
do{
delay(100); //Make a small delay for ESP8266 to have enough time to do its tasks (here has to be a delay, otherwise the ESP8266 will crash!).
}while(matrix.repeatCount() != 2);
matrix.message("The display is done in the background while we send how many times has this message repeated to the Serial Monitor", 100, 3, -1);
}
void loop() {
//Display the message on the Serial monitor (UART) while, at the same time, the message is shown on the display.
Serial.print("The message is displayed");
Serial.print(matrix.repeatCount(), DEC);
Serial.println(" puta.");
delay(1000);
}
