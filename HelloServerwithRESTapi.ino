#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//const char* ssid = "........";
//const char* password = "........";
#include "credentials.h"

ESP8266WebServer server(80);

const int led = LED_BUILTIN;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
int pwmFreq=100;
int pwmRange=32767;

byte dpins[]=   {D0,D1,D2,D3,D4,D5,D6,D7,D8};
String pin; // use the pin string for all small reads
String parts[10]; // parse results from segmenting url string seperating at /
int nparts=0;     // number of parts in URL

void digitalCommand() {
  int pins, value;
  String msg;
  // Read pin number
  pins = parts[1].toInt();
  // If the next character is a '/' it means we have an URL
  // with a value like: "/d/6/1"
  if (nparts==3) {
  value = parts[2].toInt();
  digitalWrite(dpins[pins], value);
  } 
  else {
    value = digitalRead(dpins[pins]);
  }
  // Send feedback to client
    msg="Pin D";
    msg=msg+pins;
    if (nparts!=3)
      msg=msg+" is equal to ";
    else
      msg=msg+" is set to ";
    msg=msg+value;
    server.send(200, "text/plain", msg);
}

void analogCommand() {
  int pins, value;
  String msg;
  pins = parts[1].toInt();
  // If the next character is a '/' it means we have an URL
  // with a value like: "/a/5/120"
  if (nparts==3) {
    // Read value and execute command
    value = parts[2].toInt();
    analogWrite(dpins[pins], value);
    // Send feedback to client
    msg="<html><head><title>PWM pin Report</title></head><body>Pin D";
    msg=msg+pins;
    msg=msg+" set to ";
    msg=msg+value;
    msg=msg+" PWM on scale 0-32767";
    msg=msg+"</body></html>";    
    server.send(200, "text/html", msg);
  } else {
    // Read analog pin
    value = analogRead(0);
    // Send feedback to client
    msg="<html><head><title>Analog pin Report</title></head><body>Pin A0";
    msg=msg+" equal to ";
    msg=msg+value;
    msg=msg+"</body></html>";    
    server.send(200, "text/html", msg);
  }
}

void modeCommand() {
  int pins;
  String msg;
  //Serial.println("In modeCommand");
  // Read pin number
  pins = parts[1].toInt();
  // If the next character is not a '/' we have a malformed URL  
  if (nparts<3) {
    server.send(400,"text/plain","error");
    return;
  }
  parts[2].toLowerCase();
  if (parts[2].equals("input")) {
    pinMode(dpins[pins], INPUT);
    // Send feedback to client    
    msg="<html><head><title>Digital pin Mode Report</title></head><body>Pin D";
    msg=msg+pins;
    msg=msg+" configured as INPUT!\n";
    server.send(200,"text/html",msg+"</body></html>");
    return;
  }
  if (parts[2].equals("output")) {
    pinMode(dpins[pins], OUTPUT);
    // Send feedback to client    
    msg="<html><head><title>Digital pin Mode Report</title></head><body>Pin D";
    msg=msg+pins;
    msg=msg+" configured as OUTPUT!\n";
    server.send(200,"text/html",msg+"</body></html>");
    return;
  }  
if (parts[2].equals("input_pullup")) {
    pinMode(dpins[pins], INPUT_PULLUP);
    // Send feedback to client    
    msg="<html><head><title>Digital pin Mode Report</title></head><body>Pin D";
    msg=msg+pins;
    msg=msg+" configured as INPUT_PULLUP!\n";
    server.send(200,"text/html",msg+"</body></html>");
    return;
  }     
  
    msg="<html><head><title>Digital pin Mode Report</title></head><body>";
    msg=msg+" invalid mode for D";
    msg=msg+pin;
    msg=msg+" ["+pins+"]";
    server.send(200,"text/html",msg+"</body></html>");
}

void pwmCommand() {
//"/s/pin/pw  -> set pin to PWM with pulse width of pw microseconds
  int pwmPeriod=1000000/pwmFreq;
  int duration;
  int pins, value;
  String msg;
  // Read pin number
  pins = parts[1].toInt();
  if (nparts==3) {
  value = parts[2].toInt();
  duration=value*pwmRange/pwmPeriod;
  Serial.print("pwm Duration = ");Serial.println(duration);
  analogWrite(dpins[pins],duration);
  } 
  else {
    msg="Error for servo command";
    server.send(200, "text/plain", msg);
    return;
  }
  // Send feedback to client
    msg="Pin D";
    msg=msg+pins;
    msg=msg+" is set to pulse width of ";
    msg=msg+value;
    msg=msg+" That's a duration of ";msg=msg+duration;
    server.send(200, "text/plain", msg);
}

void parse(String msg)
{
  if (msg.indexOf('/')==0) msg=msg.substring(1);
  int ploc;   nparts=0;  int curloc=0;int done=0;
  while (!done)
  {
    ploc=msg.indexOf('/');
    if (ploc >=0  && nparts<10)
    { 
      parts[nparts++]=msg.substring(0,ploc);msg=msg.substring(ploc+1);
    }
    else if (nparts<10) {parts[nparts++]=msg;done=1;}
  }
  //for (indx=0;indx<nparts;indx++) Serial.println(parts[indx]);  
}

void process() {
  // read the command
  String msg=server.uri();
   Serial.println("Processing " + msg);
   parse(msg);
  // is "d" command?
  if (parts[0].equals("d")) digitalCommand();
  // is "analog" command?
  else if (parts[0].equals("a"))  analogCommand();
  // is "mode" command?
  else if (parts[0].equals("m")) modeCommand();
//"/s/pin/pw  -> set pin to PWM with pulse width of pw microseconds
  else if (parts[0].equals("s")) pwmCommand();
  else  
  { 
        msg="Command error -> "+ server.uri(); server.send(500, "text/plain", msg);  
  }
}

void handleNotFound() 
{ 
  process(); 
}

IPAddress ip(192, 168, 0, 177); 
IPAddress dns(8,8,8,8); 
IPAddress gway(192, 168, 0, 1); 
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip,dns,gway);
  WiFi.begin(ssid, password);
  Serial.println("");
  analogWriteFreq(pwmFreq);
  analogWriteRange(pwmRange);
  pwmFreq=102;
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  server.on("/", handleRoot);
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
  yield();
}
