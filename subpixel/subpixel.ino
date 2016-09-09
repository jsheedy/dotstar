#include <FastLED.h>
#include "point.h"

const int NUM_LEDS = 144; // Number of LEDs in strip
const int NUM_POINTS = 4;

CRGB leds[NUM_LEDS];
float pixelPos[NUM_LEDS];

Point points[NUM_POINTS] = {
  {0.0, 5, 0.02,0},
  {0.0, 5, -0.01,45},
  {0.0, 5, -0.05,90},
  {0.0, 5, 0.1,120}
};

void setup() {
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(150);
  for (int i=0; i<NUM_LEDS; i++) {
    pixelPos[i] = ((float)i) / ((float)NUM_LEDS) * TWOPI;
  }
}

void loop() {
  FastLED.clear();
  for (int i=0; i<NUM_POINTS; i++) {
    drawPoint(points[i], leds, pixelPos, NUM_LEDS);
    updatePoint(points[i]);
  }
  FastLED.show();

//  FastLED.delay(10);
}
