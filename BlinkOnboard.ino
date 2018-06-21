void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); /// use 115200 as the serial baud rate
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
#define LEDon 0
  digitalWrite(LED_BUILTIN,LEDon);
  delay(100); 
  digitalWrite(LED_BUILTIN,!LEDon);
  delay(100);
  digitalWrite(LED_BUILTIN,LEDon);
  delay(100);
  digitalWrite(LED_BUILTIN,!LEDon);
  delay(800);
}
