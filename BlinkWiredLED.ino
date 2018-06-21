void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); /// use 115200 as the serial baud rate
  pinMode(D3,OUTPUT);
}

void loop() {
#define LEDon 1
  digitalWrite(D3,LEDon);
  delay(100); 
  digitalWrite(D3,!LEDon);
  delay(100);
  digitalWrite(D3,LEDon);
  delay(100);
  digitalWrite(D3,!LEDon);
  delay(800);
}
