
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
  point = (point + velocity);  
  
  if (point > 0.95) {
//    point = 0.0;
    velocity *= -1;
  }
  if (point < 0.05) {
//    point = 1.0;
    velocity *= -1;
  }
  int h = 128;
  int s = 255;
  int v = 255;

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    float iPoint = (float)i / NUM_LEDS;
    float delta = deltaPoints(iPoint, point);

    if (delta < width) {
      int v = (int)(255.0 * (1-(delta/width))); 
      leds[i] = CHSV(h,s,v);
    }
    else {
      leds[i] = CRGB( 0,0,0);    
    }
  }
  FastLED.show();
}

void simpleGradient() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV((  (int)(t / 1000l) * 5 + i) % 255, 255, 255);
  }
}

void workingLight() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255,255,255);    
  }
  FastLED.show();
}

void allRed() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);    
  }
  FastLED.show();
}
void allBlue() {
  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);    
  }
  FastLED.show();
}
  
