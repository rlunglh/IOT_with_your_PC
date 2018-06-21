float oldRGB[3], RGB[3], delta[3];
void setup()
{
// set D1,D2,D3 to OUTPUT mode
   pinMode(D1,OUTPUT); 
   pinMode(D2,OUTPUT);
   pinMode(D3,OUTPUT);
// analogWrite values to D1,D2,D3 in sequence to verify each color is working
   analogWrite(D1,0); 
   analogWrite(D2,0);
   analogWrite(D3,0);
// show individual colors
   analogWrite(D1,1023);
   delay(2000); 
   analogWrite(D1,0); 
   analogWrite(D2,400);
   delay(2000);
   analogWrite(D2,0);
   analogWrite(D3,1023);
   delay(2000);
   analogWrite(D3,0);
// Setup serial communication to support debug
   Serial.begin(115200);  Serial.println();
}
// define function to randomly assign values
// to the RGB array and calculate the delta array
void getColors() // gets random values for the three RGB values
{  
    for (int j=0;j<3;j++) // j goes from 0 to 2 over the for loop to 
//                           get all three color values
    {
       RGB[j]=(float)random(256)/256.0; 
       RGB[j]*=RGB[j]; // square value to reduce max intensities and spread color range 
       delta[j]=(RGB[j]-oldRGB[j])/100.0; 
// calculate delta for stepping color change over 100 values
    }
}
/* I have green LED on pin D2 and I reduced its max intensity to 400
 * for better apparent color balance. Your results may differ so you
 * can set the individual RGB max values as you like  */
void loop()
{
// step through the delta values and do analogWrite on D1,D2,D3
    getColors();
    for (int j=1;j<101;j++) // 100 increment values used
    {
      analogWrite(D1,1023*(oldRGB[0]+delta[0]*j));//setValue D1 pwm
      analogWrite(D2,400*(oldRGB[1]+delta[1]*j)); //setValue D2 pwm
      analogWrite(D3,1023*(oldRGB[2]+delta[2]*j));//setValue D3 pwm
      delay(3); // sleep 3 milliseconds between increments
      // delay values specified in msec so level changes in 0.3 sec
   }
   for (int j=0;j<3;j++) 
// loop to update final values in oldRGB
   {
      oldRGB[j]+=delta[j]*100.0; 
// final value is oldRGB + delta * 100
      if (oldRGB[j]<0.0) oldRGB[j]=0.001; 
// arithmetic errors could make oldRGB // negative so fix it
   }
   delay(200); 
// sleep 0.2 seconds to show persist on final color in the ramp
}

