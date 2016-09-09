#include <FastLED.h>

#define NUM_LEDS 144 // Number of LEDs in strip

//#define NUM_LEDS 144
//#define DATA_PIN 6
// Here's how to control the LEDs from any two pins:
#define DATA_PIN    4
#define CLOCK_PIN   5

CRGB leds[NUM_LEDS];

void setup() {
  // APA102 is dotstars https://github.com/FastLED/FastLED/wiki/Chipset-reference
//    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);
  // or don't
  FastLED.addLeds<APA102, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness( 100);

}

int dot = 0;
int speed = 1;
int phase = 0;
int count=0;
void hueRotate() {
  for (int i = 0; i < NUM_LEDS; i++) {
//    leds[i].fadeToBlackBy(0);

    leds[i] = CHSV(count, 255,255);
  }
  count += speed;
  if (count > 255 ) {
    speed = -1;
  }
  if (count <= 0) {
    speed = 1;
  }
}
void chaser() {
  for (int i = 0; i < NUM_LEDS; i++) {
//    leds[i].fadeLightBy(20);
//        leds[i] -=20 ;
//        leds[i].r -=10;
  leds[i].fadeToBlackBy(20);

  }
  leds[dot] = CHSV(phase, 255,255);//CRGB::Red;
  leds[(dot + 1) % NUM_LEDS] = CRGB::Green;
  leds[(dot + 2) % NUM_LEDS] = CHSV(255-phase, 255,255);//CRGB::Blue;
  FastLED.show();
  // clear this led for the next time around the loop
  //        leds[dot] = CRGB::Black;
  FastLED.delay(3);
  dot += speed;
  if (dot >= NUM_LEDS) {
    dot = 0;
//    speed =-1;
  }
  else if (dot <= 0) {
//    speed = 1;
    dot = NUM_LEDS;
  }
  else if (random(200) == 0 ) {
    speed *= -1;
  ;
  }
  phase = (phase + 3) % 255;
}

void loop() {
  hueRotate();
  FastLED.delay(120);
}
