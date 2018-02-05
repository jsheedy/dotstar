
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
//  point = (point + velocity);  
  
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
void fadeOutLarsonScanner() {
  for (uint16_t i = 255; i >= 0; i--) {
    FastLED.setBrightness(i);
    larsonScanner();
    FastLED.delay(3);
  }
  FastLED.delay(500);
}
void fadeInLarsonScanner() {
  for (uint16_t i = 0; i < 256; i++) {
    FastLED.setBrightness(i);
    larsonScanner();
    FastLED.delay(3);
  }
  FastLED.delay(500);
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

void workingLight() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,12,0);    
  }
  FastLED.show();
}

void fadeInWorkingLight() {
  for (uint16_t i = 0; i < 256; i++) {
    FastLED.setBrightness(i);
    workingLight();
    FastLED.delay(2);
  }
  FastLED.delay(200);
}

void fadeOutWorkingLight() {
  for (uint16_t i = 255; i >= 0; i--) {
    FastLED.setBrightness(i);
    workingLight();
    FastLED.delay(2);
  }
  FastLED.delay(200);
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
  
