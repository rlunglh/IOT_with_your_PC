void setup() {
  Serial.begin(115200);
  Serial.println();
}
 
void loop() {
  int val=analogRead(0);
  float volts=val*3.3/1024;
  Serial.printf("Voltage is %0.2f\n",volts);
  delay(2000);
}
