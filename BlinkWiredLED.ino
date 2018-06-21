void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); /// use 115200 as the serial baud rate
  pinMode(D7,OUTPUT);
}

void loop() {
#define LEDon 1
  digitalWrite(D7,LEDon);
  delay(100); 
  digitalWrite(D7,!LEDon);
  delay(100);
  digitalWrite(D7,LEDon);
  delay(100);
  digitalWrite(D7,!LEDon);
  delay(800);
}
