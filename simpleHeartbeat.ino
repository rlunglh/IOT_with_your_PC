/*
  Heartbeat - Turns on an LED in a heartbeat pattern.

  Most Arduinos have an on-board LED. On the UNO, MEGA and ZERO and D1mini it is attached to digital pin 13
  LED_BUILTIN should be set to the LED pin for the board in use.
  This example code is in the public domain.
  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
  modified 26 May 2017
by Rick Lunglhofer
*/
// the setup function runs once when you reset or power the board

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
// the loop function runs over and over again forever
void loop() {
  blinkIt(1);
  delay(1100);  // wait 1.1 seconds
}
void blinkIt(int polarity)
{
  if (polarity==1) {
  digitalWrite(LED_BUILTIN, HIGH);// turn the LED on
  delay(200);  // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off
  delay(200);  // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, HIGH);// turn the LED on
  delay(200); // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, LOW); // turn the LED off
  }
  else {
  digitalWrite(LED_BUILTIN, LOW);// turn the LED on
  delay(200);  // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED off
  delay(200);  // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, LOW);// turn the LED on
  delay(200); // wait for 200 milliseconds
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED off
  }
} 
