// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#include "point.h"

//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 144 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_RGB);
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_GBR);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DOTSTAR_BRG);

void setup() {

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int r=0;
int g=0;
int b=0;
int counter=0;
int speed=1;

int pos = 0;
int velocity = 1;

Point point = {255,0,0,0,1};


void drawPoint(int i) {
      if (point.pos == i) {
        r = i;
        strip.setPixelColor(i, r, g, b);
        int next = (i+1) % NUMPIXELS;
        strip.setPixelColor(next, r/2, g, b);
        
        int prev = (i-1);
        if (prev < 0) {
          prev = NUMPIXELS;
        }
        strip.setPixelColor(prev, r/2, g, b);
        
      }
}

void loop() {

    strip.clear();
    // pixels to light
    bool strobe = random(50) == 0;
    
    for (int i=0; i<NUMPIXELS; i++) {
      drawPoint(i );
      if (strobe) {
        strip.setPixelColor(i, random(100), random(50), random(200));
      }
    }
    
    if (random(100) > 10) {
      point.velocity *= -1;
    }
    point.pos+=5;
    
    if (point.pos >  NUMPIXELS || point.pos < 0) {
      point.pos = 0;
    }

    delay(0);
    strip.show();                     // Refresh strip
}
