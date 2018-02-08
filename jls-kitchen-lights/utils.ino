
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
  float width = 0.05;
  float point;

  int milli = (t % 1000);
  int second = (t / 1000) % 2;
  if (second == 0) {
    point = 0.05 + (float)milli / 1000.0 * 0.9;  
  } else {
    point = 0.05 + (float)(1000 - milli) / 1000.0 * 0.9;
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
    // breadboard circuit can't handle current from full blast LEDs 
    if(DEBUG) {
      leds[i] = CRGB(0,12,0);  
    }
    else {
      leds[i] = CRGB(255,255,255);    
    }
  }
  FastLED.show();
}

void fade(int _t, void(*f)(), bool fadeIn) {
  unsigned long _t0 = millis();
  int _dt = 0;
  uint8_t b;
  int _b;
  while(_dt < _t) {
    _b = (int)((float)_dt/(float)_t * 255.0);
    if (fadeIn) {
      b = dim8_lin(_b);  
    } else {
      b = 255-dim8_lin(_b);
    }
    FastLED.setBrightness(b);
    f();
    t = millis();
    _dt = t - _t0;
  }
}

void fadeOut(int _t, void (*f)()) {
  fade(_t, f, false);
}

void fadeIn(int _t, void (*f)()) {
  fade(_t, f, true);
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
  
