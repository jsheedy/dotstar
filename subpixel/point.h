#include "constants.h"
#include <FastLED.h>

const float deltaVal = 0.2;

struct Point {
  double pos;
  unsigned char width;
  double speed;
  int hue;
};

int getValue(float delta);
float angleDiff(float angle1, float angle2);
void updatePoint(Point &point);
void drawPoint(Point point, CRGB leds[], float pixelPos[], int NUM_LEDS);
