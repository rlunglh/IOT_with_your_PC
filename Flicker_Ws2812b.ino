#include <Adafruit_NeoPixel.h>
uint16_t NP=7 ;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NP, 0, NEO_GBR + NEO_KHZ800);
float oldRGB[3], RGB[3], delta[3];
void setup()
{
  int i;
  strip.begin();
  strip.setBrightness(255);
   Serial.begin(115200);  Serial.println();
// show individual colors
   for (i=0;i<NP;i++) strip.setPixelColor(i,strip.Color(0xff, 0x0, 0x0));strip.show();
   delay(2000); 
   for (i=0;i<NP;i++) strip.setPixelColor(i,strip.Color( 0x0, 0xff,0x0));strip.show();
   delay(2000);
   for (i=0;i<NP;i++) strip.setPixelColor(i,strip.Color(0,0,0xff));strip.show();
   delay(2000);
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
  int i;
// step through the delta values and do analogWrite on D1,D2,D3
    getColors();
    for (int j=1;j<101;j++) // 100 increment values used
    {
      
   for (i=0;i<NP;i++) strip.setPixelColor(i,strip.Color(255*(oldRGB[0]+delta[0]*j),100*(oldRGB[1]+delta[1]*j),255*(oldRGB[2]+delta[2]*j)));
     strip.show();
     delay(25); // sleep 3 milliseconds between increments
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
