/*
  Blink


  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. BUILTIN_LED is set to
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

//#define NO_SERIAL
//#define BUILTIN_LED D4
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include "ArduinoOTA.h"
#endif
char * ssid="LUNGLHOFER";
char * pass="homeplate";
int i = 1;
#ifdef ESP8266
void netConnect()
{
  char buf[100];
  long connetc = 0;
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    if (connetc % 60 == 0) {
      sprintf((char *)&buf, "\n%4d", connetc / 60);
      Serial.print((char *)&buf);
      Serial.print(F(" Connecting to WiFi "));
    }
    Serial.print(".");
#ifndef ESP32
    digitalWrite(BUILTIN_LED, connetc % 2);
#else
    digitalWrite(5, connetc % 2);
#endif
    connetc++;
    if (connetc >= 1200) {
#ifndef ESP32
      ESP.reset();
#endif
    }
  }
  digitalWrite(BUILTIN_LED, 1);
  Serial.println(F("Connected to the WiFi network"));
}
void printWifiStatus() 
{
  // print the SSID of the network you're attached to:
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(F("signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}
#endif
/*  Heartbeat - Turns on an LED in a heartbeat pattern.

  Most Arduinos have an on-board LED. On the UNO, MEGA and ZERO and Duo it is attached to digital pin 13
  BUILTIN_LED should be set to the LED pin for the board in use.
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
//#define BUILTIN_LED 16 // ESP32s ofter have an LED heere
// the setup function runs once when you reset or power the board
void setup() {
  // initialize digital pin BUILTIN_LED as an output.
  pinMode(BUILTIN_LED, OUTPUT);
#ifndef NO_SERIAL
  Serial.begin(115200);
  Serial.println(BUILTIN_LED);
#endif
#ifdef ESP8266
  netConnect();
  printWifiStatus();   ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    //Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.setHostname("HeartBeat"); 
  ArduinoOTA.begin();
#endif
}
// the loop function runs over and over again forever
long lcount=0;
void loop() {
#ifdef ESP8266
    ArduinoOTA.handle();
#endif
  delay(1);  // wait 1 millisecond
  lcount++;
  int polarity=0;
  if (lcount%1200==0) digitalWrite(BUILTIN_LED, polarity);// turn the LED on
  if (lcount%1200==2)digitalWrite(BUILTIN_LED, !polarity); // turn the LED off
  if (lcount%1200==300)digitalWrite(BUILTIN_LED, polarity);// turn the LED on
  if (lcount%1200==302)digitalWrite(BUILTIN_LED, !polarity); // turn the LED off
 
}
