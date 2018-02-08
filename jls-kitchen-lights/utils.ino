
float velocity = 0.005;
float width = 0.05;
float point = 0.5;

float deltaPoints(float p1, float p2) {
  float diff = (p2 - p1);
  if (diff > 0.5) {
    diff -= 1.0;
  }
  if (diff < -0.5) {
    diff += 1.0;
  }
  return fabs(diff);
}

void larsonScanner()
{  
  if (point > 0.95 || point < 0.05) {
    velocity *= -1;
  }

  int h = 0;
  int s = 255;
  int v = 255;

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    float iPoint = (float)i / NUM_LEDS;
    float delta = deltaPoints(iPoint, point);

    if (delta < width) {
      int v = (int)(128 * (1-(delta/width))); 
      leds[i] = CHSV(h,s,v);
    }
    else {
      leds[i] = CRGB( 0,0,0);    
    }
  }
  FastLED.show();
}

void workingLight() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,12,0);    
  }
  FastLED.show();
}

void fadeOut(int t, void (*f)()) {
  int stepsPerSecond = 30;
  int nSteps = t / stepsPerSecond;
  int stepSize = 256 / nSteps;
  for (int i = 255; i >= 0; i-=stepSize) {
    FastLED.setBrightness(i);
    f();
    FastLED.delay(1000 / stepsPerSecond);
  }
}

void fadeIn(int t, void (*f)()) {
  int stepsPerSecond = 30;
  int nSteps = t / stepsPerSecond;
  int stepSize = 256 / nSteps;
  for (uint16_t i = 0; i < 256; i+=stepSize) {
    FastLED.setBrightness(i);
    f();
    FastLED.delay(1000 / stepsPerSecond);
  }
}

void allRed() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(15, 0, 0);    
  }
  FastLED.show();
}
void allBlue() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 15);    
  }
  FastLED.show();
}

void simpleGradient() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((  (int)(t / 1000l) * 5 + i) % 255, 255, 255);
  }
  FastLED.show();
}

void clear() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);    
  }
  FastLED.show();
}
void debugLED(int i, int r,int g,int b) {
  leds[i] = CRGB(r,g,b);
  FastLED.show();
}
  
