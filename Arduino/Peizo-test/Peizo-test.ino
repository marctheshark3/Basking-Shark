
#include <Tone.h>
#define PIEZO_PIN  13     // Pin connected to the piezo buzzer.

// Define list of tone frequencies to play.
int toneFreq[] = { 262,   // C4
                   294,   // D4
                   330,   // E4
                   349,   // F4
                   392,   // G4
                   440,   // A4
                   494 }; // B4
int toneCount = sizeof(toneFreq)/sizeof(int);
 
void setup() {
  // No setup necessary!
  pinMode(13,OUTPUT);
}
 
void loop() {
  tone(13,294,5000);
}
