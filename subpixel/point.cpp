#include "point.h"
#include <FastLED.h>


int getValue(float delta) {
  if (delta < deltaVal) {
    return constrain((int) ((1.0-delta/deltaVal) * 255.0), 0, 255);
  } else {
    return 0.0;
  } 
}

void updatePoint(Point &point) {
    point.pos = fmod((point.pos + point.speed), TWOPI);
    if (point.pos < 0.0) {
      point.pos = TWOPI;
    }
    point.hue = (point.hue + random8(3)) % 255;
}

float angleDiff(float angle1, float angle2) {
  return min(fmod((angle1 - angle2 + TWOPI), TWOPI), fmod((angle2 - angle1 + TWOPI), TWOPI));
}

void drawPoint(Point point, CRGB leds[], float pixelPos[], int NUM_LEDS) {
    for (int i=0; i<NUM_LEDS; i++) {
      float delta = angleDiff(pixelPos[i], point.pos) ;
      int value = getValue(delta);     
      leds[i] += CHSV(point.hue, 255, value);
    }
}


