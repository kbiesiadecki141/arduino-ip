//************************************
//*                                  *
//*  Katelyn Biesiadecki             *
//*  February 13th, 2017             *
//*                                  *
//*  Ring Light Chaser               *
//*                                  *
//*  This sketch uses an Arduino to  *
//*  control a NeoPixel light ring   *
//*  using a potentiometer. Much of  *
//*  this code is derived from the   *
//*  Adafruit NeoPixel example repo. *
//*                                  *
//************************************

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int sensorPin = A0;
int sensorValue = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  ring.begin();
  ring.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
  changeSpeed(sensorValue);  
  //colorWipe(sensorValue);
}

int loc = 1;
uint16_t j = 0;
void changeSpeed(uint8_t wait) 
{
  ring.setPixelColor(loc - 1, ring.Color(0, 0, 0));
  ring.setPixelColor(loc, Wheel((loc+j) & 255));
  ring.show();
  delay(wait);

  loc += 1;
  
  j += 1;
  if (loc > ring.numPixels()) {
    loc = 0;
  }

  if (j > 256) {
    j = 0;
  }
}

void waohh(uint8_t wait) 
{
  uint32_t c; 
  uint32_t rainbow[] = {ring.Color(255, 0, 0),    ring.Color(127, 64, 0),   //Red, orange
                        ring.Color(255, 255, 0),  ring.Color(0, 255, 0),    //Yellow, green
                        ring.Color(0, 0, 255),    ring.Color(127, 0, 255)}; //Blue, purple
  
  for (uint16_t k = 0; k <= 5; k++) {
      c = rainbow[k];
      for (uint16_t i = 1; i <= ring.numPixels(); i++) {
        ring.setPixelColor(i-1, ring.Color(0, 0, 0));
        ring.setPixelColor(i, c);
        ring.show();
        delay(wait);
      }
  }
}

void bounceColor(uint32_t c, uint8_t wait) {
  for (uint16_t i=1; i<ring.numPixels(); i++) {
    ring.setPixelColor(i-1, ring.Color(0, 0, 0));
    ring.setPixelColor(i, c);
    ring.show();
    delay(wait);
  }
  for (uint16_t i=ring.numPixels(); i>0; i--) {
    ring.setPixelColor(i, ring.Color(0, 0, 0));
    ring.setPixelColor(i-1, c);
    ring.show();
    delay(wait);
  }
}

void bounceRainbow(uint8_t wait) {
  uint32_t c; 
  uint32_t rainbow[] = {ring.Color(255, 0, 0),    ring.Color(127, 64, 0),   //Red, orange
                        ring.Color(255, 255, 0),  ring.Color(0, 255, 0),    //Yellow, green
                        ring.Color(0, 0, 255),    ring.Color(127, 0, 255)}; //Blue, purple
  
  for (uint16_t k=0; k<5; k++) {
      c = rainbow[k];
      for (uint16_t i=1; i<ring.numPixels(); i++) {
        ring.setPixelColor(i-1, ring.Color(0, 0, 0));
        ring.setPixelColor(i, c);
        ring.show();
        delay(wait);
      }
      c = rainbow[k+1];
      k += 1;
      for (uint16_t i=ring.numPixels(); i>0; i--) {
        ring.setPixelColor(i, ring.Color(0, 0, 0));
        ring.setPixelColor(i-1, c);
        ring.show();
        delay(wait);
      }
  }
}

// Fill the dots one after the other with a color
int i = 0;
uint32_t rainbowList[] = {ring.Color(50, 0, 0),    ring.Color(25, 12, 0),   //Red, orange
                      ring.Color(50, 50, 0),  ring.Color(0, 50, 0),    //Yellow, green
                      ring.Color(0, 0, 50),    ring.Color(25, 0, 50)}; //Blue, purple
                      
uint32_t c = rainbowList[0];
int z = 0;
                   
void colorWipe(uint8_t wait) {
    ring.setPixelColor(i, c);
    ring.show();
    delay(wait);

    i += 1;

   if (i > ring.numPixels()) {
     i = 0;
     z += 1;
     if (z > 6) {
      z = 0;
     }
     c = rainbowList[z];
   } 
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel((i+j) & 255));
    }
    ring.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< ring.numPixels(); i++) {
      ring.setPixelColor(i, Wheel(((i * 256 / ring.numPixels()) + j) & 255));
    }
    ring.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, c);    //turn every third pixel on
      }
      ring.show();

      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      ring.show();

      delay(wait);

      for (uint16_t i=0; i < ring.numPixels(); i=i+3) {
        ring.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return ring.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return ring.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return ring.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
