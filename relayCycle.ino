#deffine RELAY D1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); /// use 115200 as the serial baud rate
  pinMode(RELAY,OUTPUT);
}

void loop() {
#define RelayOn 1
  digitalWrite(RELAY,RelayOn);
  delay(1000); 
  digitalWrite(RELAY,!RelayOn);
  delay(1000);
}
