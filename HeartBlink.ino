/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products

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

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
int i = 1;
/*  Heartbeat - Turns on an LED in a heartbeat pattern.

  Most Arduinos have an on-board LED. On the UNO, MEGA and ZERO and Duo it is attached to digital pin 13
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
//#define LED_BUILTIN 2
// the setup function runs once when you reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
#ifdef ESP8266
  WiFi.disconnect();
  WiFi.forceSleepBegin();
  delay(1);
#endif
}
// the loop function runs over and over again forever
void loop() {
  blinkIt(0);
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

