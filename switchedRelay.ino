#define RELAY D1
#define SWITCH D2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); /// use 115200 as the serial baud rate
  pinMode(RELAY,OUTPUT);
  pinMode(SWITCH,INPUT_PULLUP);
}

void loop() {
#define RelayOn 0
  if (!digitalRead(SWITCH)) // when switch pushed pin connected to ground - so active low
    digitalWrite(RELAY,RelayOn); // switch on activate Relay
  else 
    digitalWrite(RELAY,!RelayOn);
  delay(10);
}







