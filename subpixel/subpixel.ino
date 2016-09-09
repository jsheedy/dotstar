#include <FastLED.h>
#include "point.h"

const int NUM_LEDS = 144; // Number of LEDs in strip
const float TWOPI = 6.28318530718;
const float deltaVal = 0.2;

CRGB leds[NUM_LEDS];
float pixelPos[NUM_LEDS];

Point point1 = {0.1, 5, 0.02,0};
Point point2 = {0.5, 5, -0.1,90};
Point point3 = {0.5, 5, 0.08,180};

Point points[3];

void setup() {
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(150);
  for (int i=0; i<NUM_LEDS; i++) {
    pixelPos[i] = ((float)i) / ((float)NUM_LEDS) * TWOPI;
  }
  points[0] = point1;
  points[1] = point2;
  points[2] = point3;
}


float angleDiff(float angle1, float angle2) {
  return min(fmod((angle1 - angle2 + TWOPI), TWOPI), fmod((angle2 - angle1 + TWOPI), TWOPI));
}

int getValue(float delta) {
  // returns the Value (0-255) 
//  return map(delta, 0, fpDelta , 255, 0);
//  return map((int)(delta*MAXINT), 0, fpDelta/2.0*MAXINT , 255, 0);

  if (delta < deltaVal) {
    return constrain((int) ((1.0-delta/deltaVal) * 255.0), 0, 255);
  } else {
    return 0.0;
  }
  
}

void drawPoint(Point point) {
    for (int i=0; i<NUM_LEDS; i++) {
      float delta = angleDiff(pixelPos[i], point.pos) ;
      int value = getValue(delta);     
      leds[i] += CHSV(point.hue, 255, value);
    }
}

Point updatePoint(Point point) {
//    point.pos+= point.speed;
//    if (point.pos > TWOPI) {
//      point.pos = 0.0;
//    }
//    else if (point.pos < 0.0) {
//      point.pos = TWOPI;
//    }
    point.pos = fmod((point.pos + point.speed), TWOPI);
    if (point.pos < 0.0) {
      point.pos = TWOPI;
    }
    point.hue = (point.hue + 1) % 255;
    return point;
}

void loop() {
  FastLED.clear();
//  for (int i=0; i<3; i++) {
//    drawPoint(points[i]);
//  }
  drawPoint(point1);
  drawPoint(point2);
  drawPoint(point3);
  FastLED.show();
  point1 = updatePoint(point1);
  point2 = updatePoint(point2);
  point3 = updatePoint(point3);
//  FastLED.delay(10);
}
